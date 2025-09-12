// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_ReloadBullet.h"
#include "Character/CPP_Player.h"
#include "Character/Enemy/CPP_AICharacter.h"
#include "Item/Weapon/CPP_Basegun.h"
#include "KJHTPSPF.h"

void UCPP_ReloadBullet::Notify(USkeletalMeshComponent* Mesh, UAnimSequenceBase* Anim)
{
	if (AActor* Owner = Mesh->GetOwner())
	{
		if (ACPP_Player* Player = Cast<ACPP_Player>(Owner))
		{
			if (Player->GetWeaponType() == ECharacterWeapon::Machinegun)
			{
				Player->ReloadBullet(Player->GetNeedBulletQuantity());
				Player->SetNeedBulletQuantity();
			}
			else if (Player->GetWeaponType() == ECharacterWeapon::Shotgun)
			{
				auto Shotgun = Cast<ACPP_Basegun>(Player->GetWeapon(Player->GetWeaponType()));
				int ReloadShotGunBullet = Shotgun->GetCurrentBullet();
				Player->ReloadBullet(++ReloadShotGunBullet);
				if (ReloadShotGunBullet >= Player->GetNeedBulletQuantity())
				{
					Player->SetNeedBulletQuantity();
					Mesh->GetAnimInstance()->Montage_JumpToSection(TEXT("EndReload"), Player->GetCurrentMontage());
					Shotgun->GetSkeletalMesh()->GetAnimInstance()->Montage_JumpToSection
						(
							TEXT("EndReload"),
							Shotgun->GetSkeletalMesh()->GetAnimInstance()->GetCurrentActiveMontage()
						);
					}
				}
			}
			else if (ACPP_AICharacter* AI = Cast<ACPP_AICharacter>(Owner))
			{
				AI->ReloadBullet(AI->GetNeedBulletQuantity());
				AI->SetNeedBulletQuantity();
			}
		}
	}
