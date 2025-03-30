#include "RPGHUD.h"
#include "BarWidget.h"  // Nécessaire pour avoir la définition complète de UBarWidget
#include "Blueprint/UserWidget.h"

void ARPGHUD::BeginPlay()
{
    Super::BeginPlay();

    // Vérifier que le prefab de BarWidget est défini dans l'éditeur
    if (BarWidgetClass)
    {
        // Créer une instance du widget BarWidget
        BarWidget = CreateWidget<UBarWidget>(GetWorld(), BarWidgetClass);

        // Vérifier que l'instance est correctement créée et l'ajouter au viewport
        if (BarWidget)
        {
            BarWidget->AddToViewport();
        }
    }
}

void ARPGHUD::SetPercent(float Percent)
{
    // Vérifier que le widget existe et ensuite appeler sa fonction SetPercent()
    if (BarWidget)
    {
        BarWidget->SetPercent(Percent);
    }
}
