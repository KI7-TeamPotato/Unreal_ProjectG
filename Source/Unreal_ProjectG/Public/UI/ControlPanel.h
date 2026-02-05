// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ControlPanel.generated.h"

class UImage;

/**
 * 
 */
UCLASS()
class UNREAL_PROJECTG_API UControlPanel : public UUserWidget
{
	GENERATED_BODY()

public:
    // 외부(캐릭터)에서 조이스틱 값을 가져갈 함수
    FVector2D GetJoystickVector() const { return JoystickVector; }

protected:
    // 블루프린트 이벤트를 C++에서 오버라이드
    virtual void NativeConstruct() override;
    virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
    virtual FReply NativeOnMouseMove(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
    virtual FReply NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;


protected:
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UImage> JoyStick;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UImage> JoyStickBackground;

    // 내부 변수
    bool bIsAreaPressed = false;
    float JoystickRange = 150.0f; // 블루프린트의 Clamp 값
    FVector2D JoystickVector = FVector2D::ZeroVector;
};
