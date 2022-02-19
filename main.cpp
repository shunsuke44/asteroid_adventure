#define _USE_MATH_DEFINES
#include <cmath>

#include <Windows.h>
#include "DxLib.h"

#include "Window.h"
#include "buttons.h"
#include "Scene/SceneManager.h"
#include "Scene/Game/GameManager.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	DxLib::ChangeWindowMode(TRUE), DxLib::DxLib_Init(), DxLib::SetDrawScreen(DX_SCREEN_BACK);
	DxLib::SetMainWindowText("アステロイドアドベンチャー");
	DxLib::SetWindowSizeChangeEnableFlag(FALSE, FALSE);
	DxLib::SetGraphMode(WINDOW.width, WINDOW.height, 32);
	DxLib::SetWindowSize(WINDOW.width, WINDOW.height);

	Scene::SceneManager::create();
	Scene::SceneManager* sm = Scene::SceneManager::instance();
	KeyButton::create();

	while (DxLib::ScreenFlip() == 0 && DxLib::ProcessMessage() == 0 && DxLib::ClearDrawScreen() == 0) {
		if (sm->update()) break;
	}

	KeyButton::destroy();
	DxLib::DxLib_End();
	return 0;
}
