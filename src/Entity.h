
#ifndef ENTITY_H
#define ENTITY_H

#include <btBulletDynamicsCommon.h>
#include <irrlicht/irrlicht.h>


using namespace irr;
using namespace core;
using namespace scene;

class Entity
{
public:
		/**
		 * Empty Constructor
		 */
		Entity ( );

		/**
		 * Empty Destructor
		 */
		virtual ~Entity ( );

		void create();

		/**
		 * @return btCollisionBody*
		 */
		btRigidBody* getBody ( );
		
		btCollisionObject* getCollisionObject();

		/**
		 * @return ISceneNode*
		 */
		ISceneNode* getSceneNode ( );


		void setCollisionObject(btCollisionObject* obj);
		
		/**
		 * @param  colBody
		 */
		void setBody (btRigidBody* node );


		/**
		 * @param  node
		 */
		void setSceneNode (ISceneNode* node );


		/**
		 * @param  position
		 */
		void setPos (vector3df position );


		/**
		 * @param  rotation
		 */
		void setRot (vector3df rotation );

		void setScale (vector3df scale);
		
		vector3df getScale();

		/**
		 * @return vector3df
		 */
		vector3df getRot ( );


		/**
		 * @return vector3df
		 */
		vector3df getPos ( );


		/**
		 * @return int
		 */
		int getID ( );

private:
		ISceneNode * sceneNode;
		btRigidBody * body;
		vector3df pos;
		vector3df rot;
		vector3df scale;
		int id;
		btCollisionObject * collisionObject;
};

#endif // ENTITY_H
