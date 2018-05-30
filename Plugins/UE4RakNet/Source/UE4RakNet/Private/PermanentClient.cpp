// Fill out your copyright notice in the Description page of Project Settings.

#include "UE4RakNet.h"
#include "PermanentClient.h"
#include "Runtime/Core/Public/Containers/StringConv.h"

void UPermanentClient::InitClient(FString serverIP, int serverPort)
{
	Init();

	Connect(serverIP, serverPort);
}

void UPermanentClient::SendRequest(ERequestType requestType, FString extraSettings)
{
	RakNet::BitStream bsOut;
	bsOut.Write((RakNet::MessageID)ID_GAME_MESSAGE_DEMO);
	bsOut.Write((unsigned char)requestType);
	bsOut.Write(TCHAR_TO_UTF8(*extraSettings));
	Send(bsOut);
}

void UPermanentClient::DestroyClient()
{
	Shutdown();
}
