#include <cassert>

#include "Scene/AbstractScene.h"
#include "Scene/SceneManager.h"
#include "Scene/Title.h"
#include "Scene/TitleMenu.h"
#include "Scene/Game/GameManager.h"

namespace Scene {
	SceneManager* SceneManager::mInstance = nullptr;

	SceneManager::SceneManager() : mNext(SCENE_DEFAULT) {
		mScene = new Title();
	}

	SceneManager::~SceneManager() {
		delete mScene;
	}

	void SceneManager::create() {
		assert(!mInstance);
		mInstance = new SceneManager();
	}

	void SceneManager::destroy() {}

	int SceneManager::update() {
		mNext = SCENE_DEFAULT;
		mScene->update();
		if (mNext == SCENE_DEFAULT) {
			mScene->draw();
		}
		if (mNext == SCENE_TITLE) {
			delete mScene;
			mScene = new Title();
			return 0;
		}
		if (mNext == SCENE_TITLE_MENU) {
			delete mScene;
			mScene = new TitleMenu();
			return 0;
		}
		if (mNext == SCENE_GAME) {
			delete mScene;
			mScene = new Game::GameManager();
			return 0;
		}
		// TODO:
		return 0;
	}

	void SceneManager::moveTo(Scene next) {
		mNext = next;
	}
}
