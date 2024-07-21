#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstanceProxy.h"
#include "HeliAnimInstance.generated.h"

class ARotary_Heli;
class URotary_HeliMovementComponent;
struct FRotary_RotorSetup;


struct FRotary_RotorAnimData {
	FName BoneName = EName::None;
	FRotator Rotation = FRotator::ZeroRotator;
	FVector TorqueNormal = FVector::UpVector;

	FRotary_RotorAnimData() = default;
	FRotary_RotorAnimData(FRotary_RotorSetup const& rotor);
};


USTRUCT()
struct ROTARY_API FRotary_HeliAnimInstanceProxy : public FAnimInstanceProxy {
	GENERATED_BODY()

	FRotary_HeliAnimInstanceProxy() = default;
	FRotary_HeliAnimInstanceProxy(UAnimInstance* inst) : Super(inst) {}

public:
	void SetMovementComponent(URotary_HeliMovementComponent const* mc);
	void PreUpdate(UAnimInstance* instance, float deltaTime) override;
	auto GetAnimData() const -> TArray<FRotary_RotorAnimData> const&;

private:
	inline static constexpr
	float k_RpmToRadsPerSec = 0.10472;

	TArray<FRotary_RotorAnimData> m_RotorInstances = {};
	float m_RotorSpeed = 0;
	float m_RotorAngle = 0;
};


UCLASS(Transient)
class ROTARY_API URotary_HeliAnimInstance : public UAnimInstance {
	GENERATED_BODY()

public:
	URotary_HeliAnimInstance() : Super() {}
	void SetMovementComponent(URotary_HeliMovementComponent const* mc);
	auto GetMovementComponent() const -> URotary_HeliMovementComponent const*;

private:
	FRotary_HeliAnimInstanceProxy m_Proxy = {};

	UPROPERTY(Transient, DisplayName="Movement Component")
	URotary_HeliMovementComponent const* m_MovementComponent;

	UFUNCTION(BlueprintPure, Category="Animation")
	ARotary_Heli* GetVehicle() const;

	void NativeInitializeAnimation() override;
	auto CreateAnimInstanceProxy() -> FAnimInstanceProxy* override;
	void DestroyAnimInstanceProxy(FAnimInstanceProxy* proxy) override;
};
