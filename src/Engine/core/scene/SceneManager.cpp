/*
 * シーン管理クラス実装
 */
#include "SceneManager.h"
#include "Scene.h"
#include "SceneFactory.h"

class HsEngine::SceneManager::SceneManagementParam
{
public:
	SceneManagementParam () {}
	~SceneManagementParam () {}
	const int GetSceneId () { return sceneId; }
	bool IsNext () { return moveType == SceneMoveType::Next; }
	bool IsAdd () { return moveType == SceneMoveType::Add; }
	bool IsReplace () { return moveType == SceneMoveType::Replace; }
	bool IsReturn () { return moveType == SceneMoveType::Return; }
	bool IsReturnToRoot () { return moveType == SceneMoveType::ReturnToRoot; }

	void SetNextScene (int nextSceneId)
	{
		sceneId = nextSceneId;
		moveType = SceneMoveType::Next;
	}

	void SetAddScene (int nextSceneId)
	{
		sceneId = nextSceneId;
		moveType = SceneMoveType::Add;
	}

	void SetReplaceScene (int nextSceneId)
	{
		sceneId = nextSceneId;
		moveType = SceneMoveType::Replace;
	}

	void SetReturnScene ()
	{
		sceneId = -1;
		moveType = SceneMoveType::Return;
	}

	void SetReturnToRootScene ()
	{
		sceneId = -1;
		moveType = SceneMoveType::ReturnToRoot;
	}

private:
	// シーンの遷移タイプ
	enum SceneMoveType
	{
		Next,
		Add,
		Replace,
		Return,
		ReturnToRoot
	};

	SceneMoveType moveType;
	int sceneId;
};

namespace HsEngine
{
	SceneManager* SceneManager::instance;

	void SceneManager::Initialize ()
	{
		instance = new SceneManager ();
	}

	void SceneManager::Destroy ()
	{
		delete instance;
		instance = nullptr;
	}

	SceneManager* SceneManager::GetInstance ()
	{
		return instance;
	}

	void SceneManager::OnUpdate (const uint deltaTime)
	{
		Scene* scene = rootScene;
		while (scene != nullptr)
		{
			scene->ProcessUpdate (deltaTime, (scene->GetChild () != nullptr));
			scene = scene->GetChild ();
		}
	}

	void SceneManager::OnDraw ()
	{
		Scene* scene = rootScene;
		while (scene != nullptr)
		{
			scene->ProcessDraw ((scene->GetChild () != nullptr));
			scene = scene->GetChild ();
		}
	}

	void SceneManager::OnEndOfFrame ()
	{
		ExecuteSceneManagement ();
	}

	void SceneManager::OnGameExit ()
	{
	}

	void SceneManager::ReserveNextScene (const int sceneId)
	{
		sceneMngParam = new SceneManagementParam ();
		sceneMngParam->SetNextScene (sceneId);
	}

	void SceneManager::ReserveAddScene (const int sceneId)
	{
		sceneMngParam = new SceneManagementParam ();
		sceneMngParam->SetAddScene (sceneId);
	}

	void SceneManager::ReserveReplaceScene (const int sceneId)
	{
		sceneMngParam = new SceneManagementParam ();
		sceneMngParam->SetReplaceScene (sceneId);
	}

	void SceneManager::ReserveReturnScene ()
	{
		sceneMngParam = new SceneManagementParam ();
		sceneMngParam->SetReturnScene ();
	}

	void SceneManager::ReserveReturnToRootScene ()
	{
		sceneMngParam = new SceneManagementParam ();
		sceneMngParam->SetReturnToRootScene ();
	}

	SceneManager::SceneManager ()
		: sceneMngParam (nullptr), rootScene (nullptr), currentScene (nullptr)
	{
	}

	SceneManager::~SceneManager ()
	{
#ifdef DEBUG
		const std::string logText = "called SceneManager Destruct.";
		PutLog (logText);
#endif
		// rootSceneのデストラクタで子は再帰で破棄
		delete rootScene;
		rootScene = nullptr;

		// ↑のwhileで最下層のchildまでdeleteするのでcurrentSceneは既に破棄済み
		currentScene = nullptr;

		delete sceneMngParam;
		sceneMngParam = nullptr;
	}

	void SceneManager::ExecuteSceneManagement ()
	{
		if (sceneMngParam == nullptr)
		{
			return;
		}

		Scene* scene;
		if (sceneMngParam->IsNext ())
		{
			delete rootScene;
			rootScene = nullptr;

			currentScene = SceneFactory::CreateScene (sceneMngParam->GetSceneId ());

			if (currentScene != nullptr)
			{
				currentScene->ProcessInitialize ();
				currentScene->ProcessBegin ();
			}
			
			rootScene = currentScene;
		}
		else if (sceneMngParam->IsAdd ())
		{
			currentScene = SceneFactory::CreateScene (sceneMngParam->GetSceneId ());
			currentScene->ProcessInitialize ();
			currentScene->ProcessBegin ();

			scene = rootScene;
			while (scene != nullptr
				&& scene->GetChild () != nullptr)
			{
				scene = scene->GetChild ();
			}

			scene->SetChild (currentScene);
		}
		else if (sceneMngParam->IsReplace ())
		{
			scene = rootScene->GetChild ();
			while (scene != nullptr
				&& scene->GetChild () != currentScene)
			{
				scene = scene->GetChild ();
			}

			if (scene != nullptr)
			{
				delete currentScene;
				currentScene = nullptr;

				currentScene = SceneFactory::CreateScene (sceneMngParam->GetSceneId ());
				currentScene->ProcessInitialize ();
				currentScene->ProcessBegin ();
				scene->SetChild (currentScene);
			}
		}
		else if (sceneMngParam->IsReturn ())
		{
			if (rootScene != currentScene)
			{
				scene = rootScene->GetChild ();

				// 子のポインタがcurrentSceneのポインタと一致するまで
				while (scene != nullptr
					&& scene != currentScene)
				{
					scene = scene->GetChild ();
					if (scene == nullptr)
					{
						break;
					}
				}

				if (scene != nullptr)
				{
					scene->DestroyChild ();
					currentScene = scene;
					scene->ProcessBegin ();
				}
			}
		}
		else if (sceneMngParam->IsReturnToRoot ())
		{
			scene = rootScene->GetChild ();
			delete scene;					// 子に関してはデストラクタで再帰
			rootScene->ProcessBegin ();
			currentScene = rootScene;
		}

		delete sceneMngParam;
		sceneMngParam = nullptr;
	}
}
