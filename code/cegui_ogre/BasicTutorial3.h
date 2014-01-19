#ifndef BASICTUTORIAL3_H
#define BASICTUTORIAL3_H

#include <Terrain/OgreTerrain.h>
#include <Terrain/OgreTerrainGroup.h>
#include "BaseApplication.h"


class BasicTutorial3 : public BaseApplication
{
    public:
        BasicTutorial3();
        virtual ~BasicTutorial3();
    protected:
        virtual void createScene(void);
        virtual void createFrameListener(void);
        virtual void destroyScene(void);
        virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);
    private:
        Ogre::TerrainGlobalOptions* mTerrainGlobals;
        Ogre::TerrainGroup* mTerrainGroup;
        bool mTerrainsImported;
        OgreBites::Label* mInfoLabel;

        void defineTerrain(long x, long y);
        void initBlendMaps(Ogre::Terrain* terrain);
        void configureTerrainDefaults(Ogre::Light* light);
};

#endif // BASICTUTORIAL3_H
