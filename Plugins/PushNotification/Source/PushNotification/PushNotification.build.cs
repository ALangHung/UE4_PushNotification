// 

using System.IO;

namespace UnrealBuildTool.Rules
{
	public class PushNotification : ModuleRules
	{
		public PushNotification(TargetInfo Target)
		{
            PrivateIncludePaths.AddRange(
                new string[]
                {
                    "PushNotification/Private",
                }
            );

            PrivateDependencyModuleNames.AddRange(
				new string[]
				{
                    "Engine",
					"Core"
				}
			);

           if (Target.Platform == UnrealTargetPlatform.IOS)
            {
                PublicFrameworks.AddRange(
                    new string[]
                    {
                        "CoreGraphics",
                        "Foundation",
                        "UIKit"
                    }
                );
            }
		}
	}
}
