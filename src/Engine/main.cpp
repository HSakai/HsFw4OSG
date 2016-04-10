/*
 * ゲーム起動関数
 * 開発時は特に気にせず設定ファイル弄くるだけにする予定。
 */
#include <iostream>
#include <SDL.h>
#include <SDL_opengl.h>
#include "Config.h"
#include "SceneManager.h"

#ifdef DEBUG
#include "Debug.h"
#endif

/*
 * SDLの各種イベント検知(ウィンドウ閉じるイベントとかキー入力イベント)
 */
bool PollSDLEvent (SDL_Event* event, SDL_Keycode& inputKey)
{
	if (!SDL_PollEvent (event))
	{
		return true;
	}

	inputKey = SDLK_UNKNOWN;

	//イベント処理
	int checkExitIdx;
	switch(event->type)
	{
		case SDL_QUIT:
			return false;
		case SDL_KEYDOWN:
			inputKey = event->key.keysym.sym;
			for (checkExitIdx = 0; checkExitIdx < HsEngine::EXIT_KEYCODE_LEN; ++checkExitIdx)
			{
				if (inputKey == HsEngine::EXIT_KEYCODES [checkExitIdx])
				{
					return false;
				}
			}
			break;
	}

	return true;
}

/*
 * OpenGLの基本設定
 */
void SetupGraphic ()
{
	glViewport (0, 0, HsEngine::WINDOW_WIDTH, HsEngine::WINDOW_HEIGHT);
	glClearColor (0.0f, 0.0f, 0.0f, 0.0f);
	glEnable (GL_DEPTH_TEST);
}

int main (int argc, char* args[])
{
	//SDLシステムを初期化します。
	if(SDL_Init (SDL_INIT_VIDEO) != 0)
	{
		//エラー情報を取得して表示、終了します。
		std::cout << "初期化失敗:" << SDL_GetError () << std::endl;
		return 1;
	}

	// ダブルバッファリング設定
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	//ウインドウ作成、設定、表示
	SDL_Window *window = SDL_CreateWindow (
		HsEngine::GAME_TITLE,
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		HsEngine::WINDOW_WIDTH,
		HsEngine::WINDOW_HEIGHT,
		SDL_WINDOW_OPENGL);

	if (!window)
	{
		std::cout << "初期化失敗: window作成" << std::endl;
		return 1;
	}

	SDL_GLContext context;
	context = SDL_GL_CreateContext(window);
	if (!context)
	{
		std::cout << "初期化失敗: window作成" << std::endl;
		return 1;
	}

	// シーン管理クラス初期化
	HsEngine::SceneManager::Initialize ();
	HsEngine::SceneManager* sceneMgr = HsEngine::SceneManager::GetInstance ();

#ifdef DEBUG
	HsEngine::Debug* debug = new HsEngine::Debug ();
#endif

	sceneMgr->ReserveNextScene (HsEngine::SceneManager::ROOT_SCENE_ID);

	unsigned int lastTime = SDL_GetTicks (), currentTime, deltaTime;
	SDL_Event event;
	SDL_Keycode inputKey;
	while(PollSDLEvent (&event, inputKey))
	{
		currentTime = SDL_GetTicks ();
		deltaTime = currentTime - lastTime;
		if (deltaTime < HsEngine::FPS_TIME)
		{
			SDL_Delay (HsEngine::FPS_TIME - deltaTime);
		}

		lastTime = SDL_GetTicks ();
		deltaTime = lastTime - currentTime;

#ifdef DEBUG
		debug->UpdateFrame (lastTime);
#endif
		// シーン管理クラスとかでフレーム更新叩く
		sceneMgr->OnUpdate (deltaTime);
		sceneMgr->OnDraw ();
		SDL_GL_SwapWindow (window);

		sceneMgr->OnEndOfFrame ();
	}

#ifdef DEBUG
	delete debug;
	debug = nullptr;
#endif

	sceneMgr->OnGameExit ();
	sceneMgr = nullptr;

	HsEngine::SceneManager::Destroy ();

	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}
