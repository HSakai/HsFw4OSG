/*
 * シーン管理クラス
 */
#pragma once

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
		void OnUpdate (const uint deltaTime);
		void OnDraw ();
		void OnEndOfFrame ();
		void OnGameExit ();
		void ReserveNextScene (const int sceneId);
		void ReserveAddScene (const int sceneId);
		void ReserveReplaceScene (const int sceneId);
		void ReserveReturnScene ();
		void ReserveReturnToRootScene ();
	private:
		SceneManager ();
		~SceneManager ();
		static SceneManager* instance;
		class SceneManagementParam;
		SceneManagementParam* sceneMngParam;
		Scene* rootScene;
		Scene* currentScene;

		/*
		 * 予約されたシーンIDに紐づく遷移管理処理
		 */
		void ExecuteSceneManagement ();
	};
}
