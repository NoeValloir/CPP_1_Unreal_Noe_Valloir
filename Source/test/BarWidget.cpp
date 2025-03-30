#include "BarWidget.h"
#include "Components/ProgressBar.h"
#include "Blueprint/UserWidget.h"

void UBarWidget::NativeConstruct()
{
    Super::NativeConstruct();

    // Vérifie si ProgressBar est bien récupérée depuis le Blueprint
    if (ProgressBar)
    {
        UE_LOG(LogTemp, Warning, TEXT("ProgressBar récupérée avec succès !"));
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("ProgressBar non trouvée !"));
    }
}

void UBarWidget::SetPercent(const float& Percent)
{
    if (ProgressBar)
    {
        // Limite le pourcentage entre 0.0 et 1.0
        float ClampedPercent = FMath::Clamp(Percent, 0.0f, 1.0f);

        // Mets à jour la ProgressBar avec le pourcentage
        ProgressBar->SetPercent(ClampedPercent);
    }
}
