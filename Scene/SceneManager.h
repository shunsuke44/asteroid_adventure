#pragma once

namespace Scene {
	class AbstractScene;
	class SceneManager {
	public:
		static SceneManager* instance() { return mInstance; }
		SceneManager(const SceneManager&) = delete;
		void operator=(const SceneManager&) = delete;
		static void create();
		static void destroy();
		int update();
		enum Scene {
			SCENE_TITLE,
			SCENE_TITLE_MENU,
			SCENE_GAME,

			SCENE_DEFAULT,
		};
		void moveTo(Scene next);
	private:
		SceneManager();
		~SceneManager();
		static SceneManager* mInstance;
		AbstractScene* mScene;
		Scene mNext;
	};
}
