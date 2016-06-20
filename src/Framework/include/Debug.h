#pragma once

#ifdef DEBUG

namespace HsEngine
{
    class Debug
    {
    public:
        Debug ();
        ~Debug ();
        void UpdateFrame (const unsigned int time);
        const short SecoundFPS ();
    private:
        class DebugInfo;
        DebugInfo* debugInfo;
    };
}

#endif
