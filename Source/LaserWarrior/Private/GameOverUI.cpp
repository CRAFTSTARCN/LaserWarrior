// Fill out your copyright notice in the Description page of Project Settings.


#include "GameOverUI.h"

#include "LWGameInstance.h"
#include "Interfaces/IHttpResponse.h"

void UGameOverUI::UploadScore() {
	ULWGameInstance* Game = Cast<ULWGameInstance>(GetGameInstance());
	if(Game) {
		FString Body;
		TSharedRef<TJsonWriter<>> JsonWriter = TJsonWriterFactory<>::Create(&Body);
		JsonWriter->WriteObjectStart();
		JsonWriter->WriteValue("Username", Game->GetUsername());
		JsonWriter->WriteValue("Token", Game->GetUserToken());
		JsonWriter->WriteValue("IssueTime", Game->GetUserTokenIssueTime());
		JsonWriter->WriteValue("GameToken", Game->GetGameToken());
		JsonWriter->WriteValue("Score", (int32)Game->GetScore());
		JsonWriter->WriteObjectEnd();
		JsonWriter->Close();

		Game->GetHttpSender()->SendHttpRequest(Body,TEXT("POST"),TEXT("/api/settlement/"),
									  this,&UGameOverUI::OnUploadComplete);
	}
}

void UGameOverUI::OnUploadComplete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSuccess) {
	if(!HttpResponse.IsValid() || !bSuccess) {
		UploadFailed();
		return;
	}

	TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(HttpResponse->GetContentAsString());
	TSharedPtr<FJsonObject> JsonObject;

	if(FJsonSerializer::Deserialize(JsonReader, JsonObject)) {
		int32 code = JsonObject->GetIntegerField(TEXT("code"));
		if(code != 200) {
			UploadFailed();
		} else {
			ULWGameInstance* Game = Cast<ULWGameInstance>(GetGameInstance());
			if(Game) {
				Game->ClearOnlineGame();
			}
			UploadSuccess();
		}
	} else {
		UploadFailed();
	}
}
