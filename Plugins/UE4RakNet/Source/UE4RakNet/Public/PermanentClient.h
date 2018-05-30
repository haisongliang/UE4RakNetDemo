// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "RawClient.h"
#include "PermanentClient.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class UE4RAKNET_API UPermanentClient : public URawClient
{
	GENERATED_BODY()
	
	
public:
	//初始化客户端并尝试连接指定服务器
	UFUNCTION(BlueprintCallable, Category = "RakNet")
		void InitClient(FString serverIP, int serverPort);

	//客户端请求
	UFUNCTION(BlueprintCallable, Category = "RakNet")
		void SendRequest(ERequestType requestType, FString extraSettings);

	UFUNCTION(BlueprintCallable, Category = "RakNet")
		void DestroyClient();
};
