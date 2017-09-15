// Fill out your copyright notice in the Description page of Project Settings.

#include "AwesomeRPG.h"
#include "Sword.h"

ASword::ASword()
{
	const ConstructorHelpers::FObjectFinder<UStaticMesh> MeshObj(TEXT("StaticMesh'/Game/Mesh/LowPolyKnight/LowPoly_Knight_Sword.LowPoly_Knight_Sword'")); // load a mesh from a file
	itemMesh->SetStaticMesh(MeshObj.Object);
}


