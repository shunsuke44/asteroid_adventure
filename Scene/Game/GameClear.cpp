#include <cassert>

#include "DxLib.h"

#include "Scene/SceneManager.h"
#include "Scene/Game/GameClear.h"
#include "Scene/Game/GameManager.h"

namespace Scene {
	namespace Game {
		GameClear::GameClear(GameManager* gm) : mGameManager(gm) {
			mGraphicHandle = DxLib::LoadGraph("data/img/clear.png");
			assert(mGraphicHandle != -1);
			mKeybindGH = DxLib::LoadGraph("data/img/clear_keybind.png");
			assert(mKeybindGH != -1);
		}

		GameClear::~GameClear() {
			DxLib::DeleteGraph(mGraphicHandle);
		}

		void GameClear::update() {
			char buf[256];
			DxLib::GetHitKeyStateAll(buf);
			if (buf[KEY_INPUT_LCONTROL] || buf[KEY_INPUT_RCONTROL]) {
				if (buf[KEY_INPUT_R]) {
					mGameManager->moveTo(GameManager::SCENE_LASTREPLAY);
				}
				if (buf[KEY_INPUT_S]) {
					SceneManager::instance()->moveTo(SceneManager::SCENE_TITLE);
				}
			}
		}

		void GameClear::draw() const {
			DxLib::DrawGraph(0, 0, mGraphicHandle, FALSE);
			DxLib::DrawGraph(700, 644, mKeybindGH, TRUE);
		}
	}
}
