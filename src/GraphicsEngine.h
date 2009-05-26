
#ifndef GRAPHICSENGINE_H
#define GRAPHICSENGINE_H

#include <irrlicht/irrlicht.h>

using namespace irr;
using namespace core;
using namespace video;
using namespace scene;

class MyEventReceiver : public IEventReceiver
{
public:
        // This is the one method that we have to implement
        virtual bool OnEvent(const SEvent& event)
        {
                // Remember whether each key is down or up
                if (event.EventType == irr::EET_KEY_INPUT_EVENT)
                        KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;

                return false;
        }

        // This is used to check whether a key is being held down
        virtual bool IsKeyDown(EKEY_CODE keyCode) const
        {
                return KeyIsDown[keyCode];
        }
        
        MyEventReceiver()
        {
                for (u32 i=0; i<KEY_KEY_CODES_COUNT; ++i)
                        KeyIsDown[i] = false;
        }

private:
        // We use this array to store the current state of each key
        bool KeyIsDown[KEY_KEY_CODES_COUNT];
};


class GraphicsEngine
{

	public:
		/**
		 * Empty Constructor
		 */
		GraphicsEngine();

		/**
		 * Empty Destructor
		 */
		virtual ~GraphicsEngine();

		static GraphicsEngine* get();

		/**
		 * @return IVideoDriver*
		 */
		IVideoDriver* getDriver();

		/**
		 * @return IrrlichtDevice*
		 */
		IrrlichtDevice* getDevice();

		/**
		 * @return ISceneManager*
		 */
		ISceneManager* getSceneMgr();
		
		/**
		 */
		void init();

		MyEventReceiver receiver;

		/**
		 */
		void update();

	private:
		IVideoDriver* driver;
		ISceneManager* scenemgr;
		IrrlichtDevice* device;

};



#endif // GRAPHICSENGINE_H
