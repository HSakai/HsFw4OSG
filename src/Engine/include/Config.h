/*
 * ゲームの全体的な設定
 */
#pragma once

#include <SDL.h>

namespace HsEngine
{
	// ゲームタイトル
	extern const char* GAME_TITLE;

	// 設定FPS
	extern const char TARGET_FPS;

	// 1フレームあたりの更新時間
	const short FPS_TIME = 1000 / TARGET_FPS;

	// 画面基準幅
	extern const short WINDOW_WIDTH;

	// 画面基準高さ
	extern const short WINDOW_HEIGHT;

	// キーボード入力でのゲーム終了ショートカット登録
	extern const SDL_Keycode EXIT_KEYCODES[];

	// keyCode配列長
	extern const unsigned EXIT_KEYCODE_LEN;
}
