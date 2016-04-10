/*
 * シーンのベースとなるIF
 */
#pragma once

#include <SDL.h>

namespace HsEngine
{
	class Scene
	{
	public:
		Scene ();
		virtual ~Scene ();
		Scene* operator=(Scene* scene);
		virtual void IsKeyDown (const SDL_Keycode& inputKey);
		virtual void ProcessInitialize ();
		virtual void ProcessBegin ();
		virtual void ProcessUpdate (const uint deltaTime, const bool isEnterChild);
		virtual void ProcessDraw (const bool isEnterChild);
		Scene* GetChild ();
		void SetChild (Scene* scene);
		void DestroyChild ();
	protected:
		void JumpScene (const int sceneId);
		void CallScene (const int sceneId);
		void ReturnScene ();
		void ReturnToRootScene ();
	private:
		Scene* childScene;
	};
}
