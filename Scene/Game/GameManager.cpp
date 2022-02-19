#include <Windows.h>
#include "DxLib.h"

#include "Scene/Game/GameClear.h"
#include "Scene/Game/GameAssets.h"
#include "Scene/Game/GameManager.h"
#include "Scene/Game/GameOver.h"
#include "Scene/Game/GamePause.h"
#include "Scene/Game/GamePlay.h"
#include "Scene/Game/GameReady.h"
#include "Scene/Game/GameReplay.h"
#include "Scene/Game/PlayRecorder.h"
#include "Scene/Game/State.h"

namespace Scene {
	namespace Game {
		GameManager::GameManager() : mNext(SCENE_DEFAULT), mPlayRecorder() {
			GameAssets::create();
			mGameAssets = GameAssets::instance();
			mState = new State();
			mGameScene = new GameReady(this);
		}

		GameManager::~GameManager() {
			delete mGameScene;
			mGameScene = nullptr;
			delete mState;
			mState = nullptr;
			GameAssets::destroy();
			mGameAssets = nullptr;
		}

		void GameManager::update() {
			mNext = SCENE_DEFAULT;
			mGameScene->update();
			switch (mNext) {
			case SCENE_GAMEPLAY:
				delete mGameScene;
				mGameScene = new GamePlay(this, mState, mPlayRecorder);
				return;
			case SCENE_RETRY:
				delete mState;
				mState = new State();
				mPlayRecorder.clear();
				delete mGameScene;
				mGameScene = new GameReady(this);
				return;
			case SCENE_PAUSE:
				delete mGameScene;
				mGameScene = new GamePause(this);
				return;
			case SCENE_CLEAR:
				delete mGameScene;
				mGameScene = new GameClear(this);
				return;
			case SCENE_GAMEOVER:
				delete mGameScene;
				mGameScene = new GameOver(this);
				return;
			case SCENE_LASTREPLAY:
				delete mGameScene;
				mGameScene = new GameReplay(this, mPlayRecorder);
				return;
			default:
				return;
			}
		}

		void GameManager::moveTo(Scene next) {
			mNext = next;
		}

		void GameManager::draw() const {
			mGameScene->draw();
		}
	}
}

