#include "DestructionComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "DestructibleInterfacee.h"  // Interface de destruction
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"  // Importer SpringArmComponent

UDestructionComponent::UDestructionComponent()
{
    PrimaryComponentTick.bCanEverTick = true;

    // Valeurs par défaut
    DestructionRange = 1000.0f;
    Camera = nullptr;
}

void UDestructionComponent::BeginPlay()
{
    Super::BeginPlay();

    // Si la caméra n'est pas définie dans l'éditeur, essaye de la récupérer automatiquement
    if (!Camera)
    {
        AActor* Owner = GetOwner();
        if (Owner)
        {
            // Recherche le composant SpringArm attaché à l'actor propriétaire
            USpringArmComponent* SpringArm = Owner->FindComponentByClass<USpringArmComponent>();
            if (SpringArm)
            {
                // Récupérer la caméra attachée au SpringArm
                Camera = Cast<UCameraComponent>(SpringArm->GetChildComponent(0));  // Récupère la première caméra attachée au SpringArm
                if (Camera)
                {
                    UE_LOG(LogTemp, Warning, TEXT("Camera liée automatiquement !"));
                }
                else
                {
                    UE_LOG(LogTemp, Error, TEXT("Aucune caméra trouvée sur le SpringArm !"));
                }
            }
            else
            {
                UE_LOG(LogTemp, Error, TEXT("Aucun SpringArm trouvé sur l'actor propriétaire !"));
            }
        }
    }
}

void UDestructionComponent::DestructionBeam()
{
    if (!Camera) return;

    // Position de départ = position de la caméra
    FVector Start = Camera->GetComponentLocation();

    // Direction du regard → portée multipliée par DestructionRange
    FVector End = Start + Camera->GetForwardVector() * DestructionRange;

    // Structure pour stocker le résultat du Line Trace
    FHitResult HitResult;

    // Paramètres de collision (on ignore l'owner du component)
    FCollisionQueryParams Params;
    Params.AddIgnoredActor(GetOwner());

    // Effectuer le Line Trace
    bool bHit = GetWorld()->LineTraceSingleByChannel(
        HitResult,       // Résultat
        Start,           // Point de départ
        End,             // Point d'arrivée
        ECC_Visibility,  // Canal de collision
        Params           // Paramètres
    );

    //  Affichage du Line Trace dans le monde (DEBUG)
    DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 1.0f, 0, 2.0f);

    if (bHit) // Si le trace touche quelque chose
    {
        // Récupérer l'Actor touché
        AActor* HitActor = HitResult.GetActor();

        if (HitActor)
        {
            //  Vérification si l'Actor implémente l'interface
            if (HitActor->GetClass()->ImplementsInterface(UDestructibleInterfacee::StaticClass()))
            {
                //   Exécuter la destruction via l'interface
                IDestructibleInterfacee* Destructible = Cast<IDestructibleInterfacee>(HitActor);
                if (Destructible)
                {
                    UE_LOG(LogTemp, Warning, TEXT("DestructionBeam: Objet destructible détecté !"));
                    Destructible->Execute_DestroyObject(HitActor);
                }
            }
        }
    }
}

void UDestructionComponent::SetCamera(UCameraComponent* InCamera)
{
    if (InCamera)
    {
        Camera = InCamera;
    }
}
