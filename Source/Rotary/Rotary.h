#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleInterface.h"


class FRotaryModule : public IModuleInterface {
public:
	/** IModuleInterface implementation */
	void StartupModule() override {}
	void ShutdownModule() override {}
};
