/*
-----------------------------------------------------------------------------
Filename:    BasicTutorial7.cpp
-----------------------------------------------------------------------------

This source file is part of the
   ___                 __    __ _ _    _
  /___\__ _ _ __ ___  / / /\ \ (_) | _(_)
 //  // _` | '__/ _ \ \ \/  \/ / | |/ / |
/ \_// (_| | | |  __/  \  /\  /| |   <| |
\___/ \__, |_|  \___|   \/  \/ |_|_|\_\_|
      |___/
      Tutorial Framework
      http://www.ogre3d.org/tikiwiki/
-----------------------------------------------------------------------------
*/

#include <CEGUI/System.h>
#include <CEGUI/Logger.h>
#include <CEGUI/MouseCursor.h>
#include <CEGUI/RendererModules/Ogre/ResourceProvider.h>
#include <CEGUI/RendererModules/Ogre/ImageCodec.h>
#include <CEGUI/RendererModules/Ogre/Renderer.h>

#include "BasicTutorial7.h"

//-------------------------------------------------------------------------------------
BasicTutorial7::BasicTutorial7(void)
    : mRenderer(0)
{
}
//-------------------------------------------------------------------------------------
BasicTutorial7::~BasicTutorial7(void)
{
    CEGUI::OgreRenderer::destroySystem();
}

//-------------------------------------------------------------------------------------
void BasicTutorial7::createScene(void)
{

//    Ogre::RenderTarget * target = new Ogre::RenderTarget();
    //mRenderer = &CEGUI::OgreRenderer::bootstrapSystem();
    mRenderer = &CEGUI::OgreRenderer::create();
    CEGUI::OgreResourceProvider& rp = CEGUI::OgreRenderer::createOgreResourceProvider();
    CEGUI::OgreImageCodec& ic = CEGUI::OgreRenderer::createOgreImageCodec();
    CEGUI::System::create(*mRenderer, &rp, 0, &ic, 0,  "", "logs/CEGUI.log");

    //CEGUI::MouseCursor::setVisible(true);
    // 设置日志文件，非追加方式
    //CEGUI::Logger::getSingleton().setLogFilename("logs/CEGUI.log");


    CEGUI::ImageManager::setImagesetDefaultResourceGroup("Imagesets");
    CEGUI::Font::setDefaultResourceGroup("Fonts");
    CEGUI::Scheme::setDefaultResourceGroup("Schemes");
    CEGUI::WidgetLookManager::setDefaultResourceGroup("LookNFeel");
    CEGUI::WindowManager::setDefaultResourceGroup("Layouts");

    CEGUI::SchemeManager::getSingleton().createFromFile("TaharezLook.scheme");
    CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().setDefaultImage("TaharezLook/MouseArrow");
    CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().show();
    // Do not add this to the program
    //CEGUI::Window *guiRoot = CEGUI::WindowManager::getSingleton().loadLayoutFromFile("TextDemo.layout");
    //CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(guiRoot);
//////////////////
    CEGUI::WindowManager &wmgr = CEGUI::WindowManager::getSingleton();
    CEGUI::Window *sheet = wmgr.createWindow("DefaultWindow", "CEGUIDemo/Sheet");

    CEGUI::Window *quit = wmgr.createWindow("TaharezLook/Button", "CEGUIDemo/QuitButton");
    quit->setText("Quit");
    quit->setSize(CEGUI::USize(CEGUI::UDim(0.15, 0), CEGUI::UDim(0.05, 0)));

    //sheet->addChildWindow(quit);
    //CEGUI::System::getSingleton().setGUISheet(sheet);
    sheet->addChild(quit);
    CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(sheet);

    quit->subscribeEvent(CEGUI::PushButton::EventClicked,
    CEGUI::Event::Subscriber(&BasicTutorial7::quit, this));

    mSceneMgr->setAmbientLight(Ogre::ColourValue(254, 1, 1));
    mSceneMgr->setSkyDome(true, "Examples/CloudySky", 5, 8);
    Ogre::Entity* ogreHead = mSceneMgr->createEntity("Head", "ogrehead.mesh");
    Ogre::SceneNode* headNode = mSceneMgr->getRootSceneNode()->createChildSceneNode(Ogre::Vector3(0, 0, -300));
    headNode->attachObject(ogreHead);

    Ogre::TexturePtr tex = mRoot->getTextureManager()->createManual(
        "RTT",
        Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
        Ogre::TEX_TYPE_2D,
        512,
        512,
        0,
        Ogre::PF_R8G8B8,
        Ogre::TU_RENDERTARGET);
    Ogre::RenderTexture *rtex = tex->getBuffer()->getRenderTarget();

    Ogre::Camera *cam = mSceneMgr->createCamera("RTTCam");
    cam->setPosition(100, -100, -400);
    cam->lookAt(0, 0, -300);
    Ogre::Viewport *v = rtex->addViewport(cam);
    v->setOverlaysEnabled(false);
    v->setClearEveryFrame(true);
    v->setBackgroundColour(Ogre::ColourValue::Black);

    CEGUI::Texture &guiTex = mRenderer->createTexture("guiTex",tex);

    //CEGUI::Imageset &imageSet =
    //CEGUI::ImagesetManager::getSingleton().create("RTTImageset", guiTex);
    //imageSet.defineImage("RTTImage",
    //                    CEGUI::Point(0.0f, 0.0f),
    //                     CEGUI::Size(guiTex.getSize().d_width,
    //                                guiTex.getSize().d_height),
    //                     CEGUI::Point(0.0f, 0.0f));
    const CEGUI::Rectf rect(CEGUI::Vector2f(0.0f, 0.0f), guiTex.getOriginalDataSize());
    CEGUI::BasicImage* image = (CEGUI::BasicImage*)( &CEGUI::ImageManager::getSingleton().create("BasicImage", "RTTImage"));
    image->setTexture(&guiTex);
    image->setArea(rect);
    image->setAutoScaled(CEGUI::ASM_Both);

    CEGUI::Window *si = CEGUI::WindowManager::getSingleton().createWindow("TaharezLook/StaticImage", "RTTWindow");
    si->setSize(CEGUI::USize(CEGUI::UDim(0.5f, 0),
                                CEGUI::UDim(0.4f, 0)));
    si->setPosition(CEGUI::UVector2(CEGUI::UDim(0.5f, 0),
                                    CEGUI::UDim(0.0f, 0)));

    //si->setProperty("Image", CEGUI::PropertyHelper::imageToString(&imageSet.getImage("RTTImage")));
    //sheet->addChildWindow(si);
    si->setProperty("Image", "RTTImage");
    sheet->addChild(si);
}

