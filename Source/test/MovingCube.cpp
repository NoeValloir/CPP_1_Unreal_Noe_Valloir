#include "MovingCube.h"

// Constructor
AMovingCube::AMovingCube()
{
    PrimaryActorTick.bCanEverTick = true;

    // Create the static mesh component
    CubeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CubeMesh"));
    RootComponent = CubeMesh;

    // Load a default cube mesh
    static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMeshAsset(TEXT("/Engine/BasicShapes/Cube"));
    if (CubeMeshAsset.Succeeded())
    {
        CubeMesh->SetStaticMesh(CubeMeshAsset.Object);
    }
}

// Called when the game starts
void AMovingCube::BeginPlay()
{
    Super::BeginPlay();

    // Store the initial position of the cube
    InitialLocation = GetActorLocation();
}

// Called every frame
void AMovingCube::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // Increment time based on DeltaTime
    TimeElapsed += DeltaTime * OscillationSpeed;

    // Create a sinusoidal motion along the Z axis
    FVector NewLocation = InitialLocation;
    NewLocation.Z += FMath::Sin(TimeElapsed) * OscillationAmplitude;

    // Create a circular motion on the horizontal plane (X, Y)
    NewLocation.X += FMath::Cos(TimeElapsed) * CircleRadius;
    NewLocation.Y += FMath::Sin(TimeElapsed) * CircleRadius;

    // Apply the new location
    SetActorLocation(NewLocation);
}