//

#include "PushNotificationPrivatePCH.h"

#if PLATFORM_IOS
#import "IOSAppDelegate.h"
#include "Runtime/Engine/Classes/Kismet/KismetSystemLibrary.h"
#endif

DEFINE_LOG_CATEGORY(LogPushNotification);

class FPushNotification : public IPushNotification
{
public:
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
  
private:
    void ApplicationRegisteredForRemoteNotifications_Handler(TArray<uint8> Token);
    void ApplicationReceivedRemoteNotification_Handler(FString Json);
    void ApplicationFailedToRegisterForRemoteNotifications_Handler(FString error);
    
    void showmsg(FString msg);
};

IMPLEMENT_MODULE(FPushNotification, PushNotification)


void FPushNotification::StartupModule()
{
    UE_LOG(LogPushNotification, Log, TEXT("%s"), *FString(__FUNCTION__));
#if PLATFORM_IOS
    
    FCoreDelegates::ApplicationRegisteredForRemoteNotificationsDelegate.AddRaw(this, &FPushNotification::ApplicationRegisteredForRemoteNotifications_Handler);
    FCoreDelegates::ApplicationFailedToRegisterForRemoteNotificationsDelegate.AddRaw(this, &FPushNotification::ApplicationFailedToRegisterForRemoteNotifications_Handler);
    FCoreDelegates::ApplicationReceivedRemoteNotificationDelegate.AddRaw(this, &FPushNotification::ApplicationReceivedRemoteNotification_Handler);
    
    UIMutableUserNotificationAction *readAction = [[UIMutableUserNotificationAction alloc] init];
    readAction.identifier = @"READ_IDENTIFIER";
    readAction.title = @"Read";
    readAction.activationMode = UIUserNotificationActivationModeForeground;
    readAction.destructive = NO;
    readAction.authenticationRequired = YES;
    
    UIMutableUserNotificationAction *ignoreAction = [[UIMutableUserNotificationAction alloc] init];
    ignoreAction.identifier = @"IGNORE_IDENTIFIER";
    ignoreAction.title = @"Ignore";
    ignoreAction.activationMode = UIUserNotificationActivationModeBackground;
    ignoreAction.destructive = NO;
    ignoreAction.authenticationRequired = NO;
    
    UIMutableUserNotificationAction *deleteAction = [[UIMutableUserNotificationAction alloc] init];
    deleteAction.identifier = @"DELETE_IDENTIFIER";
    deleteAction.title = @"Delete";
    deleteAction.activationMode = UIUserNotificationActivationModeForeground;
    deleteAction.destructive = YES;
    deleteAction.authenticationRequired = YES;
    
    UIMutableUserNotificationCategory *messageCategory = [[UIMutableUserNotificationCategory alloc] init];
    messageCategory.identifier = @"MESSAGE_CATEGORY";
    [messageCategory setActions:@[readAction, ignoreAction, deleteAction] forContext:UIUserNotificationActionContextDefault];
    [messageCategory setActions:@[readAction, deleteAction] forContext:UIUserNotificationActionContextMinimal];
    
    NSSet *categories = [NSSet setWithObject:messageCategory];
    
    UIUserNotificationType types = UIUserNotificationTypeBadge | UIUserNotificationTypeSound | UIUserNotificationTypeAlert;
    UIUserNotificationSettings *mySettings = [UIUserNotificationSettings settingsForTypes:types categories:categories];
    
    [[UIApplication sharedApplication] registerUserNotificationSettings:mySettings];
    [[UIApplication sharedApplication] registerForRemoteNotifications];
    
    IOSAppDelegate* appDelegate = (IOSAppDelegate*)[[UIApplication sharedApplication] delegate];
    if(appDelegate.launchOptions!=nil){
        UE_LOG(LogPushNotification, Log, TEXT("%s  appDelegate.launchOptions!=nil"), *FString(__FUNCTION__));
        NSString *msg = [NSString stringWithFormat:@"%@", appDelegate.launchOptions];
        NSLog(@"%@",msg);
        showmsg(msg);
    }
    
    UKismetSystemLibrary::RegisterForRemoteNotifications();
#endif
}

void FPushNotification::ShutdownModule()
{
	UE_LOG(LogPushNotification, Log, TEXT("%s"), *FString(__FUNCTION__));
}


// Registered Remote Notifications
void FPushNotification::ApplicationRegisteredForRemoteNotifications_Handler(TArray<uint8> Token)
{
#if PLATFORM_IOS
    NSData* TokenData = [NSData dataWithBytes : Token.GetData() length : Token.Num()];
    NSLog(@"deviceToken: %@", TokenData);
    UE_LOG(LogPushNotification, Log, TEXT("%s"), *FString(__FUNCTION__));
#endif
}

void FPushNotification::ApplicationFailedToRegisterForRemoteNotifications_Handler(FString error)
{
#if PLATFORM_IOS
    UE_LOG(LogPushNotification, Log, TEXT("%s error:%s"), *FString(__FUNCTION__), *error);
#endif
}

// Received Remote Notification
void FPushNotification::ApplicationReceivedRemoteNotification_Handler(FString Json)
{
#if PLATFORM_IOS
    UE_LOG(LogPushNotification, Log, TEXT("%s, Json: %s"), *FString(__FUNCTION__), *Json);
    showmsg(Json);
#endif
}



void FPushNotification::showmsg(FString msg)
{
#if PLATFORM_IOS
    UIAlertView *alertView = [[UIAlertView alloc] initWithTitle:@"Message Received" message:[NSString stringWithFormat:@"%@", msg.GetNSString()]delegate:[[UIApplication sharedApplication] delegate] cancelButtonTitle:@"OK" otherButtonTitles:nil];
    [alertView show];
#endif
}
