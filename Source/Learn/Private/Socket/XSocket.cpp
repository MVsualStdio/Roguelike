// Fill out your copyright notice in the Description page of Project Settings.


#include "Socket/XSocket.h"
#include "SocketSubsystem.h"
#include "Sockets.h"
#include "XBlueprintFunctionLibrary.h"
#include "Interfaces/IPv4/IPv4Address.h"

// Sets default values
AXSocket::AXSocket()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Socket = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateSocket(NAME_Stream, TEXT("default"), false);
	
	FString address = TEXT("81.70.1.235");
	int32 port = 19834;
	FIPv4Address ip;
	FIPv4Address::Parse(address, ip);
	TSharedRef addr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
	addr->SetIp(ip.Value);
	addr->SetPort(port);
	connected = Socket->Connect(*addr);
	FTimerHandle Timer;
	//FTimerDelegate Delegate;
	//Delegate.BindUFunction(this,"SendMsg",FString("Hello"));
	//GetWorld()->GetTimerManager().SetTimer(Timer,this,&AXSocket::SendMsg,2.0,true);
}

// Called when the game starts or when spawned
void AXSocket::BeginPlay()
{
	Super::BeginPlay();
	
}

void AXSocket::SendMsg()
{
	if(connected)
	{
		UXBlueprintFunctionLibrary::Debug("SOCKET");
		FString serialized = "Hello";
        TCHAR *serializedChar = serialized.GetCharArray().GetData();
        int32 size = FCString::Strlen(serializedChar);
        int32 sent = 0;
        bool successful = Socket->Send((uint8*)TCHAR_TO_UTF8(serializedChar), size, sent);
		if(successful)
		{
			UXBlueprintFunctionLibrary::Debug("SSS");
		}
	}
}


// Called every frame
void AXSocket::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

