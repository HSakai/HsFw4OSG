#pragma once

#include "Scene.h"

class SceneSplash : public HsEngine::Scene
{
public:
    SceneSplash ();
    virtual ~SceneSplash ();
    void ProcessUpdate (const uint deltaTime, const bool isEnterChild) override;
};
