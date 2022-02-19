#pragma once

namespace Scene {
	namespace Game {
		class AnimationHandler;
		class GameAssets {
		public:
			static GameAssets* instance() { return mInstance; }
			static void create();
			static void destroy();
			GameAssets(const GameAssets&) = delete;
			void operator=(const GameAssets&) = delete;
			const int& getUfo() const { return mUfoGH; }
			const int& getBackground() const { return mBackgroundGH; }
			const int& getAsteroid() const { return mAsteroid; }
			const int& getScoreFont() const { return mScoreFont; }
			void update();
			void draw() const;
			void reset();
			bool hasStateFixAnimation() const;
			bool hasAnimation() const;
			void explode(int x, int y, int page_repeat, int repeat=1, bool fix_state=false);
		private:
			GameAssets();
			~GameAssets();
			int mUfoGH;
			int mBackgroundGH;
			int mAsteroid;
			int mScoreFont;
			AnimationHandler* mAnimationHandler;
			static GameAssets* mInstance;
		};
	}
}
