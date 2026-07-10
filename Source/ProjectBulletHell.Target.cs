using UnrealBuildTool;
using System.Collections.Generic;

public class ProjectBulletHellTarget : TargetRules
{
	public ProjectBulletHellTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.Latest;
		IncludeOrderVersion = EngineIncludeOrderVersion.Latest;

		ExtraModuleNames.AddRange(new string[] { "ProjectBulletHell" });
	}
}
