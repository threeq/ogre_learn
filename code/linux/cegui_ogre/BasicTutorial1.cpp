#include "BasicTutorial1.h"

BasicTutorial1::BasicTutorial1()
{
    //ctor
}

BasicTutorial1::~BasicTutorial1()
{
    //dtor
}

//-------------------------------------------------------------------------------------
void BasicTutorial1::createScene(void)
{
    // Set the scene's ambient light
    mSceneMgr->setAmbientLight(Ogre::ColourValue(0.5f, 0.5f, 0.5f));

    // Create an Entity
    Ogre::Entity* ogreHead = mSceneMgr->createEntity("Head", "ogrehead.mesh");

    // Create a SceneNode and attach the Entity to it
    Ogre::SceneNode* headNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("HeadNode");
    headNode->attachObject(ogreHead);
    headNode->yaw(Ogre::Degree(-90));

     // Create secend Entity
    Ogre::Entity* ogreHead2 = mSceneMgr->createEntity("Head2", "ogrehead.mesh");
    // Create secend SceneNode and attach the Entity to it
    Ogre::SceneNode* headNode2 = mSceneMgr->getRootSceneNode()->createChildSceneNode("HeadNode2", Ogre::Vector3( 100, 0, 0 ));
    headNode2->attachObject(ogreHead2);
    headNode2->scale(1,2,1);

    Ogre::Entity* ogreHead3 = mSceneMgr->createEntity("Head3", "ogrehead.mesh");
    Ogre::SceneNode* headNode3 = headNode->createChildSceneNode( "HeadNode3", Ogre::Vector3( 100, 0, 0 ) );
    headNode3->attachObject(ogreHead3);
    headNode->translate( Ogre::Vector3( 0, 55, 0 ) );
    headNode3->yaw(Ogre::Degree(-90));

    // Create a Light and set its position
    Ogre::Light* light = mSceneMgr->createLight("MainLight");
    light->setPosition(20.0f, 80.0f, 50.0f);
}
