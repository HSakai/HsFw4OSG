/*
 * カメラ設定を寄せたCameraクラス
 */
#pragma once

namespace HsEngine
{
	class Camera
	{
	public:
		Camera ();
		~Camera ();

		// 透視投影か平行投影かモード切り替え用enum
		enum CameraMode
		{
			Perspective,
			Ortho
		};

		void SetCameraMode (CameraMode mode);
	};
}
