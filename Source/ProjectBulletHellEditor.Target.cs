using UnrealBuildTool;
using System.Collections.Generic;

public class ProjectBulletHellEditorTarget : TargetRules
{
	public ProjectBulletHellEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.Latest;
		IncludeOrderVersion = EngineIncludeOrderVersion.Latest;

		ExtraModuleNames.AddRange(new string[] { "ProjectBulletHell" });
	}
}
