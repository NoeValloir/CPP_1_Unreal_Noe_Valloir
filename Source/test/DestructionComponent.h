#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DestructionComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TEST_API UDestructionComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    // Constructeur
    UDestructionComponent();

protected:
    virtual void BeginPlay() override;

public:
    // Fonction appel�e pour le rayon de destruction
    UFUNCTION(BlueprintCallable, Category = "Destruction")
    void DestructionBeam();

private:
    // Port�e du rayon destructeur (modifiable dans l'�diteur)
    UPROPERTY(EditAnywhere, Category = "Destruction", meta = (ClampMin = "0.0", ClampMax = "5000.0"))
    float DestructionRange;

    // Cam�ra associ�e pour lancer le rayon
    UPROPERTY(EditAnywhere, Category = "Destruction")
    class UCameraComponent* Camera;

    // Fonction pour g�rer la destruction
    void HandleDestruction(const FHitResult& Hit);

public:
    UFUNCTION(BlueprintCallable, Category = "Destruction")
    void SetCamera(UCameraComponent* InCamera);


};
