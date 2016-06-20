#include "SceneFactory.h"
#include "../config/SceneConst.h"
#include "../../scene/start/SceneSplash.h"

namespace HsEngine
{
    Scene* SceneFactory::CreateScene (const int sceneId)
    {
        switch (sceneId)
        {
            case SCENE_SPLASH:
                return new SceneSplash ();
        }
        return nullptr;
    }
}
