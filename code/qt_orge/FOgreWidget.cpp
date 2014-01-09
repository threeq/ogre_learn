#include "FOgreWidget.h"
#include <QKeyEvent>
#include <string>
using namespace std ;
FOgreWidget::FOgreWidget(QWidget *parent,QString strInsName) :
    QWidget(parent),m_strInsName_(strInsName)
{
    m_pSceneManager = 0 ;
    m_pRenderWindow= 0 ;
    m_pDefCamera= 0 ;
    m_pDefViewport= 0 ;
    m_pRoot = 0 ;
    m_pMainEnt= 0 ;
    m_pMainNode= 0 ;
    m_pMainLight = 0 ;
    setFocusPolicy(Qt::StrongFocus);
}

FOgreWidget::~FOgreWidget()
{
// destroy Viewport and RenderWindow
    if( m_pDefViewport )
    {
        m_pRenderWindow->removeViewport(m_pDefViewport->getZOrder());
        m_pDefViewport = 0 ;
    }

    Ogre::Root::getSingleton().detachRenderTarget(m_pRenderWindow);
    m_pRenderWindow = 0 ;
}

void FOgreWidget::paintEvent(QPaintEvent *evt)
{
    Q_UNUSED(evt);
    updateDraw() ;
}
void FOgreWidget::timerEvent(QTimerEvent *evt)
{
    Q_UNUSED(evt);
    updateDraw() ;
}
void FOgreWidget::resizeEvent(QResizeEvent *evt)
{
    QWidget::resizeEvent(evt) ;
}
void FOgreWidget::keyPressEvent(QKeyEvent *evt)
{
    std::cout <<"enter key: " << std::endl;
    if(m_pMainEnt  !=  NULL  &&  m_pMainNode  !=  NULL){
        switch(evt->key()){
        case  Qt::Key_W:
        case  Qt::Key_Up:
            rotX  =  -0.1;
            m_pMainNode->pitch(Ogre::Radian(rotX));
            break;
        case  Qt::Key_S:
        case  Qt::Key_Down:
            rotX  =  0.1;
            m_pMainNode->pitch(Ogre::Radian(rotX));
            break;
        case  Qt::Key_A:
        case  Qt::Key_Left:
            rotY  =  -0.1;
            m_pMainNode->yaw(Ogre::Radian(rotY));
            break;
        case  Qt::Key_D:
        case  Qt::Key_Right:
            rotY  =  0.1;
            m_pMainNode->yaw(Ogre::Radian(rotY));
            break;
        }
    }
	else
	{
		QWidget::keyPressEvent(evt);
	}

}

void FOgreWidget::mousePressEvent(QMouseEvent *evt)
{
    std::cout <<"moue press" << std::endl;
    QWidget::mousePressEvent(evt);
    if(evt->button()  ==  Qt::LeftButton)
        mouseLeftPressed  =  true;
    if(evt->button()  ==  Qt::RightButton){
        mouseRightPressed  =  true;
        mousePos  =  Ogre::Vector2(evt->x(),  evt->y());
    }
    if(evt->button()  ==  Qt::MidButton)
        mouseMiddleBtn  =  true;
}

void FOgreWidget::mouseMoveEvent(QMouseEvent* evt)
{
    std::cout <<"moue move" << std::endl;
    QWidget::mouseMoveEvent(evt);
}

void FOgreWidget::wheelEvent(QWheelEvent *evt)
{
    QWidget::wheelEvent(evt) ;
}

