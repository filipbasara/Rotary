#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleInterface.h"


class FRotaryEditorModule : public IModuleInterface {
public:
	void StartupModule() override;
	void ShutdownModule() override;
};
