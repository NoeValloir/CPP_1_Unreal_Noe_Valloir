#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "RPGHUD.generated.h"

// Forward declaration pour UBarWidget
class UBarWidget;

UCLASS()
class TEST_API ARPGHUD : public AHUD
{
    GENERATED_BODY()

protected:
    virtual void BeginPlay() override;

public:
    // Fonction utilisable en Blueprint pour mettre � jour le pourcentage de la ProgressBar
    UFUNCTION(BlueprintCallable, Category = "UI")
    void SetPercent(float Percent);

private:
    // Instance du widget BarWidget cr��e au runtime
    UPROPERTY()
    UBarWidget* BarWidget;

    // Classe (prefab) du widget BarWidget, �ditable dans l'�diteur
    UPROPERTY(EditAnywhere, Category = "UI")
    TSubclassOf<UBarWidget> BarWidgetClass;
};
