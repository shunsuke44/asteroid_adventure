#include "DxLib.h"

#include "Scene/Game/GameManager.h"
#include "Scene/Game/GameAssets.h"
#include "Scene/Game/GamePlay.h"
#include "Scene/Game/PlayRecorder.h"
#include "Scene/Game/State.h"

namespace Scene {
	namespace Game {
		GamePlay::GamePlay(GameManager* p, State* s, PlayRecorder& pr)
			: mGameManager(p),
			  mState(s),
			  mPlayRecorder(pr),
			  mPrevPause(true)
		{
			mGameAssets = GameAssets::instance();
			mGameAssets->reset();
		}

		void GamePlay::update() {
			char buf[256];
			DxLib::GetHitKeyStateAll(buf);
			if (buf[KEY_INPUT_SPACE]) {
				if (!mPrevPause) {
					mPrevPause = true;
					mGameManager->moveTo(GameManager::SCENE_PAUSE);
					return;
				}
			}
			else {
				mPrevPause = false;
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
			unsigned int input = getInput(buf);
			mPlayRecorder.record(mState->getClock(), input);
			mState->update(input);
		}

		inline unsigned int GamePlay::getInput(char* buf) {
			unsigned int input = 0;
			if (buf[KEY_INPUT_W]) {
				input |= State::MOVE_UP;
			}
			if (buf[KEY_INPUT_S]) {
				input |= State::MOVE_DOWN;
			}
			if (buf[KEY_INPUT_D]) {
				input |= State::MOVE_RIGHT;
			}
			if (buf[KEY_INPUT_A]) {
				input |= State::MOVE_LEFT;
			}
#ifndef NDEBUG
			if (buf[KEY_INPUT_F1]) {
				input |= State::DEBUG_CLEAR;
			}
			if (buf[KEY_INPUT_F2]) {
				input |= State::DEBUG_FAIL;
			}
#endif
			return input;
		}

		void GamePlay::draw() const {
			mState->draw();
			mGameAssets->draw();
		}

		void GamePlay::reset() {
			mState->reset();
			mGameAssets->reset();
		}
	}
}