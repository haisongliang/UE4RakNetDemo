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
	//��ʼ���ͻ��˲���������ָ��������
	UFUNCTION(BlueprintCallable, Category = "RakNet")
		void InitClient(FString serverIP, int serverPort);

	//�ͻ�������
	UFUNCTION(BlueprintCallable, Category = "RakNet")
		void SendRequest(ERequestType requestType, FString extraSettings);

	UFUNCTION(BlueprintCallable, Category = "RakNet")
		void DestroyClient();
};
