// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_Blackboard.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"

UCPP_Blackboard::UCPP_Blackboard()
{
	FBlackboardEntry Key;

	Key.EntryName = TEXT("Target");
	Key.KeyType = NewObject<UBlackboardKeyType_Object>();
	Keys.Add(Key);

	Key.EntryName = TEXT("PerceptionStartedPoint");
	Key.KeyType = NewObject<UBlackboardKeyType_Vector>();
	Keys.Add(Key);
}
