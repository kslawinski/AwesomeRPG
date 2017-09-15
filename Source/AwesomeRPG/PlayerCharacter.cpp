// Fill out your copyright notice in the Description page of Project Settings.

#include "AwesomeRPG.h"
#include "PlayerCharacter.h"
#include "Item.h"
#include "Sword.h"
#include "Shield.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

												// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

												   // Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
												   // are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)


	CollectionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Collection Sphere"));
	CollectionSphere->AttachTo(RootComponent);
	CollectionSphere->SetSphereRadius(200.0f);
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	if(itemClass == nullptr)
	{
		return;
	}


	//item = GetWorld()->SpawnActor<AItem>(itemClass);
	//item->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("ItemSocket"));//AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true),);
	//item->DetachFromActor(FDetachmentTransformRules(EDetachmentRule::KeepWorld,true)); // USE TO DETACH
}

void APlayerCharacter::DropWeapon()
{
	if (sword != nullptr)
	{
		sword->EnableItemPhisics();
		sword->DetachFromActor(FDetachmentTransformRules(EDetachmentRule::KeepWorld, true));
		sword = nullptr;
	}
}

void APlayerCharacter::PickUpItem()
{
	UE_LOG(LogTemp, Warning, TEXT("Pick up E pressed"));

	TArray<AActor*> detectedActors;

	CollectionSphere->GetOverlappingActors(detectedActors);

	for (int32 i = 0; i < detectedActors.Num(); i++)
	{
		ASword* const testSword = Cast<ASword>(detectedActors[i]);

		if (testSword && !testSword->IsPendingKill())
		{
			// Pick it up
			UE_LOG(LogTemp, Warning, TEXT("item Detected"));
			sword = testSword;
			testSword->DisableItemPhisics();
			testSword->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("RightHandSocket"));//AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true),);
		}

		AShield* const testShield = Cast<AShield>(detectedActors[i]);

		if (testShield && !testShield->IsPendingKill())
		{
			testShield->DisableItemPhisics();
			testShield->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("LeftHandSocket"));//AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true),);
		}
	}
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	//Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Set up gameplay key bindings
	check(PlayerInputComponent);
	//PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	//PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);
	PlayerInputComponent->BindAction("DropWeapon", IE_Pressed, this, &APlayerCharacter::DropWeapon);
	PlayerInputComponent->BindAction("PickUpItem", IE_Pressed, this, &APlayerCharacter::PickUpItem);

	

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
//	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	//PlayerInputComponent->BindAxis("TurnRate", this, &APlayerCharacter::TurnAtRate);
	//PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	//PlayerInputComponent->BindAxis("LookUpRate", this, &APlayerCharacter::LookUpAtRate);


}

void APlayerCharacter::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void APlayerCharacter::MoveRight(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}