#include <cassert>

#include "DxLib.h"

#include "Scene/SceneManager.h"
#include "Scene/Game/GameManager.h"
#include "Scene/Game/GameOver.h"

namespace Scene {
	namespace Game {
		GameOver::GameOver(GameManager* gm) : mGameManager(gm) {
			mGraphicHandle = DxLib::LoadGraph("data/img/gameover.png");
			assert(mGraphicHandle != -1);
		}

		GameOver::~GameOver() {
			DxLib::DeleteGraph(mGraphicHandle);
		}

		void GameOver::update() {
			char buf[256];
			DxLib::GetHitKeyStateAll(buf);
			if (buf[KEY_INPUT_LCONTROL] || buf[KEY_INPUT_RCONTROL]) {
				if (buf[KEY_INPUT_R]) {
					mGameManager->moveTo(GameManager::SCENE_LASTREPLAY);
					return;
				}
				if (buf[KEY_INPUT_B]) {
					SceneManager::instance()->moveTo(SceneManager::SCENE_TITLE);
					return;
				}
				if (buf[KEY_INPUT_S]) {
					mGameManager->moveTo(GameManager::SCENE_RETRY);
					return;
				}
			}
		}

		void GameOver::draw() const {
			DxLib::DrawGraph(0, 0, mGraphicHandle, FALSE);
		}
	}
}
