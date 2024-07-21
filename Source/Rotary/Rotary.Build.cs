using UnrealBuildTool;

public class Rotary : ModuleRules {
	public Rotary(ReadOnlyTargetRules target) : base(target) {
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new [] {
			"AnimGraphRuntime",
			"Core",
			"EnhancedInput",
			"Slate",
			"SlateCore",
			"UMG",
		});

		PrivateDependencyModuleNames.AddRange(new [] {
			"CoreUObject",
			"Engine",
			"PhysicsCore",
			"RenderCore",
			"RHI",
			"RHICore",
		});
	}
}
