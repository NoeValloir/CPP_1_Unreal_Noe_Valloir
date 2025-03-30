#include "RPGHUD.h"
#include "BarWidget.h"  // N�cessaire pour avoir la d�finition compl�te de UBarWidget
#include "Blueprint/UserWidget.h"

void ARPGHUD::BeginPlay()
{
    Super::BeginPlay();

    // V�rifier que le prefab de BarWidget est d�fini dans l'�diteur
    if (BarWidgetClass)
    {
        // Cr�er une instance du widget BarWidget
        BarWidget = CreateWidget<UBarWidget>(GetWorld(), BarWidgetClass);

        // V�rifier que l'instance est correctement cr��e et l'ajouter au viewport
        if (BarWidget)
        {
            BarWidget->AddToViewport();
        }
    }
}

void ARPGHUD::SetPercent(float Percent)
{
    // V�rifier que le widget existe et ensuite appeler sa fonction SetPercent()
    if (BarWidget)
    {
        BarWidget->SetPercent(Percent);
    }
}
