
#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include <irrlicht/irrlicht.h>
#include "Entity.h"

using namespace irr;
using namespace core;

class EntityManager
{
public:
		/**
		 * Empty Constructor
		 */
		EntityManager ( );

		/**
		 * Empty Destructor
		 */
		virtual ~EntityManager ( );
		
		static EntityManager* get();
		
		/**
		 * @return int
		 */
		int getNewID ( );
		
		Entity* getEntity(int id);
		int count();
		void addEntity(Entity* ent);

private:
		
		int lastID;
		void initAttributes ( ) ;		
		array<Entity*> allEntitys;

};

#endif // ENTITYMANAGER_H
