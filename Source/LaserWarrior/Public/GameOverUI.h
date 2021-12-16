// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Interfaces/IHttpRequest.h"
#include "GameOverUI.generated.h"

/**
 * 
 */
UCLASS()
class LASERWARRIOR_API UGameOverUI : public UUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float TotalScore;

	UFUNCTION(BlueprintImplementableEvent)
	void UploadSuccess();

	UFUNCTION(BlueprintImplementableEvent)
	void UploadFailed();

public:

	UFUNCTION(BlueprintCallable)
	void UploadScore();

	void OnUploadComplete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSuccess);
};
