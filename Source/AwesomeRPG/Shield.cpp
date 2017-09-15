// Fill out your copyright notice in the Description page of Project Settings.

#include "AwesomeRPG.h"
#include "Shield.h"

AShield::AShield()
{
	const ConstructorHelpers::FObjectFinder<UStaticMesh> MeshObj(TEXT("StaticMesh'/Game/Mesh/LowPolyKnight/LowPoly_Knight_Shield.LowPoly_Knight_Shield'")); // load a mesh from a file
	itemMesh->SetStaticMesh(MeshObj.Object);
}


