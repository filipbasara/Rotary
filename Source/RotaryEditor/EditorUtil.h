#pragma once

#include "CoreMinimal.h"


namespace Rotary::Editor::Util {

template <typename T>
auto LoadAsset(FName const& referenceName) -> T*
{
	return Cast<T>(StaticLoadObject(T::StaticClass(), nullptr, *referenceName.ToString()));
}

} // namespace Rotary::Editor::Util
