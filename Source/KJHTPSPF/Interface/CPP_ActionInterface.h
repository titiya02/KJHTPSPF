// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CPP_ActionInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UCPP_ActionInterface : public UInterface
{
	GENERATED_BODY()
};

class KJHTPSPF_API ICPP_ActionInterface
{
	GENERATED_BODY()

public:
	virtual void BeginActionAStarted() PURE_VIRTUAL(BeginActionAStarted,);
	virtual void BeginActionACompleted() PURE_VIRTUAL(BeginActionACompleted, );
};
