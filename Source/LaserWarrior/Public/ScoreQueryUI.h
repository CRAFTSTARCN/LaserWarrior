// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Interfaces/IHttpRequest.h"
#include "ScoreQueryUI.generated.h"

/**
 * 
 */
UCLASS()
class LASERWARRIOR_API UScoreQueryUI : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int32 Score;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int32 RankOfScore;

	UFUNCTION(BlueprintImplementableEvent)
	void StartQuery();

	UFUNCTION(BlueprintImplementableEvent)
	void EndQuery();

public:

	UFUNCTION(BlueprintCallable)
	void QueryScore();

	void OnQueryComplete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSuccess);
	
};