bool FOgreWidget::LoadPlugin()
{
    assert(m_pRoot!=0) ;
#if defined(_DEGUG) || defined(DEBUG)
// Load D3D9 Render System(debug)
    m_pRoot->loadPlugin("RenderSystem_Direct3D9_d");
// Load OpenGL Render System(debug)
    m_pRoot->loadPlugin("RenderSystem_GL_d");
// Load partical system(debug)
    m_pRoot->loadPlugin("Plugin_ParticleFX_d");
// Load octree
    m_pRoot->loadPlugin("Plugin_OctreeSceneManager_d");
#else
// Load D3D9 Render System
    //m_pRoot->loadPlugin("RenderSystem_Direct3D9");
// Load OpenGL Render System
    m_pRoot->loadPlugin("RenderSystem_GL");
// Load partical system
    m_pRoot->loadPlugin("Plugin_ParticleFX");
// Load octree
    m_pRoot->loadPlugin("Plugin_OctreeSceneManager");
#endif
    return true;
}

bool FOgreWidget::LoadResource()
{
// Load resource paths from config file
    Ogre::ConfigFile cf;
    cf.load("config/resources.cfg");
// Go through all sections & settings in the file
    Ogre::ConfigFile::SectionIterator seci = cf.getSectionIterator();
    Ogre::String secName, typeName, archName;

    while (seci.hasMoreElements())
    {
        secName = seci.peekNextKey();
        Ogre::ConfigFile::SettingsMultiMap *settings = seci.getNext();
        Ogre::ConfigFile::SettingsMultiMap::iterator i;

        for(i = settings->begin(); i != settings->end(); ++i)
        {
            typeName = i->first;
            archName = i->second;
            Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
                archName, typeName, secName);
        }
    }

    return true;
}
bool FOgreWidget::CreateSceneManager()
{
    assert(m_pRoot);
    m_pSceneManager = m_pRoot->createSceneManager(Ogre::ST_INTERIOR);
    //LogManager::getSingleton().
    return true;
}
bool FOgreWidget::CreateDefaultCamera()
{
    assert(m_pRoot);
    assert(m_pSceneManager);
    assert(m_pRenderWindow);
//m_pDefCamera = m_pSceneManager->createCamera(strName);
    m_pDefCamera = m_pSceneManager->createCamera("MyCamera");
    m_pDefCamera->setPosition(Ogre::Vector3(100,100,100));
    m_pDefCamera->lookAt(Ogre::Vector3(0,0,0));
    m_pDefCamera->setNearClipDistance(90);
    m_pDefCamera->setFarClipDistance(1000);
    m_pDefViewport = m_pRenderWindow->addViewport(m_pDefCamera);
    m_pDefViewport->setBackgroundColour(Ogre::ColourValue(0, 0.0, 255.0, 1));
    m_pDefCamera->setAspectRatio(Ogre::Real(m_pDefViewport->getActualWidth()) / Ogre::Real(m_pDefViewport->getActualHeight()));

// Make window active and post an update
    m_pRenderWindow->setActive(true);
    m_pRenderWindow->update();
    return true;
}
// Create Render Window
bool FOgreWidget::CreateRenderWindow()
{
    assert(m_pRoot);

    QWidget *q_parent = dynamic_cast <QWidget *> ( parent() );
    Ogre::NameValuePairList params;
#ifdef Q_WS_X11
    // Get the parameters of the window QT created
    QX11Info info = x11Info();
    Ogre::String winHandle;
    winHandle  = Ogre::StringConverter::toString((unsigned long)(info.display()));
    winHandle += ":";
    winHandle += Ogre::StringConverter::toString((unsigned int)(info.screen()));
    winHandle += ":";

    assert( q_parent );

    winHandle += Ogre::StringConverter::toString( (unsigned long) q_parent->winId() );

    params["parentWindowHandle"] = winHandle;
#endif
#ifdef _WIN32

    if (q_parent)
        params["parentWindowHandle"] = Ogre::StringConverter::toString( ( unsigned long ) q_parent->winId() );
    else
        params["parentWindowHandle"] = Ogre::StringConverter::toString( ( unsigned long ) GetDesktopWindow );

#endif
    // Create Ogre render window
    string strName  ;
    strName = m_strInsName_.toStdString() ;
    strName += "_Window" ;
    m_pRenderWindow = m_pRoot->createRenderWindow( strName,
                      this->width(),
                      this->height(),
                      false,
                      &params );

    m_pRenderWindow->setActive( true );
    m_pRenderWindow->resize(width(), height());
    m_pRenderWindow->setVisible( true );

    // Get the ID of Ogre render window
    WId window_id;
    m_pRenderWindow->getCustomAttribute( "WINDOW", &window_id );
    assert( window_id );

    // Take over the ogre created window.
    QWidget::create( window_id );

    resizeEvent( NULL );

    setAttribute( Qt::WA_PaintOnScreen );
    //setAttribute( Qt::WA_NoSystemBackground );
    //setAttribute( Qt::WA_NoBackground );
    //setAttribute( Qt::WA_NativeWindow );
    setAttribute( Qt::WA_OpaquePaintEvent );

    if(m_pRenderWindow == 0) return false;

    return true;
}

