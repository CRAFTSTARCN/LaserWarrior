// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Interfaces/IHttpRequest.h"
#include "RankList.generated.h"

/**
 * 
 */
UCLASS()
class LASERWARRIOR_API URankList : public UUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 LineCount;

	UFUNCTION(BlueprintImplementableEvent)
	void SetLine(int32 LineIndex, const FString& Username, int32 Score);

	UFUNCTION(BlueprintImplementableEvent)
	void OnGetRankFailed();

	UFUNCTION(BlueprintImplementableEvent)
	void StartWaitNetwork();

	UFUNCTION(BlueprintImplementableEvent)
	void EndWaitNetwork();
	
public:

	UFUNCTION(BlueprintCallable)
	void UpdateRankList();

	void OnRankListFetched(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSuccess);
};
