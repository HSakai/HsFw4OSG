/*
 * キーボード入力イベントハンドラ
 */
#include <osgGA/GUIEventHandler>
#include <osgGA/GUIEventAdapter>

namespace HsEngine
{
    class KeyEventHandler : public osgGA::GUIEventHandler
    {
    public:
        virtual bool handle (const osgGA::GUIEventAdapter& ea,osgGA::GUIActionAdapter&);
    };
}
