#include "BasicPawn.h"
#include "Components/StaticMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Constructeur
ABasicPawn::ABasicPawn()
{
    // Crée le root component
    Root = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
    RootComponent = Root;

    // Crée le mesh de cube et l'attache au root
    CubeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CubeMesh"));
    CubeMesh->SetupAttachment(RootComponent);

    // Assigne un mesh de base au cube
    static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMeshAsset(TEXT("/Engine/BasicShapes/Cube.Cube"));
    if (CubeMeshAsset.Succeeded())
    {
        CubeMesh->SetStaticMesh(CubeMeshAsset.Object);
    }

    // Crée la caméra et l'attache au root
    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera->SetupAttachment(RootComponent);

    // Permet de contrôler le Pawn avec le joueur
    AutoPossessPlayer = EAutoReceiveInput::Player0;

    // Initialisation des valeurs de vitesse et rotation
    CurrentVelocity = FVector::ZeroVector;
    CurrentRotation = FRotator::ZeroRotator;
}

void ABasicPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    // Lier les axes d'entrée à des fonctions
    PlayerInputComponent->BindAxis("MoveForward", this, &ABasicPawn::MoveForward);
    PlayerInputComponent->BindAxis("Turn", this, &ABasicPawn::Turn);
}

// Fonction pour avancer/reculer
void ABasicPawn::MoveForward(float Value)
{
    if (Value != 0.0f)
    {
        // Ajoute la vitesse de déplacement en fonction de la direction (avant/arrière)
        CurrentVelocity.X = FMath::Lerp(CurrentVelocity.X, Value * MoveSpeed, MoveInertia * GetWorld()->GetDeltaSeconds());
    }
    else
    {
        // Si la valeur est 0, on arrête progressivement le mouvement
        CurrentVelocity.X = FMath::Lerp(CurrentVelocity.X, 0.0f, MoveInertia * GetWorld()->GetDeltaSeconds());
    }
}

// Fonction pour tourner
void ABasicPawn::Turn(float Value)
{
    if (Value != 0.0f)
    {
        // Applique l'inertie pour tourner
        CurrentRotation.Yaw = FMath::Lerp(CurrentRotation.Yaw, Value * TurnSpeed, TurnInertia * GetWorld()->GetDeltaSeconds());
    }
    else
    {
        // Si la valeur est 0, on arrête progressivement la rotation
        CurrentRotation.Yaw = FMath::Lerp(CurrentRotation.Yaw, 0.0f, TurnInertia * GetWorld()->GetDeltaSeconds());
    }
}

void ABasicPawn::ApplyInertia(float DeltaTime)
{
    // Applique l'inertie à la position et la rotation
    AddActorLocalOffset(CurrentVelocity * DeltaTime, true);
    AddActorLocalRotation(CurrentRotation, true);
}

void ABasicPawn::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    ApplyInertia(DeltaTime);
}
