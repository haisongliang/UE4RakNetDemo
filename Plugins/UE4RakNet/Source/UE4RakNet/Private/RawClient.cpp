// Fill out your copyright notice in the Description page of Project Settings.

#include "UE4RakNet.h"
#include "RawClient.h"


void URawClient::Init()
{
	if (!hasInit)
	{
		TickDelegate = FTickerDelegate::CreateUObject(this, &URawClient::Tick);
		TickDelegateHandle = FTicker::GetCoreTicker().AddTicker(TickDelegate);

		//初始化客户端
		client = RakNet::RakPeerInterface::GetInstance();		
	}
	hasInit = true;
}

bool URawClient::Tick(float DeltaTime)
{
	if (!client)
	{
		return true;
	}

	//解析数据包
	for (packet = client->Receive(); packet; client->DeallocatePacket(packet), packet = client->Receive())
	{
		switch (packet->data[0])
		{
		case ID_CONNECTION_REQUEST_ACCEPTED:
			//("Our connection request has been accepted.\n");
			ConnectionEvent.Broadcast(EConnectionEvent::EConnectionEvent_Connected);
			break;
		case ID_CONNECTION_ATTEMPT_FAILED:
			//failed
			ConnectionEvent.Broadcast(EConnectionEvent::EConnectionEvent_ConnectionTimeout);
			break;
		case ID_NO_FREE_INCOMING_CONNECTIONS:
			//printf("The server is full.\n");
			ConnectionEvent.Broadcast(EConnectionEvent::EConnectionEvent_ServerFull);
			break;
		case ID_DISCONNECTION_NOTIFICATION:
			//disconnected
			ConnectionEvent.Broadcast(EConnectionEvent::EConnectionEvent_Disconnected);
			break;
		case ID_CONNECTION_LOST:
			//lost
			ConnectionEvent.Broadcast(EConnectionEvent::EConnectionEvent_Lost);
			break;
		case ID_GAME_MESSAGE_DEMO:
		{
			RakNet::RakString rs;
			RakNet::BitStream bsIn(packet->data, packet->length, false);
			bsIn.IgnoreBytes(sizeof(RakNet::MessageID));
			EResponseType responseType;
			bsIn.Read((unsigned char&)responseType);
			bsIn.Read(rs);
			ResponseEvent.Broadcast(responseType, UTF8_TO_TCHAR(rs.C_String()));
		}
		break;
		default:
			//unknown message
			//ConnectionEvent.Broadcast(EConnectionEvent::EConnectionEvent_Unknown);
			break;
		}
	}
	return true;
}

void URawClient::Connect(FString serverIP, int serverPort)
{
	if (client)
	{
		RakNet::SocketDescriptor sd;
		client->Startup(1, &sd, 1);
		client->Connect(TCHAR_TO_UTF8(*serverIP), serverPort, 0, 0);
	}
}

void URawClient::Send(RakNet::BitStream& bsOut)
{
	if (client)
	{
		client->Send(&bsOut, HIGH_PRIORITY, RELIABLE_ORDERED, 0, RakNet::UNASSIGNED_SYSTEM_ADDRESS, true);
	}
}

void URawClient::Shutdown()
{
	if (client)
	{
		client->Shutdown(1000, 0, PacketPriority::HIGH_PRIORITY);
		RakNet::RakPeerInterface::DestroyInstance(client);
		client = nullptr;
	}
	if (hasInit)
	{
		FTicker::GetCoreTicker().RemoveTicker(TickDelegateHandle);
		hasInit = false;
	}
}
