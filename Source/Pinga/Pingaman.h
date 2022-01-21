// Fill out your copyright notice in the Description page of Project Settings.

//In this class we define our main characters methods and settings, atributes

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"

#include "Blueprint/UserWidget.h"


#include "Pingaman.generated.h"

UCLASS()
class PINGA_API APingaman : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APingaman();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	UCameraComponent* FollowCamera;

	//Define right and left movement methods
	void MoveForward(float Axis);
	void MoveRight(float Axis);

	//dead means can move or not
	bool bDead;
	//We can only accses this power variable in blueprint if we dont add BlueprintReadOnly we cant acceses it 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float Score;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float Power;

	UPROPERTY(EditAnywhere)
	float Power_Threshold;
	//It wont compile if we dont implement it
	UFUNCTION()
	void OnBeginOverlap(class UPrimitiveComponent* HitComp, class AActor* OtherActor,
	                    class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	                    const FHitResult& SweepResult);

	UPROPERTY(EditAnywhere, Category = "UI HUD")
	TSubclassOf<UUserWidget> Player_Power_Widget_Class;
	UUserWidget* Player_Power_Widget;

	TSubclassOf<UUserWidget> Player_Score_Widget_Class;
	UUserWidget* Player_Score_Widget;

	void RestarGame();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