bool FOgreWidget::Initialize( )
{
// already inited
    if(m_pRoot!= 0) return true ;

    if(Ogre::Root::getSingletonPtr() == 0)
    {
        // create scene root with no config file and plugin
        //m_pRoot = new Root("");
        m_pRoot = new Ogre::Root("config/plugins.cfg", "config/ogre.cfg", "logs/Ogre.log");
        // Load plugin
        //FALSE_RETURN( LoadPlugin(), false );
        // Select Render System
        FALSE_RETURN( SelectRenderSystem(), false );
        m_pRoot->initialise(false);
        // Load Resource
        FALSE_RETURN( LoadResource(), false );
    }
    else
    {
        m_pRoot = Ogre::Root::getSingletonPtr();
    }

// Create Render Window
    FALSE_RETURN( CreateRenderWindow(), false );
// Create Scene Manager
    FALSE_RETURN( CreateSceneManager(), false );
// Create Default Camera and Viewport
    FALSE_RETURN( CreateDefaultCamera(), false );
    Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
// Create Scene
    FALSE_RETURN( CreateScene(), false );
    CreateLight() ;
    startTimer(2);
    return false ;
}

// Select Render System
bool FOgreWidget::SelectRenderSystem()
{
    if(!m_pRoot->restoreConfig())
    {
        // If returned true, user clicked OK so initialise
        // Here we choose to let the system create a default rendering window by passing 'true'
        if(!m_pRoot->showConfigDialog()) {
            exit(0);
        }
    }
    m_pRoot->saveConfig();
    return true;
}

bool FOgreWidget::CreateScene()
{
    string strName  ;
    strName = m_strInsName_.toStdString() ;
    strName += ".mesh" ;
    m_pMainEnt = m_pSceneManager->createEntity("root_mesh", strName);
    m_pMainNode = m_pSceneManager->getRootSceneNode()->createChildSceneNode();
    m_pMainNode->attachObject(m_pMainEnt);
    return true ;
}
void FOgreWidget::updateDraw()
{
    if(m_pRenderWindow != 0)
    {
        //std::cout<<"I'm "<<m_strInsName_.toStdString()<<"\n";
        m_pRoot->_fireFrameStarted();
        m_pRenderWindow->update();
        //m_pDefCamera->moveRelative(mDirection);
        //float xClient = 0.001;
        //if(m_x!=0) {
        //    xClient = 1.0/m_x;
        //    std::cout<<m_x<< " : " << xClient<<"\n";
        //}
        //m_pDefCamera->yaw(Ogre::Radian(xClient));
        //m_pDefCamera->pitch(Ogre::Radian(m_y));
        m_pRoot->_fireFrameEnded();
    }
}

// 设置环境光
void FOgreWidget::CreateLight()
{
    m_pSceneManager->setAmbientLight(Ogre::ColourValue(0.9, 0.5, 0.5));
    m_pMainLight = m_pSceneManager->createLight("mainLight");
    m_pMainLight->setPosition(200,200,400);
}

#include "FOgreWidget.moc"
