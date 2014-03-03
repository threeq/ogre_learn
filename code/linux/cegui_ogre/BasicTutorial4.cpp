#include "BasicTutorial4.h"

BasicTutorial4::BasicTutorial4()
{
    //ctor
}

BasicTutorial4::~BasicTutorial4()
{
    //dtor
}

//-----------------------------------------------------
void BasicTutorial4::createScene()
{
    // 设置环境灯光
    mSceneMgr->setAmbientLight(Ogre::ColourValue(0.25, 0.25, 0.25));
    //加入entity
    Ogre::Entity* ninjaEntity = mSceneMgr->createEntity("Ninja", "ninja.mesh");
    Ogre::SceneNode* node = mSceneMgr->getRootSceneNode()->createChildSceneNode("NinjaNode");
    node->attachObject(ninjaEntity);

    Ogre::Light* pointLight = mSceneMgr->createLight("pointLight");
    pointLight->setType(Ogre::Light::LT_POINT);
    pointLight->setPosition(Ogre::Vector3(250, 150, 250));
    pointLight->setDiffuseColour(Ogre::ColourValue::White);
    pointLight->setSpecularColour(Ogre::ColourValue::White);

    mCamera->setPosition(Ogre::Vector3(250, 150, -250));
    mCamera->setDirection(Ogre::Vector3(-555, 150-100, 300));
}

//------------------------------------------------------
bool BasicTutorial4::processUnbufferedInput(const Ogre::FrameEvent& evt)
{
    static bool mMouseDown = false;     // If a mouse button is depressed
    static Ogre::Real mToggle = 0.0;    // The time left until next toggle
    static Ogre::Real mRotate = 0.13;   // The rotate constant
    static Ogre::Real mMove = 250;      // The movement constant

    bool currMouse = mMouse->getMouseState().buttonDown(OIS::MB_Left);

    if (currMouse && ! mMouseDown)
    {
        Ogre::Light* light = mSceneMgr->getLight("pointLight");
        light->setVisible(! light->isVisible());
    }

    mMouseDown = currMouse;

    mToggle -= evt.timeSinceLastFrame;

    if ((mToggle < 0.0f ) && mKeyboard->isKeyDown(OIS::KC_1))
    {
        mToggle  = 0.5;
        Ogre::Light* light = mSceneMgr->getLight("pointLight");
        light->setVisible(! light->isVisible());
    }

    Ogre::Vector3 transVector = Ogre::Vector3::ZERO;

    if (mKeyboard->isKeyDown(OIS::KC_I)) // Forward
    {
        transVector.z -= mMove;
    }
    if (mKeyboard->isKeyDown(OIS::KC_K)) // Backward
    {
        transVector.z += mMove;
    }
    if (mKeyboard->isKeyDown(OIS::KC_J)) // Left - yaw or strafe
    {
        if(mKeyboard->isKeyDown( OIS::KC_LSHIFT ))
        {
            // Yaw left
            mSceneMgr->getSceneNode("NinjaNode")->yaw(Ogre::Degree(mRotate * 5));
        } else {
            transVector.x -= mMove; // Strafe left
        }
    }
    if (mKeyboard->isKeyDown(OIS::KC_L)) // Right - yaw or strafe
    {
        if(mKeyboard->isKeyDown( OIS::KC_LSHIFT ))
        {
            // Yaw right
            mSceneMgr->getSceneNode("NinjaNode")->yaw(Ogre::Degree(-mRotate * 5));
        } else {
            transVector.x += mMove; // Strafe right
        }
    }
    if (mKeyboard->isKeyDown(OIS::KC_U)) // Up
    {
        transVector.y += mMove;
    }
    if (mKeyboard->isKeyDown(OIS::KC_O)) // Down
    {
        transVector.y -= mMove;
    }

    mSceneMgr->getSceneNode("NinjaNode")->translate(transVector * evt.timeSinceLastFrame, Ogre::Node::TS_LOCAL);

    return true;
}

//----------------------------------------------------------
bool BasicTutorial4::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
    bool ret = BaseApplication::frameRenderingQueued(evt);
    if(!processUnbufferedInput(evt)) return false;
    return ret;
}
