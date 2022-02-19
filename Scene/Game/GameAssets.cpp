#include <cassert>

#include "DxLib.h"

#include "Scene/Game/GameAssets.h"
#include "Scene/Game/AnimationHandler.h"

namespace Scene {
	namespace Game {
		GameAssets* GameAssets::mInstance = nullptr;

		void GameAssets::create() {
			assert(mInstance == nullptr);
			mInstance = new GameAssets();
		}

		void GameAssets::destroy() {
			delete mInstance;
			mInstance = nullptr;
		}

		void GameAssets::update() {
			mAnimationHandler->update();
		}

		void GameAssets::draw() const {
			mAnimationHandler->draw();
		}

		void GameAssets::reset() {
			mAnimationHandler->clear();
		}

		bool GameAssets::hasStateFixAnimation() const {
			return mAnimationHandler->hasStateFixAnimation();
		}

		bool GameAssets::hasAnimation() const {
			return mAnimationHandler->hasAnimation();
		}

		GameAssets::GameAssets() {
			mUfoGH = DxLib::LoadGraph("data/img/UFO.png");
			assert(mUfoGH != -1);
			mBackgroundGH = DxLib::LoadGraph("data/img/background.png");
			assert(mBackgroundGH != -1);
			mAsteroid = DxLib::LoadGraph("data/img/asteroid.png");
			assert(mAsteroid != -1);
			mAnimationHandler = new AnimationHandler();
			mScoreFont = DxLib::CreateFontToHandle("Arial", 30, 7);
			assert(mScoreFont != -1);
		}

		GameAssets::~GameAssets() {
			DxLib::DeleteGraph(mUfoGH);
			DxLib::DeleteGraph(mBackgroundGH);
			DxLib::DeleteGraph(mAsteroid);
		}

		void GameAssets::explode(int x, int y, int page_repeat, int repeat, bool fix_state) {
			mAnimationHandler->explode(x, y, page_repeat, repeat, fix_state);
		}
	}
}
