#ifndef BASICTUTORIAL4_H
#define BASICTUTORIAL4_H

#include "BaseApplication.h"

class BasicTutorial4 : public BaseApplication
{
public:
    BasicTutorial4();
    virtual ~BasicTutorial4();
protected:

    /** @brief (one liner)
      *
      * (documentation goes here)
      */
    virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);
    /** @brief (one liner)
      *
      * (documentation goes here)
      */
    virtual void createScene(void);
private:

    bool processUnbufferedInput(const Ogre::FrameEvent& evt);
};

#endif // BASICTUTORIAL4_H
