// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ControlPanel.h"
#include "Components/Image.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Character/Hero/HeroCharacter.h"
#include "AbilitySystem/PGCharacterAttributeSet.h"
#include "UI/BarWidget.h"

void UControlPanel::InitBar(float CurrentHP, float MaxHP, float CurrentCost, float MaxCost)
{
    HPBar->InitProgressBar(FLinearColor::Red, FText::FromString(TEXT("Hero HP")), CurrentHP, MaxHP);
    CostBar->InitProgressBar(FLinearColor::Blue, FText::FromString(TEXT("Cost")), CurrentCost, MaxCost);
}

void UControlPanel::UpdateHP(float InValue)
{
    HPBar->UpdateCurrent(InValue);
}

void UControlPanel::UpdateCost(float InValue)
{
    CostBar->UpdateCurrent(InValue);
}

void UControlPanel::NativeConstruct()
{
    Super::NativeConstruct();

    AHeroCharacter* Hero = Cast<AHeroCharacter>(GetOwningPlayerPawn());
    if (Hero)
    {
        UE_LOG(LogTemp, Log, TEXT("영웅 확인 완료"));
        Hero->SetJoystickWidget(this);
        UPGCharacterAttributeSet* AttributeSet = Hero->GetHeroAttributeSet();
        InitBar(AttributeSet->GetHealth(), AttributeSet->GetMaxHealth(), AttributeSet->GetCost(), AttributeSet->GetMaxCost());
    }
}

FReply UControlPanel::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
    if (JoyStickBackground)
    {
        // 마우스의 스크린 좌표 가져오기
        FVector2D ScreenPos = InMouseEvent.GetScreenSpacePosition();

        // 조이스틱 배경의 지오메트리 정보 가져오기
        const FGeometry& BackgroundGeometry = JoyStickBackground->GetCachedGeometry();

        // 해당 배경 영역 안에 마우스가 있는지 체크
        if (BackgroundGeometry.IsUnderLocation(ScreenPos))
        {
            bIsAreaPressed = true;
            return FReply::Handled().CaptureMouse(TakeWidget());
        }
    }
    return FReply::Unhandled();
}

FReply UControlPanel::NativeOnMouseMove(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
    if (bIsAreaPressed)
    {
        // 마우스의 스크린 좌표 가져오기
        FVector2D ScreenPos = InMouseEvent.GetScreenSpacePosition();

        // 2. 조이스틱 배경의 지오메트리 정보 가져오기
        const FGeometry& BackgroundGeometry = JoyStickBackground->GetCachedGeometry();

        // 위젯 로컬 좌표 계산
        FVector2D LocalPos = BackgroundGeometry.AbsoluteToLocal(ScreenPos);
        FVector2D Center = BackgroundGeometry.GetLocalSize() / 2.0f;

        // 중심으로부터의 벡터 계산
        FVector2D Delta = LocalPos - Center;

        // 거리 제한 및 정규화
        float Distance = FMath::Clamp(Delta.Size(), 0.0f, JoystickRange);
        JoystickVector = Delta.GetSafeNormal(); // 이동 방향

        // 조이스틱 이미지 이동
        if (JoyStick)
        {
            JoyStick->SetRenderTranslation(JoystickVector * Distance);
        }

        // 실제 이동에 사용할 벡터 업데이트 (0~1 사이 값)
        JoystickVector *= (Distance / JoystickRange);

        return FReply::Handled();
    }
    return FReply::Unhandled();
}

FReply UControlPanel::NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
    if (bIsAreaPressed)
    {
        bIsAreaPressed = false;
        JoystickVector = FVector2D::ZeroVector;

        // 조이스틱 위치 초기화
        if (JoyStick)
        {
            JoyStick->SetRenderTranslation(FVector2D::ZeroVector);
        }

        // 마우스 캡처 해제
        return FReply::Handled().ReleaseMouseCapture();
    }
    return FReply::Unhandled();
}
