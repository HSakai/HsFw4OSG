/*
 * ゲーム起動関数
 * 開発時は特に気にせず設定ファイル弄くるだけにする予定。
 */
#include <iostream>
#include <osg/Timer>
#include <osgGA/EventQueue>
#include "Config.h"
#include "SceneManager.h"

#ifdef DEBUG
#include "Debug.h"
#endif

int main (int argc, char* args[])
{
    // シーン管理クラス初期化
    HsEngine::SceneManager::Initialize ();
    HsEngine::SceneManager* sceneMgr = HsEngine::SceneManager::GetInstance ();

#ifdef DEBUG
    HsEngine::Debug* debug = new HsEngine::Debug ();
#endif

    sceneMgr->ReserveNextScene (HsEngine::SceneManager::ROOT_SCENE_ID);

    osg::ref_ptr<osgGA::EventQueue> eventQueue = new osgGA::EventQueue(osgGA::GUIEventAdapter::Y_INCREASING_UPWARDS);

    osg::Timer_t startTick = osg::Timer::instance()->tick();
    eventQueue->setStartTick(startTick);

    osgViewer::Viewer* viewer = HsEngine::SceneManager::GetInstance ()->GetViewer ();
    double deltaTime = 0, elapsedTime = 0, lastTime = 0;
    while (!viewer->done())
    {
        viewer->frame ();
        elapsedTime = viewer->elapsedTime () * 1000;
        deltaTime = elapsedTime - lastTime;
        if (deltaTime < HsEngine::FPS_TIME)
        {
            continue;
        }
        lastTime = elapsedTime;

#ifdef DEBUG
        debug->UpdateFrame (static_cast<unsigned int> (osg::Timer::instance()->time_s () * 1000));
#endif

        // シーン管理クラスとかでフレーム更新叩く
        sceneMgr->OnUpdate (deltaTime);
        sceneMgr->OnDraw ();

        sceneMgr->OnEndOfFrame ();
    }

#ifdef DEBUG
    delete debug;
    debug = nullptr;
#endif

    sceneMgr->OnGameExit ();
    sceneMgr = nullptr;

    HsEngine::SceneManager::Destroy ();

    return 0;
}
