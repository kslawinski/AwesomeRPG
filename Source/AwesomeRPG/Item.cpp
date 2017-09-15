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

	itemMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	//itemMesh->SetSimulatePhysics(true);

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
	itemMesh->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
}

