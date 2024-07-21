#pragma once

#include "CoreMinimal.h"
#include "BoneControllers/AnimNode_SkeletalControlBase.h"
#include "AnimNode_RotorController.generated.h"

struct FRotary_HeliAnimInstanceProxy;


struct FRotary_RotorLookupData {
	int32 Index;
	FBoneReference BoneRef;

	FRotary_RotorLookupData() = default;
	FRotary_RotorLookupData(int32 idx, FBoneReference const& boneRef)
		: Index(idx)
		, BoneRef(boneRef)
	{}
};


USTRUCT()
struct ROTARY_API FAnimNode_Rotary_RotorController : public FAnimNode_SkeletalControlBase {
	GENERATED_BODY()

public:
	FAnimNode_Rotary_RotorController() = default;

	void GatherDebugData(FNodeDebugData& data) override;
	void Initialize_AnyThread(FAnimationInitializeContext const& ctx) override;

	auto IsValidToEvaluate(
		USkeleton const* skel,
		FBoneContainer const& requiredBones)
		-> bool override;

	void EvaluateSkeletalControl_AnyThread(
		FComponentSpacePoseContext& inout_ctx,
		TArray<FBoneTransform>& out_boneTransforms)
		override;

private:
	FRotary_HeliAnimInstanceProxy const* m_Proxy = nullptr;
	TArray<FRotary_RotorLookupData> m_Rotors = {};

	void InitializeBoneReferences(FBoneContainer const& requiredBones) override;
};
