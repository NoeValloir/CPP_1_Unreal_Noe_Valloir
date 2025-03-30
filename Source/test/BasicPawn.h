#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/StaticMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"  // Pour un contrôle plus souple de la caméra
#include "BasicPawn.generated.h"

UCLASS()
class TEST_API ABasicPawn : public APawn
{
    GENERATED_BODY()

public:
    ABasicPawn();

protected:
    // Composants
    UPROPERTY(VisibleAnywhere, Category = "Components")
    USceneComponent* Root;

    UPROPERTY(VisibleAnywhere, Category = "Components")
    UStaticMeshComponent* CubeMesh;

    UPROPERTY(VisibleAnywhere, Category = "Components")
    UCameraComponent* Camera;

    // Propriétés pour la vitesse de déplacement et rotation
    UPROPERTY(EditAnywhere, Category = "Movement")
    float MoveSpeed = 500.0f;  // Vitesse de déplacement, modifiable dans l'éditeur

    UPROPERTY(EditAnywhere, Category = "Movement")
    float TurnSpeed = 45.0f;  // Vitesse de rotation, modifiable dans l'éditeur

    // Propriétés pour l'inertie
    UPROPERTY(EditAnywhere, Category = "Movement")
    float MoveInertia = 5.0f;  // Inertie du mouvement, modifiable dans l'éditeur

    UPROPERTY(EditAnywhere, Category = "Movement")
    float TurnInertia = 5.0f;  // Inertie de la rotation, modifiable dans l'éditeur

    // Vitesse actuelle
    FVector CurrentVelocity;
    FRotator CurrentRotation;

public:
    // Déclaration de la fonction Tick
    virtual void Tick(float DeltaTime) override;

    // Fonction SetupPlayerInputComponent pour lier les entrées
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    // Fonctions pour gérer les inputs
    void MoveForward(float Value);
    void Turn(float Value);

    // Appliquer l'inertie
    void ApplyInertia(float DeltaTime);
};
