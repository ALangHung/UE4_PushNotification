// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameMode.h"
#include "PluginDevZoneGameMode.generated.h"

/**
 * 
 */
UCLASS()
class PLUGINDEVZONE_API APluginDevZoneGameMode : public AGameMode
{
	GENERATED_BODY()
	
	virtual void BeginPlay() override;
	
    UFUNCTION()
    void ApplicationRegisteredForRemoteNotifications_Handler(TArray<uint8> Token);
    
    UFUNCTION()
    void ApplicationFailedToRegisterForRemoteNotifications_Handler(FString error);
    
    UFUNCTION()
    void ApplicationReceivedRemoteNotification_Handler(FString Json);
    
};
