// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UObject/NoExportTypes.h"

#include "AllowWindowsPlatformTypes.h"

#include "CommonMessage.h"
#include "RakNetTypes.h"
#include "RakPeerInterface.h"
#include "BitStream.h"
#include "MessageIdentifiers.h"

#include "HideWindowsPlatformTypes.h"

#include "Runtime/Core/Public/Containers/Ticker.h"
#include "RawClient.generated.h"

/**
 * Raw RakNetClient Interface
 */
UCLASS()
class UE4RAKNET_API URawClient : public UObject
{
	GENERATED_BODY()

protected:

	//RakNet½Ó¿Ú
	RakNet::RakPeerInterface* client = nullptr;
	RakNet::Packet *packet;

	/** Delegate for callbacks to Tick */
	FTickerDelegate TickDelegate;
	FDelegateHandle TickDelegateHandle;

	bool hasInit = false;

public:

	//init
	void Init();

	// tick callback
	bool Tick(float DeltaTime);

	//connect to server
	//UFUNCTION(BlueprintCallable, Category = "RakNet")
		void Connect(FString serverIP, int serverPort);

	//disconnect from server and shutdown
	//UFUNCTION(BlueprintCallable, Category = "RakNet")
		void Shutdown();

	//Connection Event Callback
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FConnectionEvent, EConnectionEvent, Response);
	UPROPERTY(BlueprintAssignable, Category = "RakNet")
		FConnectionEvent ConnectionEvent;

	//send message
	void Send(RakNet::BitStream& bsOut);

	//Message
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FResponseEvent, EResponseType, ResponseType, FString, Response);
	UPROPERTY(BlueprintAssignable, Category = "RakNet")
		FResponseEvent ResponseEvent;
};
