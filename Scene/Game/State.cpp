#include "DxLib.h"

#include "Window.h"
#include "Scene/Game/AnimationHandler.h"
#include "Scene/Game/Asteroid.h"
#include "Scene/Game/GameAssets.h"
#include "Scene/Game/Player.h"
#include "Scene/Game/PlayRecorder.h"
#include "Scene/Game/State.h"

namespace Scene {
	namespace Game {
		State::State()
			: mClearTime(60 * 40), // 60FPS‚Å40•b
			  mHasFailed(false),
			  mClock(0)
		{ 
			mGameAssets = GameAssets::instance();
			mPlayer = new Player(mGameAssets->getUfo());
			mAsteroidManager = new AsteroidManager(mGameAssets->getAsteroid(), 40);
		}

		State::~State() {
			delete mPlayer;
			mPlayer = nullptr;
			delete mAsteroidManager;
			mAsteroidManager = nullptr;
		}

		void State::update(unsigned int input) {
			++mClock;
			mPlayer->update(input);
			mAsteroidManager->update();
#ifndef NDEBUG
			if (input & DEBUG_CLEAR) {
				mClock = mClearTime;
				return;
			}
			if (input & DEBUG_FAIL) {
				mHasFailed = true;
				return;
			}
#endif
			if (mAsteroidManager->checkHit(mPlayer) == 1) {
				mGameAssets->explode(mPlayer->getX(), mPlayer->getY(), 8, 1, true);
				mHasFailed = true;
				return;
			}
		}

		void State::drawScore() const {
			int color = DxLib::GetColor(255, 0, 0);
			DxLib::DrawFormatStringToHandle(WINDOW.width - 200, WINDOW.height - 40, color, 
											mGameAssets->getScoreFont(),
											"Time  %4d:%02d", mClock / 60, (mClock % 60) * 100 / 60);
		}

		void State::draw() const {
			DxLib::DrawGraph(0, 0, mGameAssets->getBackground(), FALSE);
			mPlayer->draw();
			mAsteroidManager->draw();
			drawScore();
		}

		void State::reset() {
			mClock = 0;
			mHasFailed = false;
			mPlayer->reset();
			mAsteroidManager->reset();
		}
	}
}
