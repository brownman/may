#include "Entity.h"

#include <irrlicht/irrlicht.h>
#include <btBulletCollisionCommon.h>

#include "EntityManager.h"

using namespace irr;

using namespace core;

Entity::Entity()
{
	id = EntityManager::get()->getNewID();
	EntityManager::get()->addEntity(this);
//	body = 0;
//	collisionObject = 0;
}

Entity::~Entity() { }

void Entity::create()
{
}


/**
 * @return btRigidBody*
 */

btRigidBody* Entity::getBody()
{
	return body;
}

btCollisionObject* Entity::getCollisionObject()
{
	return collisionObject;
}

/**
 * @return ISceneNode*
 */
ISceneNode* Entity::getSceneNode()
{
	return sceneNode;
}


void Entity::setCollisionObject(btCollisionObject* obj)
{
	this->collisionObject = obj;
}


/**
 * @param  colBody
 */
void Entity::setBody(btRigidBody* body)
{
	this->body = body;
}


/**
 * @param  node
 */
void Entity::setSceneNode(ISceneNode* node)
{
	this->sceneNode = node;
}


/**
 * @param  position
 */
void Entity::setPos(vector3df position)
{
	this->pos = position;
}


/**
 * @param  rotation
 */
void Entity::setRot(vector3df rotation)
{
	this->rot = rotation;
}

void Entity::setScale(irr::core::vector3df scale)
{
	this->scale = scale;
}

irr::core::vector3df Entity::getScale()
{
	return this->scale;
}

/**
 * @return vector3df
 */
vector3df Entity::getRot()
{
	return rot;
}


/**
 * @return vector3df
 */
vector3df Entity::getPos()
{
	return pos;
}


/**
 * @return int
 */
int Entity::getID()
{
	return id;
}

