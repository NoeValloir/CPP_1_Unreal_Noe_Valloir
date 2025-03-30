#include "BarWidget.h"
#include "Components/ProgressBar.h"
#include "Blueprint/UserWidget.h"

void UBarWidget::NativeConstruct()
{
    Super::NativeConstruct();

    // V�rifie si ProgressBar est bien r�cup�r�e depuis le Blueprint
    if (ProgressBar)
    {
        UE_LOG(LogTemp, Warning, TEXT("ProgressBar r�cup�r�e avec succ�s !"));
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("ProgressBar non trouv�e !"));
    }
}

void UBarWidget::SetPercent(const float& Percent)
{
    if (ProgressBar)
    {
        // Limite le pourcentage entre 0.0 et 1.0
        float ClampedPercent = FMath::Clamp(Percent, 0.0f, 1.0f);

        // Mets � jour la ProgressBar avec le pourcentage
        ProgressBar->SetPercent(ClampedPercent);
    }
}
