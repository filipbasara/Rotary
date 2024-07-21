#include "Rotary/HeliAnimInstance.h"

#include "Rotary/Heli.h"
#include "Rotary/HeliMovement.h"

#define AnimData FRotary_RotorAnimData
#define Proxy FRotary_HeliAnimInstanceProxy
#define Self URotary_HeliAnimInstance


// Animation Data --------------------------------------------------------------

AnimData::FRotary_RotorAnimData(FRotary_RotorSetup const& rotor)
	: BoneName(rotor.BoneName)
	, TorqueNormal(rotor.TorqueNormal)
{}


// Animation instance proxy ----------------------------------------------------

void Proxy::SetMovementComponent(URotary_HeliMovementComponent const* mc)
{
	auto const& rotors = mc->Rotors;
	m_RotorInstances.Empty(rotors.Num());

	for (auto const& rotor : rotors)
		m_RotorInstances.Add({ rotor });
}

void Proxy::PreUpdate(UAnimInstance* instance, float deltaTime)
{
	Super::PreUpdate(instance, deltaTime);

	auto const* inst = CastChecked<URotary_HeliAnimInstance>(instance);
	if (!inst) return;

	auto const* mc = inst->GetMovementComponent();
	if (!mc) return;

	auto deltaAngle = mc->GetCurrentRPM() * deltaTime * -k_RpmToRadsPerSec;
	m_RotorAngle = FMath::Fmod(m_RotorAngle + deltaAngle, 2 * PI);

	for (auto& rotor : m_RotorInstances)
		rotor.Rotation = FQuat(rotor.TorqueNormal, m_RotorAngle).Rotator();
}

auto Proxy::GetAnimData() const -> TArray<FRotary_RotorAnimData> const&
{
	return m_RotorInstances;
}


// Animation instance ----------------------------------------------------------

void Self::SetMovementComponent(URotary_HeliMovementComponent const* mc)
{
	m_MovementComponent = mc;
	m_Proxy.SetMovementComponent(mc);
}

auto Self::GetMovementComponent() const -> URotary_HeliMovementComponent const*
{
	return m_MovementComponent;
}

auto Self::GetVehicle() const -> ARotary_Heli*
{
	return Cast<ARotary_Heli>(GetOwningActor());
}

void Self::NativeInitializeAnimation()
{
	if (auto* actor = GetOwningActor())
		if (auto* mc = actor->FindComponentByClass<URotary_HeliMovementComponent>())
			SetMovementComponent(mc);
}

auto Self::CreateAnimInstanceProxy() -> FAnimInstanceProxy*
{
	return &m_Proxy;
}

void Self::DestroyAnimInstanceProxy(FAnimInstanceProxy* proxy)
{}


#undef Self
#undef Proxy
#undef AnimData
