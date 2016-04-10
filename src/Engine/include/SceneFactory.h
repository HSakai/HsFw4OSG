/*
 * シーン生成関数
 * 使用者側でincludeしてシーン初期化関数の実体を実装する。
 */
namespace HsEngine
{
	class Scene;
	
	namespace SceneFactory
	{
		extern Scene* CreateScene (const int sceneId);
	}
}
