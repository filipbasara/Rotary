#include "Rotary/AnimNode_RotorController.h"
#include "Rotary/HeliAnimInstance.h"

#define Self FAnimNode_Rotary_RotorController


void Self::GatherDebugData(FNodeDebugData& data)
{
	Super::GatherDebugData(data);
	// TODO
}

void Self::Initialize_AnyThread(FAnimationInitializeContext const& ctx)
{
	m_Proxy = static_cast<FRotary_HeliAnimInstanceProxy*>(ctx.AnimInstanceProxy);
}

void Self::InitializeBoneReferences(FBoneContainer const& requiredBones)
{
	auto const& data = m_Proxy->GetAnimData();
	auto len = data.Num();
	m_Rotors.Empty(len);

	for (auto i = 0; i < len; ++i) {
		auto* rotor = new (m_Rotors) FRotary_RotorLookupData { i, { data[i].BoneName }};
		rotor->BoneRef.Initialize(requiredBones);
	}

	// Sort by bone index
	m_Rotors.Sort([](FRotary_RotorLookupData const& a, FRotary_RotorLookupData const& b) -> bool {
		return a.BoneRef.BoneIndex < b.BoneRef.BoneIndex;
	});
}

auto Self::IsValidToEvaluate(
	USkeleton const* skel,
	FBoneContainer const& requiredBones)
	-> bool
{
	for (auto const& rotor : m_Rotors)
		if (rotor.BoneRef.IsValidToEvaluate(requiredBones))
			return true;

	return false;
}

void Self::EvaluateSkeletalControl_AnyThread(
	FComponentSpacePoseContext& inout_ctx,
	TArray<FBoneTransform>& out_boneTransforms)
{
	check(out_boneTransforms.Num() == 0);

	auto const& data = m_Proxy->GetAnimData();
	auto const& container = inout_ctx.Pose.GetPose().GetBoneContainer();

	for (auto const& rotor : m_Rotors) {
		if (!rotor.BoneRef.IsValidToEvaluate())
			continue;

		auto idx = rotor.BoneRef.GetCompactPoseIndex(container);
		auto xform = inout_ctx.Pose.GetComponentSpaceTransform(idx);

		FAnimationRuntime::ConvertCSTransformToBoneSpace(
			inout_ctx.AnimInstanceProxy->GetComponentTransform(),
			inout_ctx.Pose,
			xform,
			idx,
			BCS_ComponentSpace
		);

		auto q = FQuat { data[rotor.Index].Rotation };
		xform.SetRotation(q * xform.GetRotation());

		FAnimationRuntime::ConvertBoneSpaceTransformToCS(
			inout_ctx.AnimInstanceProxy->GetComponentTransform(),
			inout_ctx.Pose,
			xform,
			idx,
			BCS_ComponentSpace
		);

		out_boneTransforms.Add({ idx, xform });
	}
}


#undef Self
