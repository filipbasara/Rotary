#include "Rotary/AnimGraphNode_RotorController.h"

#include "Rotary/HeliAnimInstance.h"
#include "Kismet2/BlueprintEditorUtils.h"
#include "Kismet2/CompilerResultsLog.h"

#define Self UAnimGraphNode_Rotary_RotorController
#define LOCTEXT_NAMESPACE "A3Nodes"


auto Self::GetNodeTitle(ENodeTitleType::Type type) const -> FText
{
	if (type == ENodeTitleType::ListView || type == ENodeTitleType::MenuTitle)
		return GetControllerDescription();

	return LOCTEXT("AnimGraphNode_Rotary_RotorController", "Rotor Controller");
}

auto Self::GetTooltipText() const -> FText
{
	return LOCTEXT(
		"AnimGraphNode_Rotary_RotorController_Tooltip",
		"Rotates the aircraft's rotor systems based on Heli Movement Component "
			"setup. This only works when the owner is a Heli actor."
	);
}

auto Self::IsCompatibleWithGraph(UEdGraph const* graph) const -> bool
{
	auto* bp = FBlueprintEditorUtils::FindBlueprintForGraph(graph);
	return (
		bp != nullptr
		&& bp->ParentClass->IsChildOf<URotary_HeliAnimInstance>()
		&& Super::IsCompatibleWithGraph(graph)
	);
}

void Self::ValidateAnimNodePostCompile(
	FCompilerResultsLog& msgLog,
	UAnimBlueprintGeneratedClass* compiledClass,
	int32 compiledNodeIdx)
{
	if (!compiledClass->IsChildOf<URotary_HeliAnimInstance>())
		msgLog.Error(
			TEXT("@@ is only allowed in HeliAnimInstance. Change animation "
				"blueprint parent to HeliAnimInstance to fix."),
			this
		);
}

auto Self::GetControllerDescription() const -> FText
{
	return LOCTEXT(
		"AnimGraphNode_Rotary_RotorController",
		"Rotor Controller for Rotary-Wing Aircraft"
	);
}

auto Self::GetNode() const -> FAnimNode_SkeletalControlBase const*
{
	return &m_Node;
}


#undef LOCTEXT_NAMESPACE
#undef Self
