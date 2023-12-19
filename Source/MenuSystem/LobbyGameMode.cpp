// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyGameMode.h"
#include "GameFramework/GameStateBase.h"
#include "GameFramework/PlayerState.h"

void ALobbyGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	if (GameState)
	{
		const int32 NumberOfPlayers = GameState.Get()->PlayerArray.Num();

		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(1, 60.f, FColor::Yellow,
			                                 FString::Printf(TEXT("Players in game: %d"), NumberOfPlayers));

			if (const APlayerState* PlayerState = NewPlayer->GetPlayerState<APlayerState>())
			{
				GEngine->AddOnScreenDebugMessage(-11, 60.f, FColor::Cyan,
				                                 FString::Printf(
					                                 TEXT("%s Joined the game"), *PlayerState->GetPlayerName()));
			}
		}
	}
}

void ALobbyGameMode::Logout(AController* Exiting)
{
	Super::Logout(Exiting);

	if (GEngine && GameState)
	{
		const int32 NumberOfPlayers = GameState.Get()->PlayerArray.Num();
		GEngine->AddOnScreenDebugMessage(1, 60.f, FColor::Yellow,
		                                 FString::Printf(TEXT("Players in game: %d"), NumberOfPlayers - 1));

		if (const APlayerState* PlayerState = Exiting->GetPlayerState<APlayerState>())
		{
			GEngine->AddOnScreenDebugMessage(-11, 60.f, FColor::Cyan,
			                                 FString::Printf(
				                                 TEXT("%s Joined the game"), *PlayerState->GetPlayerName()));
		}
	}
}
