#include "DestructibleCube.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "UObject/ConstructorHelpers.h"

ADestructibleCube::ADestructibleCube()
{
    PrimaryActorTick.bCanEverTick = true;

    // ✅ Crée le mesh du cube
    CubeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CubeMesh"));
    RootComponent = CubeMesh;

    // ✅ Utilise le cube de base d'Unreal
    static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMeshAsset(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
    if (CubeMeshAsset.Succeeded())
    {
        CubeMesh->SetStaticMesh(CubeMeshAsset.Object);
        CubeMesh->SetRelativeScale3D(FVector(1.f));
        UE_LOG(LogTemp, Warning, TEXT("Cube mesh chargé avec succès !"));
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Erreur de chargement du mesh !"));
    }

    // ✅ Configuration des collisions
    CubeMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    CubeMesh->SetCollisionResponseToAllChannels(ECR_Block);
    CubeMesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

    // ✅ Lier la fonction OnHit à l'événement de collision
    CubeMesh->OnComponentHit.AddDynamic(this, &ADestructibleCube::OnHit);
}

void ADestructibleCube::BeginPlay()
{
    Super::BeginPlay();
}

void ADestructibleCube::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, FVector NormalImpulse,
    const FHitResult& Hit)
{
    if (OtherActor && OtherActor != this)
    {
        UE_LOG(LogTemp, Warning, TEXT("Collision détectée !"));
        DestroyObject_Implementation(); // ✅ Détruit le cube lors de la collision
    }
}

void ADestructibleCube::DestroyObject_Implementation()
{
    UE_LOG(LogTemp, Warning, TEXT("Cube détruit !"));
    Destroy(); // ✅ Détruit l'actor
}
