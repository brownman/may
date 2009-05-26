#include "EntityManager.h"


EntityManager::EntityManager()
{
	initAttributes();
}

EntityManager::~EntityManager() { }

EntityManager* EntityManager::get()
{
	static EntityManager emgr;
	return &emgr;
}

Entity* EntityManager::getEntity(int id)
{
	return allEntitys[id];
}

void EntityManager::addEntity(Entity* ent)
{
	allEntitys.push_back(ent);
}

/**
 * @return int
 */
int EntityManager::getNewID()
{
	return lastID++;
}

void EntityManager::initAttributes()
{
	lastID = 0;
}

int EntityManager::count()
{
	return allEntitys.size();
}


