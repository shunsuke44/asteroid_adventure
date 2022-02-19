#pragma once

#include "Scene/AbstractScene.h"

namespace Scene {
	namespace Game {
		class GameAssets;
		class GameManager;
		class PlayRecorder;
		class State;
		class GamePlay : public AbstractScene {
		public:
			GamePlay(GameManager* p, State* s, PlayRecorder& pr);
			~GamePlay() = default;
			void update();
			void draw() const;
			void reset();
			inline unsigned int getInput(char* buf);
		private:
			GameManager* mGameManager;
			State* mState;
			GameAssets* mGameAssets;
			PlayRecorder& mPlayRecorder;
			bool mPrevPause;
		};
	}
}
