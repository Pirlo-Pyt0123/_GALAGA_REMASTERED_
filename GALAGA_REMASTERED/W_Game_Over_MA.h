// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "W_Game_Over_MA.generated.h"



UCLASS()
class GALAGA_REMASTERED_API UW_Game_Over_MA : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidget))
	class UButton* Menu_Regreso_Button;

	UPROPERTY(meta = (BindWidget))
	class UButton* Salir_Button;

protected:
	virtual void NativeConstruct() override;

private:
	UFUNCTION()
	void OnMenuRegresoClicked();

	UFUNCTION()
	void OnSalirClicked();
	
};
