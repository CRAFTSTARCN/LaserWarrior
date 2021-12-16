// Fill out your copyright notice in the Description page of Project Settings.


#include "RankList.h"

#include "LWGameInstance.h"
#include "Interfaces/IHttpResponse.h"

void URankList::UpdateRankList() {
	ULWGameInstance* Game = Cast<ULWGameInstance>(GetGameInstance());
	if(Game) {
		FString Body;
		StartWaitNetwork();
		Game->GetHttpSender()->SendHttpRequest(Body, TEXT("GET"), TEXT("/api/rank/"),
									  this,&URankList::OnRankListFetched);
	}
}

void URankList::OnRankListFetched(FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSuccess) {
	EndWaitNetwork();
	if(!bSuccess || !HttpResponse.IsValid()) {
		OnGetRankFailed();
		return;
	}

	TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(HttpResponse->GetContentAsString());
	TSharedPtr<FJsonObject> JsonObject;

	if(FJsonSerializer::Deserialize(JsonReader, JsonObject)) {
		int32 code = JsonObject->GetIntegerField(TEXT("code"));
		if(code == 200) {
			TArray<TSharedPtr<FJsonValue>> RankArray = JsonObject->GetArrayField("RankList");
			int LineIndex=0;
			for (auto JsonValue : RankArray) {
				const TSharedPtr<FJsonObject>* Object;
				bool CastSuccess = JsonValue->TryGetObject(Object);
				if(CastSuccess) {
					SetLine(LineIndex,
					(*Object)->GetStringField("PlayedUser"),(*Object)->GetIntegerField("Score"));
					++LineIndex;
				}
			}
		} else {
			OnGetRankFailed();
		}
	}
}
