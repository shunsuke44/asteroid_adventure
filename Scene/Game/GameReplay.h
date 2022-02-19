#pragma once

#include <utility>
#include <vector>

#include "Scene/AbstractScene.h"

namespace Scene {
	namespace Game {
		class GameAssets;
		class GameManager;
		class PlayRecorder;
		class State;
		class GameReplay : public AbstractScene {
		public:
			GameReplay(GameManager* gm, const PlayRecorder& pr);
			~GameReplay();
			void update();
			void draw() const;
		private:
			GameManager* mGameManager;
			State* mState;
			GameAssets* mGameAssets;
			std::vector<std::pair<int, unsigned int>> mRecord;
			int mIdx;
		};
	}
}
