#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BarWidget.generated.h"

class UProgressBar;

UCLASS()
class TEST_API UBarWidget : public UUserWidget
{
    GENERATED_BODY()

protected:
    virtual void NativeConstruct() override;

public:
    // Fonction pour mettre à jour le pourcentage de la barre de progression
    UFUNCTION(BlueprintCallable, Category = "UI")
    void SetPercent(const float& Percent);

private:
    // Référence à la barre de progression
    UPROPERTY(meta = (BindWidget))
    UProgressBar* ProgressBar; // Le widget ProgressBar lié à ton BP_BarWidget

};
