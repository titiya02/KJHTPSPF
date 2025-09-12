// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_Bullet.h"
#include "KJHTPSPF.h"
#include "GameFramework/ProjectileMovementComponent.h"

ACPP_Bullet::ACPP_Bullet()
{
	SetRootComponent(AssignDefaultSubobject(Mesh));
	ItemCollision->SetupAttachment(Mesh);
}

EBulletType ACPP_Bullet::GetBulletType() const
{
	return BulletType;
}

void ACPP_Bullet::BeginActionAStarted()
{
	Super::BeginActionAStarted();
}

void ACPP_Bullet::BeginActionACompleted()
{
	Super::BeginActionACompleted();
}
