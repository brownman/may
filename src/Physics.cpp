#include "Physics.h"

#include <btBulletDynamicsCommon.h>
#include <btBulletCollisionCommon.h>
#include <BulletCollision/CollisionShapes/btShapeHull.h>

#include "GraphicsEngine.h"
#include "EntityManager.h"
#include "support/cd_wavefront.h"

Physics::Physics()
{
}

Physics::~Physics() { }

/**
 */
void Physics::init()
{
	// init bullet
	btDefaultCollisionConfiguration * CollisionConfiguration = new btDefaultCollisionConfiguration();
	btBroadphaseInterface * BroadPhase = new btAxisSweep3(btVector3(-1000, -1000, -1000), btVector3(1000, 1000, 1000));
	btCollisionDispatcher * Dispatcher = new btCollisionDispatcher(CollisionConfiguration);
	btSequentialImpulseConstraintSolver * Solver = new btSequentialImpulseConstraintSolver();
	physicsWorld = new btDiscreteDynamicsWorld(Dispatcher, BroadPhase, Solver, CollisionConfiguration);
}


/**
 */
void Physics::update(float deltaTime)
{
	// step the simulation
	physicsWorld->stepSimulation(deltaTime * 0.001f);

	// update objects positions

	for (int i = 0; i <= EntityManager::get()->count() - 1;i++)
	{
		Entity* e = EntityManager::get()->getEntity(i);

		if (e->getBody() != 0)
		{
			btVector3 pos = e->getBody()->getCenterOfMassPosition();
			e->getSceneNode()->setPosition(vector3df(pos.getX(), pos.getY(), pos.getZ()));

			btQuaternion equat = e->getBody()->getOrientation();
			core::quaternion quat;
			quat.W = equat.getW();
			quat.X = equat.getX();
			quat.Y = equat.getY();
			quat.Z = equat.getZ();

			core::vector3df rot;
			quat.toEuler(rot);
			e->getSceneNode()->setRotation(rot);
		}
	}
}


/**
 * @return btDiscreteDynamicsWorld
 */
btDiscreteDynamicsWorld * Physics::getWorld()
{
	return physicsWorld;
}


/**
 * @param  filename
 * @param  pos
 * @param  mass
 * @param  scale
 */
btCollisionShape * Physics::createShapeFromTrimesh(const char * filename, vector3df pos, float mass, vector3df scale)
{
	btTriangleMesh* trimesh = new btTriangleMesh();

	// Set the initial position of the object
	btTransform trans;
	trans.setIdentity();
	trans.setOrigin(btVector3(pos.X, pos.Y, pos.Z));

	// set the initial scale of the object
	btVector3 localscale = btVector3(scale.X, scale.Y, scale.Z);
	// Is the file existing?
	//std::string filename = FileSystem::get()->getFileExists(std::string("models/") + modelfile);

	// Load the wavefront file
	ConvexDecomposition::WavefrontObj file;
	file.loadObj("playground.obj");

	// Create the shape
	// Store the triangle data from the modelfile in the triangle shape

	if (file.mTriCount)
	{
		for (int i = 0; i < file.mTriCount; i++)
		{
			int index0 = file.mIndices[i*3];
			int index1 = file.mIndices[i*3+1];
			int index2 = file.mIndices[i*3+2];

			btVector3 vertex0(file.mVertices[index0*3], file.mVertices[index0*3+1], file.mVertices[index0*3+2]);
			btVector3 vertex1(file.mVertices[index1*3], file.mVertices[index1*3+1], file.mVertices[index1*3+2]);
			btVector3 vertex2(file.mVertices[index2*3], file.mVertices[index2*3+1], file.mVertices[index2*3+2]);

			vertex0 *= localscale;
			vertex1 *= localscale;
			vertex2 *= localscale;

			trimesh->addTriangle(vertex0, vertex1, vertex2);
		}

		btCollisionShape* shape;

		if (mass != 0.0f)
		{
			// create convex shape
			btConvexShape *tmpshape = new btConvexTriangleMeshShape(trimesh);
			btShapeHull *hull = new btShapeHull(tmpshape);
			btScalar margin = tmpshape->getMargin();
			hull->buildHull(margin);
			tmpshape->setUserPointer(hull);

			shape = new btConvexHullShape();
			btConvexHullShape *convexshape = (btConvexHullShape*)(shape);

			for (int j = 0; j < hull->numVertices() ; j++)
			{
				convexshape->addPoint(btVector3(hull->getVertexPointer()[j]));
			}

			delete tmpshape;

			delete hull;
			return shape;
		}

		else
		{
			shape = new btBvhTriangleMeshShape(trimesh, true);
			return shape;
			/*btCollisionObject* obj = new btCollisionObject();
			obj->setCollisionShape(shape);
			obj->setWorldTransform(trans);

			physicsWorld->addCollisionObject(obj);

			Entity* tri = new Entity();
			tri->setPhysicsNode(obj);

			objects.push_back(tri);*/
		}

	}
}

