#pragma once

namespace Scene {
	namespace Game {
		class Player;
		class AsteroidManager;
		class GameAssets;
		class State {
		public:
			State();
			~State();
			enum Input {
				MOVE_UP = 1 << 0,
				MOVE_DOWN = 1 << 1,
				MOVE_LEFT = 1 << 2,
				MOVE_RIGHT = 1 << 3,
				MOVE_INVALID = 1 << 4,
#ifndef NDEBUG
				DEBUG_CLEAR = 1 << 8,
				DEBUG_FAIL  = 1 << 9,
#endif
			};
			void update(unsigned int input);
			void draw() const;
			bool hasCleared() const { return mClock >= mClearTime; }
			bool hasFailed() const { return mHasFailed; }
			void reset();
			const int& getClock() const { return mClock; }
		private:
			void drawScore() const;
			GameAssets* mGameAssets;
			Player* mPlayer;
			AsteroidManager* mAsteroidManager;
			int mClearTime;
			int mClock;
			bool mHasFailed;
		};
	}
}
