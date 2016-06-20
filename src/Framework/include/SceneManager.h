/*
 * シーン管理クラス
 */
#pragma once

#include <osgViewer/Viewer>
#include <osgGA/GUIEventAdapter>
#include "Utils.h"

namespace HsEngine
{
    class Scene;
    class SceneManager
    {
    public:
        static void Initialize ();
        static void Destroy ();
        static SceneManager* GetInstance ();
        static const int ROOT_SCENE_ID = 0;
        void OnKeyDown (const osgGA::GUIEventAdapter::KeySymbol& inputKey);
        void OnUpdate (const uint deltaTime);
        void OnDraw ();
        void OnEndOfFrame ();
        void OnGameExit ();
        void ReserveNextScene (const int sceneId);
        void ReserveAddScene (const int sceneId);
        void ReserveReplaceScene (const int sceneId);
        void ReserveReturnScene ();
        void ReserveReturnToRootScene ();
        osgViewer::Viewer* GetViewer ();
    private:
        SceneManager ();
        ~SceneManager ();
        static SceneManager* instance;
        class SceneManagementParam;
        SceneManagementParam* sceneMngParam;
        Scene* rootScene;
        Scene* currentScene;
        osgViewer::Viewer* viewer;

        /*
         * 予約されたシーンIDに紐づく遷移管理処理
         */
        void ExecuteSceneManagement ();
    };
}
