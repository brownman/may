#include <irrlicht/irrlicht.h>
#include <btBulletDynamicsCommon.h>
#include <btBulletCollisionCommon.h>
#include <BulletCollision/CollisionShapes/btShapeHull.h>

#include "src/GraphicsEngine.h"
#include "src/Physics.h"

#include <stdio.h>
#include <stdlib.h>
#include <string>

#include "src/EntityManager.h"

using namespace irr;

void QuaternionToEuler(const btQuaternion &TQuat, btVector3 &TEuler);

int main(int argc, char **argv)
{
	GraphicsEngine * graphics = GraphicsEngine::get();
	graphics->init();
	IrrlichtDevice* device = graphics->getDevice();
	
	Physics* physics = new Physics();
	physics->init();
	
	physics->createStaticTrimesh("playground.obj", vector3df(0, 0, 0), vector3df(2, 2, 2));
	physics->addSphere(vector3df(0,0,0), 2, 1, vector3df(1,1,1));
	EntityManager::get()->getEntity(2)->getSceneNode();
	
	for(int i = 0; i <= 3; i++)
	{
	physics->addSphere();
	physics->addCube();
	}
	
	ICameraSceneNode * cam = graphics->getSceneMgr()->addCameraSceneNode(EntityManager::get()->getEntity(2)->getSceneNode(), vector3df(0,5,15));
	
	// draw everything
	u32 timestamp = device->getTimer()->getTime();
	u32 delta = 0;
	
	while(device->run() && device->getVideoDriver())
	{
		delta = device->getTimer()->getTime() - timestamp;
		timestamp = device->getTimer()->getTime();
		
	cam->setTarget(EntityManager::get()->getEntity(2)->getSceneNode()->getPosition());
		
	if(graphics->receiver.IsKeyDown(KEY_KEY_A))
	{
		EntityManager::get()->getEntity(2)->getBody()->applyCentralForce(btVector3(50,0,0));
	}
	
	else if(graphics->receiver.IsKeyDown(KEY_KEY_D))
	{
		EntityManager::get()->getEntity(2)->getBody()->applyCentralForce(btVector3(-50,0,0));
	}
	else if(graphics->receiver.IsKeyDown(KEY_KEY_S))
	{
		EntityManager::get()->getEntity(2)->getBody()->applyCentralForce(btVector3(0,0,50));
	}
	else if(graphics->receiver.IsKeyDown(KEY_KEY_W))
	{
		EntityManager::get()->getEntity(2)->getBody()->applyCentralForce(btVector3(0,0,-50));
	}
	else if(graphics->receiver.IsKeyDown(KEY_SPACE))
	{
		EntityManager::get()->getEntity(2)->getBody()->applyCentralForce(btVector3(0,50,0));
	}
		physics->update(delta);
		graphics->update();
	}

	// delete device
	device->drop();
	return 0;
}
