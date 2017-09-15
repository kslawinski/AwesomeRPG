// Fill out your copyright notice in the Description page of Project Settings.

#include "AwesomeRPG.h"
#include "Item.h"


// Sets default values
AItem::AItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Object"), false);
	itemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Item Mesh Comp"), false);
	itemMesh->SetupAttachment(RootComponent);

	const ConstructorHelpers::FObjectFinder<UStaticMesh> MeshObj(TEXT("StaticMesh'/Game/Mesh/LowPolyKnight/LowPoly_Knight_Sword.LowPoly_Knight_Sword'")); // load a mesh from a file
	itemMesh->SetStaticMesh(MeshObj.Object);

	itemMesh->SetSimulatePhysics(false);
	itemMesh->SetMassOverrideInKg(TEXT("GripPoint"),2.0f);
	itemMesh->bGenerateOverlapEvents = true;

}

// Called when the game starts or when spawned
void AItem::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AItem::EnableItemPhisics()
{

	itemMesh->SetSimulatePhysics(true);
	itemMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	itemMesh->bGenerateOverlapEvents = true;
}

void AItem::DisableItemPhisics()
{
	itemMesh->SetSimulatePhysics(false);
	itemMesh->bGenerateOverlapEvents = false;
	itemMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	itemMesh->ResetRelativeTransform();
}

