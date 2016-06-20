#ifdef DEBUG

#include <iostream>
#include "Debug.h"

namespace HsEngine
{
    class Debug::DebugInfo
    {
    public:
        DebugInfo () : lastTime (0), fps (0), prevFps (0) {}
        ~DebugInfo () {}

        void UpdateFrame (const unsigned int time)
        {
            fps++;
            if (time - lastTime < 1000)
            {
                return;
            }

            prevFps = fps;
            std::cout << "[Secound Fps::" << prevFps << "][" << time << "][" << lastTime << "]" << std::endl;
            fps = 0;
            lastTime = time;
        }

        const short CurrentFps () const
        {
            return prevFps;
        }

    private:
        unsigned int lastTime;
        unsigned short fps;
        unsigned short prevFps;
    };

    Debug::Debug ()
    {
        debugInfo = new Debug::DebugInfo ();
    }

    Debug::~Debug ()
    {
        delete debugInfo;
        debugInfo = nullptr;
    }

    void Debug::UpdateFrame (const unsigned int time)
    {
        debugInfo->UpdateFrame (time);
    }

    const short Debug::SecoundFPS ()
    {
        return debugInfo->CurrentFps ();
    }
}

#endif
