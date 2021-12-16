// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Interfaces/IHttpRequest.h"
#include "StartUI.generated.h"

/**
 * 
 */
UCLASS()
class LASERWARRIOR_API UStartUI : public UUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FString ErrorInfo;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FString User;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 Rank;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 BestScore;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void StopNetWait();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void ShowNetworkError();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void ShowErrorInfo();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void LoginSuccess();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void ShowBattleHistory();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void NoBattleHistory();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void AllocSuccess();
	
public:

	
	UFUNCTION(BlueprintCallable)
	void Regist(const FString& Username, const FString& Password);

	UFUNCTION(BlueprintCallable)
	void PlayerLogin(const FString& Username, const FString& Password);
	
	void OnRegistSuccess(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSuccess);

	UFUNCTION(BlueprintCallable)
	void GetBattleHistory();
	
	void OnBattleHistroyFetched(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSuccess);

	UFUNCTION(BlueprintCallable)
	void AllocGame();

	void OnGameAlloced(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSuccess);
};
