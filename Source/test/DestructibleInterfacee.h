#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "DestructibleInterfacee.generated.h"

UINTERFACE(MinimalAPI, Blueprintable)
class UDestructibleInterfacee : public UInterface
{
    GENERATED_BODY()
};

class TEST_API IDestructibleInterfacee
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Destructible")
    void DestroyObject();
};
