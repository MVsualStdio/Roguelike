// Fill out your copyright notice in the Description page of Project Settings.


#include "XGameMode.h"
#include "Engine.h"
#include "XAction.h"
#include "XAIPrimaryDataAsset.h"
#include "AI/XAICharacter.h"
#include "EnvironmentQuery/EnvQueryManager.h"
#include "XAttrributeComponent.h"
#include "XGameInterface.h"
#include "XPlayerChacter.h"
#include "XPlayerState.h"
#include "XSaveGame.h"
#include "Chaos/ImplicitQRSVD.h"
#include "Kismet/KismetMathLibrary.h"
#include "XGameInterface.h"
#include "Serialization/ObjectAndNameAsStringProxyArchive.h"
#include "XActionActorComponent.h"
#include "Engine/AssetManager.h"

AXGameMode::AXGameMode()
{
	DelayTime = 5.0f;
	PlayerStateClass = AXPlayerState::StaticClass();
	SlotName = "SaveGame01";
	// APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(),0);
	// AXPlayerChacter* Player = Cast<AXPlayerChacter>(PlayerController->GetCharacter());
	 //Player->OnDeath.AddDynamic(this,&AXGameMode::Respawn);
	//PlayerChacter->OnDeath.AddDynamic(this,&AXGameMode::Respawn);
}

void AXGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);
	LoadGame();
}


void AXGameMode::StartPlay()
{
	Super::StartPlay();
	
	GetWorld()->GetTimerManager().SetTimer(TimeHandle,this,&AXGameMode::SpawnAI,2.0f,true);
}

void AXGameMode::HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer)
{
	
	AXPlayerState* Ps = NewPlayer->GetPlayerState<AXPlayerState>();
	if(Ps)
	{
		Ps->LoadPlayerState(CurrentSaveGame);
	}
	Super::HandleStartingNewPlayer_Implementation(NewPlayer);
}


void AXGameMode::SpawnAI()
{
	UEnvQueryInstanceBlueprintWrapper* EQSInstance = UEnvQueryManager::RunEQSQuery(this,QueryTemplate,this,EEnvQueryRunMode::Type::RandomBest5Pct,nullptr);
	if(EQSInstance)
	{
		EQSInstance->GetOnQueryFinishedEvent().AddDynamic(this,&AXGameMode::SpawnAIQuery);
	}
	
}



void AXGameMode::SpawnAIQuery(UEnvQueryInstanceBlueprintWrapper* QueryInstance, EEnvQueryStatus::Type QueryStatus)
{
	if(QueryStatus != EEnvQueryStatus::Type::Success)
	{
		return;
	}
	TArray<FVector> QueryRes = QueryInstance->GetResultsAsLocations();

	int32 ExistAI = 0;
	for(TActorIterator<AXAICharacter> it(GetWorld()); it; ++it)
	{
		AXAICharacter* AI = *it;
		
		UXAttrributeComponent* Attribute = Cast<UXAttrributeComponent>(AI->GetComponentByClass(UXAttrributeComponent::StaticClass())); 
		if(Attribute)
		{
			if(Attribute->IsAlive())
			{
				++ExistAI;
			}
		}
	}
	float MaxAINums = 10.0f;
	if(Curve)
	{
		MaxAINums = Curve->GetFloatValue(GetWorld()->TimeSeconds);
	}
	//MaxAINums = 0.0f;
	if(ExistAI >= MaxAINums)
	{
		return;
	}
	if(QueryRes.IsValidIndex(0))
	{
		if(DataTable)
		{
			TArray<FAIRow*> OutRow;
			DataTable->GetAllRows("",OutRow);
			int RandomIndex = FMath::RandRange(0,OutRow.Num()-1);
			FAIRow* SelectData = OutRow[RandomIndex];
			UAssetManager* AssetManager = UAssetManager::GetIfValid();
			if(AssetManager)
			{
				TArray<FName> Bundles;
				FStreamableDelegate Delegate;
				AssetManager->LoadPrimaryAsset(SelectData->AIId,Bundles,Delegate);
			}
			AActor* Actor = GetWorld()->SpawnActor<AActor>(SelectData->->AICharector->Character,QueryRes[0],FRotator::ZeroRotator);
			if(Actor)
			{
				UXActionActorComponent* Component = Cast<UXActionActorComponent>(Actor->GetComponentByClass(UXActionActorComponent::StaticClass()));
				if(Component)
				{
					for(TSubclassOf<UXAction> Action : SelectData->AICharector->Action)
					{
						Component->AddAction(Actor,Action);
					}
					
				}
			}
		}
		
	}
	
}

