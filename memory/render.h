#pragma once

#include "../stdafx.h"

static inline void MainLoop(SDK::UCanvas* pCanvas)
{
	if (!ue->SetObjects()) return;

	ue->PlayerController->GetViewportSize(&width, &height);

	pCanvas->K2_DrawLine(SDK::FVector2D(width / 2 - 12, height / 2), SDK::FVector2D(width / 2 - 2, height / 2), 2.0f, SDK::FLinearColor(255.0f, 255.0f, 255.0f, 255.0f));
	pCanvas->K2_DrawLine(SDK::FVector2D(width / 2 + 13, height / 2), SDK::FVector2D(width / 2 + 3, height / 2), 2.0f, SDK::FLinearColor(255.0f, 255.0f, 255.0f, 255.0f));
	pCanvas->K2_DrawLine(SDK::FVector2D(width / 2, height / 2 - 12), SDK::FVector2D(width / 2, height / 2 - 2), 2.0f, SDK::FLinearColor(255.0f, 255.0f, 255.0f, 255.0f));
	pCanvas->K2_DrawLine(SDK::FVector2D(width / 2, height / 2 + 13), SDK::FVector2D(width / 2, height / 2 + 3), 2.0f, SDK::FLinearColor(255.0f, 255.0f, 255.0f, 255.0f));
	auto MyPlayer = (SDK::APortalWarsCharacter*)ue->PlayerController->K2_GetPawn();
	auto CamManager = ue->PlayerController->PlayerCameraManager;
	float closestDistance = FLT_MAX;
	SDK::APortalWarsCharacter* closestEnemyDist = 0;

	SDK::TArray<SDK::AActor*> actors;

	ue->GPStatics->STATIC_GetAllActorsOfClass(ue->World, (SDK::AActor*)SDK::APortalWarsCharacter::StaticClass(), &actors);

	for (int i = 0; i < actors.Num(); i++) {

		SDK::APortalWarsCharacter* enemies = (SDK::APortalWarsCharacter*)actors[i];

		if (enemies)
		{
			auto EnemyMesh = enemies->Mesh;

			SDK::FVector ActorLoc = enemies->K2_GetActorLocation();
			unrealengine::DrawBoundingBox(pCanvas, enemies, SDK::FLinearColor{ 255.f, 0.f, 0.f, 1 });

			if (MyPlayer) {
				bool iscollision = false;
				if (SDK::Syscall::NtGetAsyncKeyState(VK_XBUTTON1)) iscollision = !iscollision;
					
				if (iscollision) MyPlayer->bActorEnableCollision = false;
				else if (!iscollision) MyPlayer->bActorEnableCollision = true;

				MyPlayer->CharacterMovement->MaxWalkSpeed = 40.f;
				MyPlayer->CharacterMovement->JumpZVelocity = 40.f;

			}

			if (enemies && SDK::Syscall::NtGetAsyncKeyState(VK_RBUTTON))
			{
				//unrealengine::SeMemoryAimbottAim(CamManager, enemies);
			}
			
		}
	}

	
}

static inline void MainRenderer(SDK::UObject* pObject, SDK::UCanvas* pCanvas)
{
	if (pCanvas) MainLoop(pCanvas);

	return origin_renderer(pObject, pCanvas);
}