// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HttpModule.h"
#include "Components/ActorComponent.h"
#include "Interfaces/IHttpRequest.h"
#include "HttpSender.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LASERWARRIOR_API UHttpSender : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHttpSender();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString HostURL;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float TimeoutSecond;
	
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	template<typename UserClass>
	void SendHttpRequest(const FString& RequestBody, const FString& Method, const FString& Path,
						 UserClass* UserObject, 
		                 typename FHttpRequestCompleteDelegate::TUObjectMethodDelegate<UserClass>::FMethodPtr CompleteCallback)
	{
		TSharedRef<IHttpRequest, ESPMode::ThreadSafe> HttpRequest = FHttpModule::Get().CreateRequest();
		HttpRequest->SetURL(HostURL + Path);
		HttpRequest->SetVerb(Method);
		HttpRequest->SetTimeout(TimeoutSecond);
		HttpRequest->SetContentAsString(RequestBody);
		HttpRequest->SetHeader(TEXT("Content-Type"), TEXT("application/json;charset=UTF-8"));
		HttpRequest->OnProcessRequestComplete().BindUObject(UserObject, CompleteCallback);
		HttpRequest->ProcessRequest();
	}
};
