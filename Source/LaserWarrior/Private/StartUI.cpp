// Fill out your copyright notice in the Description page of Project Settings.


#include "StartUI.h"

#include "LWGameInstance.h"
#include "Interfaces/IHttpResponse.h"

void UStartUI::OnRegistSuccess(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSuccess) {
	StopNetWait();
	if(!HttpResponse.IsValid() || !bSuccess) {
		ShowNetworkError();
		return;
	}

	TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(HttpResponse->GetContentAsString());
	TSharedPtr<FJsonObject> JsonObject;

	if(FJsonSerializer::Deserialize(JsonReader, JsonObject)) {
		int32 code = JsonObject->GetIntegerField(TEXT("code"));
		if(code != 200) {
			ErrorInfo = JsonObject->GetStringField(TEXT("message"));
			ShowErrorInfo();
		} else {
			User = JsonObject->GetStringField("Username");
			ULWGameInstance* LWGameInstance = Cast<ULWGameInstance>(GetGameInstance());
			if(LWGameInstance) {
				LWGameInstance->SetUser(User, JsonObject->GetStringField("Token"), JsonObject->GetStringField("IssueTime"));
			}
			LoginSuccess();
		}
	} else {
		ShowNetworkError();
	}
}

void UStartUI::Regist(const FString& Username, const FString& Password) {
	FString Body;
	TSharedRef<TJsonWriter<>> JsonWriter = TJsonWriterFactory<>::Create(&Body);
	JsonWriter->WriteObjectStart();
	JsonWriter->WriteValue("Username", Username);
	JsonWriter->WriteValue("Password", Password);
	JsonWriter->WriteObjectEnd();
	JsonWriter->Close();

	ULWGameInstance* Game = Cast<ULWGameInstance>(GetGameInstance());
	if(Game) {
		Game->GetHttpSender()->SendHttpRequest(Body,TEXT("POST"),TEXT("/api/register/"),
			                          this,&UStartUI::OnRegistSuccess);
	}
}

void UStartUI::PlayerLogin(const FString& Username, const FString& Password) {
	FString Body;
	TSharedRef<TJsonWriter<>> JsonWriter = TJsonWriterFactory<>::Create(&Body);
	JsonWriter->WriteObjectStart();
	JsonWriter->WriteValue("Username", Username);
	JsonWriter->WriteValue("Password", Password);
	JsonWriter->WriteObjectEnd();
	JsonWriter->Close();

	ULWGameInstance* Game = Cast<ULWGameInstance>(GetGameInstance());
	if(Game) {
		Game->GetHttpSender()->SendHttpRequest(Body,TEXT("POST"),TEXT("/api/login/"),
									  this,&UStartUI::OnRegistSuccess);
	}
}

void UStartUI::GetBattleHistory() {
	ULWGameInstance* Game = Cast<ULWGameInstance>(GetGameInstance());
	if(Game) {
		FString Body;
		TSharedRef<TJsonWriter<>> JsonWriter = TJsonWriterFactory<>::Create(&Body);
		JsonWriter->WriteObjectStart();
		JsonWriter->WriteValue("Username", User);
		JsonWriter->WriteValue("Token", Game->GetUserToken());
		JsonWriter->WriteValue("IssueTime", Game->GetUserTokenIssueTime());
		JsonWriter->WriteObjectEnd();
		JsonWriter->Close();

		Game->GetHttpSender()->SendHttpRequest(Body, TEXT("POST"), TEXT("/api/mybest/"),
									  this,&UStartUI::OnBattleHistroyFetched);
	}
}

void UStartUI::OnBattleHistroyFetched(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSuccess) {
	StopNetWait();
	if(!HttpResponse.IsValid() || !bSuccess) {
		ShowNetworkError();
		return;
	}

	TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(HttpResponse->GetContentAsString());
	TSharedPtr<FJsonObject> JsonObject;

	if(FJsonSerializer::Deserialize(JsonReader, JsonObject)) {
		int32 code = JsonObject->GetIntegerField(TEXT("code"));
		if(code != 200) {
			
		} else {
			BestScore = JsonObject->GetIntegerField(TEXT("MaxScore"));
			Rank = JsonObject->GetIntegerField(TEXT("BestRank"));
			if(Rank < 0) {
				NoBattleHistory();
			} else {
				ShowBattleHistory();
			}
		}
	} else {
		ShowNetworkError();
	}
}

void UStartUI::AllocGame() {
	ULWGameInstance* Game = Cast<ULWGameInstance>(GetGameInstance());
	if(Game) {
		FString Body;
		TSharedRef<TJsonWriter<>> JsonWriter = TJsonWriterFactory<>::Create(&Body);
		JsonWriter->WriteObjectStart();
		JsonWriter->WriteValue("Username", User);
		JsonWriter->WriteValue("Token", Game->GetUserToken());
		JsonWriter->WriteValue("IssueTime", Game->GetUserTokenIssueTime());
		JsonWriter->WriteObjectEnd();
		JsonWriter->Close();

		Game->GetHttpSender()->SendHttpRequest(Body, TEXT("POST"), TEXT("/api/alloc/"),
									  this,&UStartUI::OnGameAlloced);
	}
}

void UStartUI::OnGameAlloced(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSuccess) {
	StopNetWait();
	if(!HttpResponse.IsValid() || !bSuccess) {
		ShowNetworkError();
		return;
	}

	TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(HttpResponse->GetContentAsString());
	TSharedPtr<FJsonObject> JsonObject;

	if(FJsonSerializer::Deserialize(JsonReader, JsonObject)) {
		int32 code = JsonObject->GetIntegerField(TEXT("code"));
		if(code != 200) {

		} else {
			FString GameToken = JsonObject->GetStringField("GameToken");
			ULWGameInstance* Game = Cast<ULWGameInstance>(GetGameInstance());
			if(Game) {
				Game->SetGame(GameToken);
				AllocSuccess();
			}
		}
	} else {
		ShowNetworkError();
	}
}
