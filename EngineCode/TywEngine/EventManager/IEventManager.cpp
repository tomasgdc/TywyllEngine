#include <stdafx.h>
#include "MultiCore\CriticalSection.h"
#include "IEventManager.h"



GenericObjectFactory<IEventData, EventType> g_eventFactory;

IEventManager::IEventManager()
{

}


IEventManager::~IEventManager()
{

}