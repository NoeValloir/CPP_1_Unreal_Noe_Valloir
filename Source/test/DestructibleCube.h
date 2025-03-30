#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DestructibleInterfacee.h"
#include "DestructibleCube.generated.h"

UCLASS()
class TEST_API ADestructibleCube : public AActor, public IDestructibleInterfacee
{
    GENERATED_BODY()

public:
    ADestructibleCube();

protected:
    virtual void BeginPlay() override;

public:
    UFUNCTION()
    void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
        UPrimitiveComponent* OtherComp, FVector NormalImpulse,
        const FHitResult& Hit);

    virtual void DestroyObject_Implementation() override;

    UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent* CubeMesh;
};
