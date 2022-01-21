// Fill out your copyright notice in the Description page of Project Settings.


#include "Pingaman.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
APingaman::APingaman()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//Get Module and use CapsuleSizeMethod with params
	GetCapsuleComponent()->InitCapsuleSize(42.0f, 96.0f);

	//we want forbide char movement instead move camera

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 600.0f;
	GetCharacterMovement()->AirControl = 0.2f;

	//CameraBoom will be child of a capstule so it will follow the character
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);

	CameraBoom->TargetArmLength = 500.0f;
	//this allowes to use camera as controller
	CameraBoom->bUsePawnControlRotation = true;
	//We created camera object
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	//We add boom to the camera object witch uses our spring arm component
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	bDead = false;
	Power = 100.0f;
	Score = 0.0f;

	


}

// Called when the game starts or when spawned
void APingaman::BeginPlay()
{
	Super::BeginPlay();

	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &APingaman::OnBeginOverlap);

	if(Player_Power_Widget_Class != nullptr )
	{
		Player_Power_Widget = CreateWidget(GetWorld(), Player_Power_Widget_Class);
		Player_Power_Widget->AddToViewport();
	}

	if (Player_Score_Widget_Class != nullptr)
	{
		Player_Score_Widget = CreateWidget(GetWorld(), Player_Score_Widget_Class);
		Player_Score_Widget->AddToViewport();
	}
	
}

// Called every frame
void APingaman::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//This wil remove value every frame
	Power -= DeltaTime * Power_Threshold;

	if (Power <= 0)
	{
		if(!bDead)
		{
			bDead = true;

			GetMesh()->SetSimulatePhysics(true);
			//
			FTimerHandle UnusedHandle;
			//GetWorldTimer will Set timer by using this unusedHandel inside this class ,&APingaman::Restart is the function we want to call after 3 seconds has passed
			// and false means we don t want repeatedly to call function
			GetWorldTimerManager().SetTimer(UnusedHandle, this, &APingaman::RestarGame, 3.0f, false);
		}
	}
}

// Called to bind functionality to input
void APingaman::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Name of the input and we bind this input to this component
	//It means this Method allows us rotate our Pawn
	//Pitch allows us 
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	//We inherit jump method from ACharacter class
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &APingaman::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APingaman::MoveRight);

	//

}

void APingaman::MoveForward(float Axis)
//Move character forwardon x axis
{
	if(!bDead)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Axis);
	}
}

void APingaman::MoveRight(float Axis)
{
	if (!bDead)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Axis);
	}
}

void APingaman::RestarGame()
{
	UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
}

void APingaman::OnBeginOverlap(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//OtherActor is our pickable item and if we pick it up we gain power and destroy pickable item
	if(OtherActor->ActorHasTag("Recharge"))
	{
		Power += 10.f;

		if (Power > 100.0f)
			Power = 100.0f;

		OtherActor->Destroy();
	}
}
