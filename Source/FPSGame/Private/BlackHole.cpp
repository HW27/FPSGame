// Fill out your copyright notice in the Description page of Project Settings.

#include "BlackHole.h"
#include "Runtime/Engine/Classes/GameFramework/Actor.h"

// Sets default values
ABlackHole::ABlackHole()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	RootComponent = MeshComponent;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SphereComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	SphereComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	SphereComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ABlackHole::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABlackHole::NotifyActorBeginOverlap(AActor * OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

}

void ABlackHole::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SphereComponent->GetOverlappingActors(OverlappingActors);

	for (auto Actor : OverlappingActors)
	{
		
		UStaticMeshComponent* MeshComp = Cast<UStaticMeshComponent>(Actor->GetRootComponent());
		if (MeshComp != nullptr)
			MeshComp->AddRadialForce(GetActorLocation(), 500.f, 20000.f, ERadialImpulseFalloff::RIF_Linear, true);
	}
}
