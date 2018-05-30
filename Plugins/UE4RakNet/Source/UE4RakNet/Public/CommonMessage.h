#pragma once

#include "MessageIdentifiers.h"
#include "UObject/NoExportTypes.h"
#include "CommonMessage.generated.h"

//自定义消息头
enum GameMessages
{
	ID_GAME_MESSAGE_DEMO = ID_USER_PACKET_ENUM + 100
};

//Connection Event
UENUM(BlueprintType)		//"BlueprintType" is essential to include
enum class EConnectionEvent : uint8
{
	EConnectionEvent_Connected 			UMETA(DisplayName = "CE_Connected"),
	EConnectionEvent_Disconnected		UMETA(DisplayName = "CE_Disconnected"),
	EConnectionEvent_Lost 				UMETA(DisplayName = "CE_Lost"),
	EConnectionEvent_ServerFull			UMETA(DisplayName = "CE_ServerFull"),
	EConnectionEvent_ConnectionTimeout	UMETA(DisplayName = "CE_TimeOut"),
	EConnectionEvent_Unknown			UMETA(DisplayName = "CE_Unknown")
};


//请求类型
UENUM(BlueprintType)
enum class ERequestType : uint8
{
	ERequestType_DEMO			UMETA(DisplayName = "REQ_DEMO")
};

//响应类型
UENUM(BlueprintType)
enum class EResponseType : uint8
{
	EResponseType_DEMO  		UMETA(DisplayName = "RES_DEMO")
};
