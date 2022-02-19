#include <cassert>

#include "DxLib.h"

#include "Scene/Game/GameAssets.h"
#include "Scene/Game/GameManager.h"
#include "Scene/Game/GameReady.h"

namespace Scene {
	namespace Game {
		GameReady::GameReady(GameManager* gm) : mGameManager(gm) {
			mReadyGH = DxLib::LoadGraph("data/img/ready.png");
			assert(mReadyGH != -1);
			mGoGH = DxLib::LoadGraph("data/img/go.png");
			assert(mGoGH != -1);
			mGameAssets = GameAssets::instance();
			mCount = 0;
			mReadyTime = 1 * 60;
			mGoTime = 1 * 60;
			mX = 321;
			mY = 246;
		}

		GameReady::~GameReady() {
			DxLib::DeleteGraph(mReadyGH);
			DxLib::DeleteGraph(mGoGH);
		}

		void GameReady::update() {
			if (mCount >= mReadyTime + mGoTime) mGameManager->moveTo(GameManager::SCENE_GAMEPLAY);
			++mCount;
		}

		void GameReady::draw() const {
			DxLib::DrawGraph(0, 0, mGameAssets->getBackground(), FALSE);
			if (mCount < mReadyTime) {
				DxLib::DrawGraph(mX, mY, mReadyGH, TRUE);
			}
			else if (mCount >= mReadyTime) {
				DxLib::DrawGraph(mX, mY, mGoGH, TRUE);
			}
		}
	}
}
