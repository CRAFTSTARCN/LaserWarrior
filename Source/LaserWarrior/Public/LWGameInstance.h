// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HttpSender.h"
#include "Engine/GameInstance.h"
#include "LWGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class LASERWARRIOR_API ULWGameInstance : public UGameInstance
{
	GENERATED_BODY()

protected:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FString Username;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FString Token;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FString TokenIssueTime;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FString GameToken;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bLogIn;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bInOnlineGame;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float Score;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UHttpSender* HttpSender;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void LoadGameOver();

public:

	ULWGameInstance();

	UFUNCTION(BlueprintCallable)
	void SetUser(const FString& InUsername, const FString& InToken, const FString& InIssueTime);
	
	UFUNCTION(BlueprintCallable)
	void ResetUser();

	UFUNCTION(BlueprintCallable)
	void ClearOnlineGame();

	UFUNCTION(BlueprintCallable)
	void SetGame(const FString& InGameToken);
	
	UFUNCTION(BlueprintCallable)
	void GameOver(float TotalScore);
	
	UFUNCTION(BlueprintCallable)
	FORCEINLINE bool PlayerIsLogin() const { return bLogIn; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE bool PlayerIsInOnlineGame() const { return bInOnlineGame; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE FString GetUsername() const { return Username; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE FString GetUserToken() const { return Token; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE FString GetUserTokenIssueTime() const { return TokenIssueTime; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE float GetScore() const { return Score; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE FString GetGameToken() const { return GameToken; }

	FORCEINLINE UHttpSender* GetHttpSender() { return HttpSender; }
};
