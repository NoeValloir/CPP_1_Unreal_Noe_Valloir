#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Math/UnrealMathUtility.h" // For FMath
#include "MovingCube.generated.h"

UCLASS()
class TEST_API AMovingCube : public AActor
{
    GENERATED_BODY()

public:
    // Default constructor
    AMovingCube();

protected:
    // Called when the game starts
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

private:
    // Component for the cube mesh
    UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent* CubeMesh;

    // Speed of the oscillation
    UPROPERTY(EditAnywhere, Category = "Oscillation")
    float OscillationSpeed = 1.0f;

    // Amplitude of the oscillation
    UPROPERTY(EditAnywhere, Category = "Oscillation")
    float OscillationAmplitude = 50.0f;

    // Radius of the circle movement
    UPROPERTY(EditAnywhere, Category = "Movement")
    float CircleRadius = 100.0f;

    // Initial position of the cube
    FVector InitialLocation;

    // Internal time tracker
    float TimeElapsed = 0.0f;
};