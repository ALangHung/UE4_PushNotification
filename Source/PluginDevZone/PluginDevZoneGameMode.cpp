// Fill out your copyright notice in the Description page of Project Settings.

#include "PluginDevZone.h"
#include "PluginDevZoneGameMode.h"

#if PLATFORM_IOS
#import "IOSAppDelegate.h"
#include "Runtime/Engine/Classes/Kismet/KismetSystemLibrary.h"
#endif

DECLARE_LOG_CATEGORY_EXTERN(LogPluginDevZoneGameMode, Log, All);
DEFINE_LOG_CATEGORY(LogPluginDevZoneGameMode)

void APluginDevZoneGameMode::BeginPlay()
{
    Super::BeginPlay();
    
    UE_LOG(LogPluginDevZoneGameMode, Log, TEXT("%s"), *FString(__FUNCTION__));
    
#if PLATFORM_IOS
    
    FCoreDelegates::ApplicationRegisteredForRemoteNotificationsDelegate.AddUObject(this, &APluginDevZoneGameMode::ApplicationRegisteredForRemoteNotifications_Handler);
    FCoreDelegates::ApplicationFailedToRegisterForRemoteNotificationsDelegate.AddUObject(this, &APluginDevZoneGameMode::ApplicationFailedToRegisterForRemoteNotifications_Handler);
    FCoreDelegates::ApplicationReceivedRemoteNotificationDelegate.AddUObject(this, &APluginDevZoneGameMode::ApplicationReceivedRemoteNotification_Handler);
    
    UKismetSystemLibrary::RegisterForRemoteNotifications();
#endif
    
}

// Registered Remote Notifications
void APluginDevZoneGameMode::ApplicationRegisteredForRemoteNotifications_Handler(TArray<uint8> Token)
{
#if PLATFORM_IOS
    NSData* TokenData = [NSData dataWithBytes : Token.GetData() length : Token.Num()];
    NSLog(@"ApplicationRegisteredForRemoteNotifications_Handler deviceToken: %@", TokenData);
    UE_LOG(LogPluginDevZoneGameMode, Log, TEXT("%s"), *FString(__FUNCTION__));
#endif
}

void APluginDevZoneGameMode::ApplicationFailedToRegisterForRemoteNotifications_Handler(FString error)
{
#if PLATFORM_IOS
    UE_LOG(LogPluginDevZoneGameMode, Log, TEXT("%s error:%s"), *FString(__FUNCTION__), *error);
#endif
}

// Received Remote Notification
void APluginDevZoneGameMode::ApplicationReceivedRemoteNotification_Handler(FString Json)
{
#if PLATFORM_IOS
    UE_LOG(LogPluginDevZoneGameMode, Log, TEXT("%s, Json: %s"), *FString(__FUNCTION__), *Json);
#endif
}
