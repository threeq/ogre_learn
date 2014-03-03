#ifndef FOGREWIDGET_H
#define FOGREWIDGET_H

#include <QWidget>
#include <QX11Info>

// 如果为假就返回
#ifndef FALSE_RETURN
#define FALSE_RETURN(h, r) if(!h) return r;
#endif
#ifndef _DEGUG
#define _DEGUG
#endif
#include <QEvent>
#include <Ogre.h>
#include <OgreConfigFile.h>

class FOgreWidget : public QWidget
{
        Q_OBJECT
    public:
        FOgreWidget(QWidget *parent ,QString strInsName);
        ~FOgreWidget();
//QSize minimumSizeHint() const;
//QSize sizeHint() const;
    protected:

// 事件处理函数
        void resizeEvent(QResizeEvent *evt);//窗口可能缩放

        void timerEvent(QTimerEvent *evt);//可以设一时钟来更新窗口

        void paintEvent(QPaintEvent *evt);//呵，当然得处理了

        virtual void keyPressEvent(QKeyEvent *evt);
//void keyReleaseEvent(QKeyEvent* evt);

        void mousePressEvent(QMouseEvent *evt) ;

//void mouseReleaseEvent(QMouseEvent* evt);
        void mouseMoveEvent(QMouseEvent* evt);

        void wheelEvent(QWheelEvent *evt);

        bool LoadPlugin() ;
        bool LoadResource() ;
        bool CreateSceneManager() ;
        bool CreateRenderWindow() ;
        bool CreateDefaultCamera() ;
        bool SelectRenderSystem() ;
        bool CreateScene()  ;

        void updateDraw() ;
        void CreateLight() ;

        Ogre::SceneManager *m_pSceneManager ;
        Ogre::RenderWindow *m_pRenderWindow;
        Ogre::Camera *m_pDefCamera;
        Ogre::Viewport *m_pDefViewport;
        Ogre::Root *m_pRoot ;
        Ogre::Entity   *m_pMainEnt;
        Ogre::SceneNode   *m_pMainNode;
        Ogre::Light *m_pMainLight;
    public :
        bool Initialize() ;
    private:
        QString  m_strInsName_ ;
        float rotX, rotY;
        Ogre::Vector2 mousePos;
        bool mouseLeftPressed,mouseRightPressed,mouseMiddleBtn;
};

#endif // FOGREWIDGET_H
