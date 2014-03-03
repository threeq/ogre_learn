#ifndef BASICTUTORIAL2_H
#define BASICTUTORIAL2_H

#include "BaseApplication.h"


class BasicTutorial2 : public BaseApplication
{
    public:
        BasicTutorial2();
        virtual ~BasicTutorial2();
    protected:
        virtual void createScene(void);
        virtual void createCamera(void);
        virtual void createViewports(void);

    private:
};

#endif // BASICTUTORIAL2_H
