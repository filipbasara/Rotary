using UnrealBuildTool;

public class RotaryEditor : ModuleRules {
	public RotaryEditor(ReadOnlyTargetRules target) : base(target) {
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new [] {
			"AnimGraph",
			"Core",
			"Projects",
			"RenderCore",
			"Rotary",
		});

		PrivateDependencyModuleNames.AddRange(new [] {
			"BlueprintGraph",
			"CoreUObject",
			"Engine",
			"UnrealEd",
			"Slate",
			"SlateCore",
		});
	}
}
