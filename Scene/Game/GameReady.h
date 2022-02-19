#pragma once

#include "Scene/AbstractScene.h"

namespace Scene {
	namespace Game {
		class GameManager;
		class GameAssets;
		class GameReady : public AbstractScene {
		public:
			GameReady(GameManager* gm);
			~GameReady();
			void update();
			void draw() const;
		private:
			GameManager* mGameManager;
			GameAssets* mGameAssets;
			int mX, mY;
			int mReadyGH;
			int mGoGH;
			int mCount;
			int mReadyTime;
			int mGoTime;
		};
	}
}
