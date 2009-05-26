
#ifndef PHYSICS_H
#define PHYSICS_H

#include <btBulletDynamicsCommon.h>
#include <btBulletCollisionCommon.h>
#include <irrlicht/irrlicht.h>

#include "Entity.h"

using namespace irr;
using namespace core;

class Physics
{

	public:
		/**
		 * Empty Constructor
		 */
		Physics();

		/**
		 * Empty Destructor
		 */
		virtual ~Physics();

		/**
		 */
		void init();

		/**
		 */
		void update(float deltaTime);

		/**
		 * @return btDiscreteDynamicsWorld
		 */
		btDiscreteDynamicsWorld * getWorld();

		/**
		 * @param  filename
		 * @param  pos
		 * @param  mass
		 * @param  scale
		 */
		btCollisionShape * createShapeFromTrimesh(const char * filename, vector3df pos = vector3df(0, 0, 0), float mass = 0.0f, vector3df scale = vector3df(1.0f, 1.0f, 1.0f));
		
		Entity* createStaticTrimesh(const char * filename, vector3df pos = vector3df(0, 0, 0), vector3df scale = vector3df(1.0f, 1.0f, 1.0f));

		/**
		 * @param  pos
		 * @param  mass
		 * @param  size
		 * @param  scale
		 */
		void addCube(vector3df pos = vector3df(0.0f, 0.0f, 0.0f), float mass = 1.0f, float size = 1.0f, vector3df scale = vector3df(1.0f, 1.0f, 1.0f));

		/**
		 * @param  mass
		 * @param  pos
		 * @param  radius
		 * @param  scale
		 */
		void addSphere(vector3df pos = vector3df(0.0f, 0.0f, 0.0f), float mass = 1.0f, float radius = 1, vector3df scale = vector3df(1.0f, 1.0f, 1.0f));

	private:
		btDiscreteDynamicsWorld * physicsWorld;

};

#endif // PHYSICS_H