void BasicTutorial7::createFrameListener(void)
{
    Ogre::LogManager::getSingletonPtr()->logMessage("*** Initializing OIS ***");
    OIS::ParamList pl;
    size_t windowHnd = 0;
    std::ostringstream windowHndStr;

    mWindow->getCustomAttribute("WINDOW", &windowHnd);
    windowHndStr << windowHnd;
    pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));

    mInputManager = OIS::InputManager::createInputSystem( pl );

    mKeyboard = static_cast<OIS::Keyboard*>(mInputManager->createInputObject( OIS::OISKeyboard, true ));
    mMouse = static_cast<OIS::Mouse*>(mInputManager->createInputObject( OIS::OISMouse, true ));

    mMouse->setEventCallback(this);
    mKeyboard->setEventCallback(this);

    //Set initial mouse clipping size
    windowResized(mWindow);

    //Register as a Window listener
    Ogre::WindowEventUtilities::addWindowEventListener(mWindow, this);

    mRoot->addFrameListener(this);
}

bool BasicTutorial7::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
    if(mWindow->isClosed())
        return false;

    if(mShutDown)
        return false;

    //Need to capture/update each device
    mKeyboard->capture();
    mMouse->capture();

    //Need to inject timestamps to CEGUI System.
    CEGUI::System::getSingleton().injectTimePulse(evt.timeSinceLastFrame);

    return true;
}

bool BasicTutorial7::keyPressed( const OIS::KeyEvent &arg )
{
    CEGUI::GUIContext& context = CEGUI::System::getSingleton().getDefaultGUIContext();
    context.injectKeyDown((CEGUI::Key::Scan)arg.key);
    context.injectChar((CEGUI::Key::Scan)arg.text);

    if (arg.key == OIS::KC_ESCAPE)
    {
        mShutDown = true;
    }

    mCameraMan->injectKeyDown(arg);
    return true;
}

bool BasicTutorial7::keyReleased( const OIS::KeyEvent &arg )
{
    if(CEGUI::System::getSingleton().getDefaultGUIContext().injectKeyUp((CEGUI::Key::Scan)arg.key)) return true;
    mCameraMan->injectKeyUp(arg);
    return true;
}

CEGUI::MouseButton convertButton(OIS::MouseButtonID buttonID)
{
    switch (buttonID)
    {
    case OIS::MB_Left:
        return CEGUI::LeftButton;
        break;

    case OIS::MB_Right:
        return CEGUI::RightButton;
        break;

    case OIS::MB_Middle:
        return CEGUI::MiddleButton;
        break;

    default:
        return CEGUI::LeftButton;
        break;
    }
}

bool BasicTutorial7::mouseMoved( const OIS::MouseEvent &arg )
{
    mCameraMan->injectMouseMove(arg);
    return true;
}

bool BasicTutorial7::mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
    //if(CEGUI::System::getSingleton().injectMouseButtonUp(convertButton(id))) return true;
    mCameraMan->injectMouseDown(arg, id);
    return true;
}

bool BasicTutorial7::mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
    //if(CEGUI::System::getSingleton().injectMouseButtonUp(convertButton(id))) return true;
    mCameraMan->injectMouseUp(arg, id);
    return true;
}

bool BasicTutorial7::quit(const CEGUI::EventArgs &e)
{
    mShutDown = true;
    return true;
}
