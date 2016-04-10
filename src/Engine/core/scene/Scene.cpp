#include "Scene.h"
#include "SceneManager.h"

#ifdef DEBUG
#include "Utils.h"
#endif

namespace HsEngine
{
	Scene::Scene () : childScene (nullptr)
	{
	}

	Scene::~Scene ()
	{
		if (childScene != nullptr)
		{
			delete childScene;
			childScene = nullptr;
		}
	}

	Scene* Scene::operator=(Scene* scene)
	{
		return scene;
	}

	void Scene::IsKeyDown (const SDL_Keycode& inputKey)
	{
	}

	void Scene::ProcessInitialize ()
	{
	}

	void Scene::ProcessBegin ()
	{
	}

	void Scene::ProcessUpdate (const uint deltaTime, const bool isEnterChild)
	{
	}

	void Scene::ProcessDraw (const bool isEnterChild)
	{
	}

	void Scene::JumpScene (const int sceneId)
	{
		SceneManager::GetInstance ()->ReserveNextScene (sceneId);
	}

	void Scene::CallScene (const int sceneId)
	{
		SceneManager::GetInstance ()->ReserveReplaceScene (sceneId);
	}

	void Scene::ReturnScene ()
	{
		SceneManager::GetInstance ()->ReserveReturnScene ();
	}

	void Scene::ReturnToRootScene ()
	{
		SceneManager::GetInstance ()->ReserveReturnToRootScene ();
	}

	Scene* Scene::GetChild ()
	{
		return childScene;
	}

	void Scene::SetChild (Scene* scene)
	{
#ifdef DEBUG
		if (childScene != nullptr)
		{
			const std::string logText = "already set child !!";
			PutLog (logText);
		}
#endif
		if (scene == nullptr)
		{
#ifdef DEBUG
			const std::string logText = "scene is nullptr !! so, return this method.";
			PutLog (logText);
#endif
			return;
		}

		if (childScene != nullptr)
		{
			DestroyChild ();
		}

		childScene = scene;
	}

	void Scene::DestroyChild ()
	{
		if (childScene == nullptr)
		{
			return;
		}

		delete childScene;
		childScene = nullptr;
	}
}