void AXGameMode::Respawn(AController* Controller)
{
	if(Controller)
	{
		Controller->UnPossess();
		RestartPlayer(Controller);
	}
}

void AXGameMode::ActorOnKilled(AActor* KilledActor, AActor* OtherActor)
{
	AXPlayerChacter* PlayerChacter = Cast<AXPlayerChacter>(KilledActor);
	APawn* Pawn = Cast<APawn>(OtherActor);
	APawn* KilledPawn = Cast<APawn>(KilledActor);
	if(PlayerChacter)
	{
		FTimerHandle TimerHandle;
		FTimerDelegate TimeDele;
		TimeDele.BindUFunction(this, "Respawn", PlayerChacter->GetController());
		// TimeDele.BindLambda([this,PlayerChacter]()
		// {
		// 	Respawn(PlayerChacter->GetController());
		// });
		GetWorld()->GetTimerManager().SetTimer(TimerHandle,TimeDele,DelayTime,false);
	}
	else if(Pawn)
	{
		//AXPlayerState* State =  Cast<AXPlayerState>(UGameplayStatics::GetPlayerState(Pawn,0));
		//AXPlayerState* State =  Cast<AXPlayerState>(UGameplayStatics::GetPlayerPawn(GetWorld(),0)->GetPlayerState());
		//AXPlayerState* State = Pawn->GetPlayerState<AXPlayerState>();
		AXPlayerState* State = Pawn->GetPlayerState<AXPlayerState>();
		AXAICharacter* AI = Cast<AXAICharacter>(KilledActor);
		
		if(State && DataTable && AI)
		{
			FAIRow* Row = DataTable->FindRow<FAIRow>(AI->AIName,"");
			if(Row)
			{
				State->AddCredites(Row->KillReward);
			}
			
				
		}
		
		//UE_LOG(LogTemp, Log, TEXT("ADD"));
	}
}

void AXGameMode::SaveGame()
{
	for(int i=0;i<GameState->PlayerArray.Num();++i)
	{
		AXPlayerState* Ps = Cast<AXPlayerState>(GameState->PlayerArray[i]);
		if(Ps)
		{
			Ps->SavePlayerState(CurrentSaveGame);
			UE_LOG(LogTemp,Log,TEXT("SAVE"));
			break;
		}
	}
	CurrentSaveGame->SaveData.Empty();

	for(FActorIterator it(GetWorld());it;++it)
	{
		AActor* Actor = *it;
		if(it->Implements<UXGameInterface>())
		{
			FActorSaveData SaveData;
			SaveData.ActorName = Actor->GetName();
			SaveData.Transform = Actor->GetTransform();
			FMemoryWriter MemoryWriter(SaveData.ByteData);
			FObjectAndNameAsStringProxyArchive Ar(MemoryWriter,true);
			Ar.ArIsSaveGame = true;
			Actor->Serialize(Ar);
			CurrentSaveGame->SaveData.Add(SaveData);
		}
	}
	UGameplayStatics::SaveGameToSlot(CurrentSaveGame,SlotName,0);	
}

void AXGameMode::LoadGame()
{
	if(UGameplayStatics::DoesSaveGameExist(SlotName,0))
	{

		CurrentSaveGame = Cast<UXSaveGame>(UGameplayStatics::LoadGameFromSlot(SlotName,0));
		if(CurrentSaveGame == nullptr)
		{
			UE_LOG(LogTemp,Log,TEXT("Load Error"));
			return;
		}
		for(FActorIterator it(GetWorld());it;++it)
		{
			AActor* Actor = *it;
			if(Actor->Implements<UXGameInterface>())
			{
				for(FActorSaveData SaveData:CurrentSaveGame->SaveData)
				{
					if(Actor->GetName() == SaveData.ActorName)
					{
						Actor->SetActorTransform(SaveData.Transform);
						FMemoryReader MemReader(SaveData.ByteData);

						FObjectAndNameAsStringProxyArchive Ar(MemReader, true);
						Ar.ArIsSaveGame = true;
						// Convert binary array back into actor's variables
						Actor->Serialize(Ar);
						IXGameInterface::Execute_IntergetOnLoad(Actor);
						break;
					}
				}
			}
		}
	}
	else
	{
		CurrentSaveGame = Cast<UXSaveGame>(UGameplayStatics::CreateSaveGameObject(UXSaveGame::StaticClass()));
		UE_LOG(LogTemp,Log,TEXT("Create LOG"));
	}
}

