using UnrealBuildTool;

public class ProjectBulletHell : ModuleRules
{
	public ProjectBulletHell(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",

			// Gameplay Ability System
			"GameplayAbilities",
			"GameplayTags",
			"GameplayTasks"
		});

		PrivateDependencyModuleNames.AddRange(new string[]
		{
			"Slate",
			"SlateCore"
		});

		// Uncomment if/when online subsystem or networking replication features are added.
		// PrivateDependencyModuleNames.Add("NetCore");

		PublicIncludePaths.AddRange(new string[]
		{
			"ProjectBulletHell",
			"ProjectBulletHell/Core",
			"ProjectBulletHell/Player",
			"ProjectBulletHell/Abilities",
			"ProjectBulletHell/Weapons",
			"ProjectBulletHell/Movement",
			"ProjectBulletHell/UI"
		});
	}
}
