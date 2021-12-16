// Fill out your copyright notice in the Description page of Project Settings.


#include "ScoreQueryUI.h"
#include "Interfaces/IHttpResponse.h"

#include "LWGameInstance.h"

void UScoreQueryUI::QueryScore() {
	ULWGameInstance* Game = Cast<ULWGameInstance>(GetGameInstance());
	if(Game) {
		StartQuery();
		FString Body;
		TSharedPtr<TJsonWriter<>> JsonWriter = TJsonWriterFactory<>::Create(&Body);

		JsonWriter->WriteObjectStart();
		JsonWriter->WriteValue("Score", Score);
		JsonWriter->WriteObjectEnd();
		JsonWriter->Close();

		Game->GetHttpSender()->SendHttpRequest(Body, TEXT("POST"), TEXT("/api/query/"),
											   this, &UScoreQueryUI::OnQueryComplete);
	}
}

void UScoreQueryUI::OnQueryComplete(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSuccess) {
	EndQuery();
	if(!bSuccess || !HttpResponse.IsValid()) {
		return;
	}

	TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(HttpResponse->GetContentAsString());
	TSharedPtr<FJsonObject> JsonObject;

	if(FJsonSerializer::Deserialize(JsonReader, JsonObject)) {
		int32 code = JsonObject->GetIntegerField(TEXT("code"));
		if(code == 200) {
			RankOfScore = JsonObject->GetIntegerField(TEXT("BestRank"));
		}
	}
}
