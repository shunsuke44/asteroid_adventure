#include <algorithm>
#include <cassert>

#include "DxLib.h"

#include "Scene/Game/GameAssets.h"
#include "Scene/Game/GameManager.h"
#include "Scene/Game/GameReplay.h"
#include "Scene/Game/State.h"
#include "Scene/Game/PlayRecorder.h"

namespace Scene {
	namespace Game {
		GameReplay::GameReplay(GameManager* gm, const PlayRecorder& pr) : mGameManager(gm) {
			auto record = pr.getRecord();
			mRecord.resize(record.size());
			std::copy(record.begin(), record.end(), mRecord.begin());
			mState = new State();
			mGameAssets = GameAssets::instance();
			mGameAssets->reset();
			mIdx = 0;
		}

		GameReplay::~GameReplay() {
			delete mState;
			mState = nullptr;
		}

		void GameReplay::update() {
			char buf[256];
			DxLib::GetHitKeyStateAll(buf);
			if (buf[KEY_INPUT_SPACE]) {
				mGameManager->moveTo(GameManager::SCENE_PAUSE);
			}
			if (mGameAssets->hasStateFixAnimation()) {
				mGameAssets->update();
				return;
			}
			mGameAssets->update();
			if (mState->hasCleared()) {
				mGameManager->moveTo(GameManager::SCENE_CLEAR);
				return;
			}
			else if (mState->hasFailed()) {
				mGameManager->moveTo(GameManager::SCENE_GAMEOVER);
				return;
			}
			assert(mIdx < mRecord.size());
			std::pair<int,unsigned int> input = mRecord[mIdx];
			assert(input.first == mIdx && mIdx == mState->getClock());
			mState->update(input.second);
			++mIdx;
		}

		void GameReplay::draw() const {
			mState->draw();
			mGameAssets->draw();
		}
	}
}
