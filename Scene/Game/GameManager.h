#pragma once

#include "Scene/AbstractScene.h"
#include "Scene/Game/PlayRecorder.h"

namespace Scene {
	namespace Game {
		class GameAssets;
		class GameScene;
		class PlayRecorder;
		class State;
		class GameManager : public AbstractScene {
		public:
			GameManager();
			~GameManager();
			void update();
			void draw() const;
			enum Scene {
				SCENE_GAMEPLAY,
				SCENE_PAUSE,
				SCENE_RETRY,
				SCENE_CLEAR,
				SCENE_GAMEOVER,
				SCENE_LASTREPLAY,

				SCENE_DEFAULT,
			};
			void moveTo(Scene next);
		private:
			GameAssets* mGameAssets;
			AbstractScene* mGameScene;
			PlayRecorder mPlayRecorder;
			State* mState;
			Scene mNext;
		};
	}
}