Entity* Physics::createStaticTrimesh(const char* filename, irr::core::vector3df pos, irr::core::vector3df scale)
{
	Entity* entity = new Entity();

	ISceneManager * scenemgr = GraphicsEngine::get()->getSceneMgr();
	IMeshSceneNode * node = scenemgr->addMeshSceneNode(scenemgr->getMesh(filename));
	node->setScale(scale);
	node->setMaterialFlag(video::EMF_LIGHTING, true);

	btTransform trans;
	trans.setIdentity();
	trans.setOrigin(btVector3(pos.X, pos.Y, pos.Z));

	btCollisionObject *obj = new btCollisionObject();
	obj->setCollisionShape(createShapeFromTrimesh(filename, pos, 0, scale));
	obj->setWorldTransform(trans);

	entity->setSceneNode(node);
	entity->setCollisionObject(obj);
	entity->setPos(pos);
	entity->setScale(scale);

	physicsWorld->addCollisionObject(obj);

	EntityManager::get()->addEntity(entity);

	return entity;
}



/**
 * @param  pos
 * @param  mass
 * @param  size
 * @param  scale
 */
void Physics::addCube(vector3df pos, float mass, float size, vector3df scale)
{

	Entity* entity = new Entity();

	ISceneManager * scenemgr = GraphicsEngine::get()->getSceneMgr();

	//create cube
	ISceneNode *node = scenemgr->addCubeSceneNode(size);
	node->setPosition(pos);

	// Set the initial position of the object
	btTransform transform;
	transform.setIdentity();
	transform.setOrigin(btVector3(pos.X, pos.Y, pos.Z));

	btDefaultMotionState *motionState = new btDefaultMotionState(transform);

	// Create the shape
	btCollisionShape *shape = new btBoxShape(btVector3(size, size, size));

	// Add mass
	btVector3 localInertia;
	shape->calculateLocalInertia(mass, localInertia);

	// Create the rigid body object
	btRigidBody *rigidBody = new btRigidBody(mass, motionState, shape, localInertia);

	// Add it to the world
	physicsWorld->addRigidBody(rigidBody);

	entity->setSceneNode(node);
	entity->setBody(rigidBody);
	entity->setPos(pos);
	entity->setScale(scale);
	EntityManager::get()->addEntity(entity);
}


/**
 * @param  mass
 * @param  pos
 * @param  radius
 * @param  scale
 */
void Physics::addSphere(vector3df pos, float mass, float radius, vector3df scale)
{
	Entity* entity = new Entity();
	
	ISceneManager * scenemgr = GraphicsEngine::get()->getSceneMgr();

	//create cube
	ISceneNode *node = scenemgr->addSphereSceneNode(radius);
	node->setPosition(pos);

	// Set the initial position of the object
	btTransform transform;
	transform.setIdentity();
	transform.setOrigin(btVector3(pos.X, pos.Y, pos.Z));

	btDefaultMotionState *motionState = new btDefaultMotionState(transform);

	// Create the shape
	btCollisionShape *shape = new btSphereShape(radius);

	// Add mass
	btVector3 localInertia;
	shape->calculateLocalInertia(mass, localInertia);

	// Create the rigid body object
	btRigidBody *rigidBody = new btRigidBody(mass, motionState, shape, localInertia);

	// Add it to the world
	physicsWorld->addRigidBody(rigidBody);
	
	entity->setSceneNode(node);
	entity->setBody(rigidBody);
	entity->setPos(pos);
	entity->setScale(scale);
	EntityManager::get()->addEntity(entity);
}

