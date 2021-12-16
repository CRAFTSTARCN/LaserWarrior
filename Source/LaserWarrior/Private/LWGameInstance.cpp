// Fill out your copyright notice in the Description page of Project Settings.


#include "LWGameInstance.h"

ULWGameInstance::ULWGameInstance() {
	HttpSender = CreateDefaultSubobject<UHttpSender>(TEXT("Http Sender"));
}

void ULWGameInstance::SetUser(const FString& InUsername, const FString& InToken, const FString& InIssueTime) {
	Username = InUsername;
	Token = InToken;
	TokenIssueTime = InIssueTime;
	bLogIn = true;
}

void ULWGameInstance::ResetUser() {
	Username = TEXT("");
	Token = TEXT("");
	TokenIssueTime = TEXT("");
	bLogIn = false;
}

void ULWGameInstance::ClearOnlineGame() {
	GameToken = TEXT("");
	bInOnlineGame = false;
}

void ULWGameInstance::SetGame(const FString& InGameToken) {
	GameToken = InGameToken;
	bInOnlineGame = true;
}

void ULWGameInstance::GameOver(float TotalScore) {
	Score = TotalScore;
	LoadGameOver();
}
