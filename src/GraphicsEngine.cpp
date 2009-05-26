#include "GraphicsEngine.h"
#include <irrlicht/irrlicht.h>

using namespace irr;
using namespace core;
using namespace video;
using namespace scene;


GraphicsEngine::GraphicsEngine ( ) 
{
MyEventReceiver  receiver;
}

GraphicsEngine::~GraphicsEngine ( ) { }

/**
 * @return IVideoDriver*
 */
IVideoDriver* GraphicsEngine::getDriver ( )
{
	return driver;
}

/**
 * @return IrrlichtDevice*
 */
IrrlichtDevice* GraphicsEngine::getDevice ( )
{
	return device;
}

/**
 * @return ISceneManager*
 */
ISceneManager* GraphicsEngine::getSceneMgr ( )
{
	return scenemgr;
}

/**
 */
void GraphicsEngine::init ( )
{

	// start up the engine
	device = createDevice(video::EDT_OPENGL, core::dimension2d<s32>(800,600), 32, 0, true, 0, &receiver);

	driver = device->getVideoDriver();
	scenemgr = device->getSceneManager();

	device->setWindowCaption(L"may");
	device->getCursorControl()->setVisible(false);
	
	ILightSceneNode * light = scenemgr->addLightSceneNode(0,core::vector3df(0,0,10),video::SColorf(1,0,0));
	light->enableCastShadow(true);
//	scenemgr->addCameraSceneNodeFPS();
}

/**
 */
void GraphicsEngine::update ()
{
		driver->beginScene(true, true, video::SColor(200,200,200,255));
		scenemgr->drawAll();
		driver->endScene();
}

GraphicsEngine* GraphicsEngine::get()
{
	static GraphicsEngine graphics;
	return &graphics;
}

