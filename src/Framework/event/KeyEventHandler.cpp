#include "KeyEventHandler.h"
#include "SceneManager.h"
#include <iostream>
namespace HsEngine
{
    bool KeyEventHandler::handle (const osgGA::GUIEventAdapter& ea,osgGA::GUIActionAdapter&)
    {
        switch (ea.getEventType())
        {
            case osgGA::GUIEventAdapter::KEYDOWN:
                SceneManager::GetInstance ()->OnKeyDown ((osgGA::GUIEventAdapter::KeySymbol)ea.getKey ());
                break;
        }
        return true;
    }
}
