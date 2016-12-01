//

#pragma once

#include "ModuleManager.h"

class IPushNotification : public IModuleInterface
{
public:
	static inline IPushNotification& Get()
	{
		return FModuleManager::LoadModuleChecked< IPushNotification >( "PushNotificationPlugin" );
	}

	static inline bool IsAvailable()
	{
		return FModuleManager::Get().IsModuleLoaded("PushNotificationPlugin");
	}
};