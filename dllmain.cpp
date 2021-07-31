#include "stdafx.h"

void main() {
	/***************-UWORLD-**********************/
	ue->GWorld = (SDK::UWorld**)((DWORD64)GetModuleHandleW(NULL) + 0x505D150);
	printf("GWorld: 0x%x\n", ue->GWorld - (SDK::UWorld**)GetModuleHandleW(nullptr));
	/********************************************/

	/***************-GObjects-**********************/
	SDK::UObject::GObjects = (SDK::FUObjectArray*)((DWORD64)GetModuleHandleW(NULL) + 0x4F182B0);
	printf("GObjects: 0x%x\n", SDK::UObject::GObjects - (SDK::FUObjectArray*)GetModuleHandleW(nullptr));
	/**********************************************/

	/***************-GNames-**********************/
	auto FNames = hooking::FindPattern(GetModuleHandleW(NULL), "\x41\xb8\x00\x00\x00\x00\xe8\x00\x00\x00\x00\x48\x8b\xc3\x48\x83\xc4\x00\x5b\xc3\x48\x8b\x42", "xx????x????xxxxxx?xxxxx", 0);
	SDK::FName::GNames = reinterpret_cast<SDK::TNameEntryArray*>(FNames - 0x3F);
	printf("GNames: 0x%x\n", SDK::FName::GNames - (SDK::TNameEntryArray*)GetModuleHandleW(nullptr));
	/*********************************************/

	/***************-BoneMatrix-*******************/
	auto GetBoneMatrix = hooking::FindPattern(GetModuleHandleW(nullptr), "\xE8\x00\x00\x00\x00\x48\x8B\x47\x30\xF3\x0F\x10\x45\x00",
		("x????xxxxxxxx?"), 0);
	ue->GetBoneMatrix = reinterpret_cast<decltype(ue->GetBoneMatrix)>(rva(GetBoneMatrix, 5));
	printf("GetBoneMatrix: 0x%x\n", ue->GetBoneMatrix - (PBYTE)GetModuleHandleW(nullptr));
	/*********************************************/

	/***************-Post render-**********************/
	SDK::UWorld* World = *ue->GWorld;
	auto GameInstance = World->OwningGameInstance;
	auto LocalPlayer = GameInstance->LocalPlayers[0];
	auto ViewportClient = LocalPlayer->ViewportClient;
	// swapping vtables
	auto vTable = *(void***)(ViewportClient);
	origin_renderer = (PostRender_t)vTable[100];
	hook->SwapVtable((void*)ViewportClient, 100, MainRenderer);
	printf("ViewportClient: 0x%x\n", ViewportClient - (SDK::UGameViewportClient*)GetModuleHandleW(nullptr));
	/*************************************************/
}

BOOL WINAPI DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved) {
	if (dwReason == 1) {
		AllocConsole();
		freopen("conin$", "r", stdin);
		freopen("conout$", "w", stdout);
		freopen("conout$", "w", stderr);
		main();
	}
	return true;
}