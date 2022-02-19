#pragma once

#include <cassert>
#include <vector>

namespace Scene {
	namespace Game {
		class Animation;
		class AnimationHandler {
		public:
			AnimationHandler();
			~AnimationHandler();
			void explode(int x, int y, int page_repeat, int repeat = 1, bool fix_state = false);
			void update();
			void draw() const;
			bool hasStateFixAnimation() const { return mStateFixAnims.size() > 0; }
			bool hasAnimation() const { return mStateFixAnims.size() > 0 || mNormalAnims.size() > 0; }
			const int& getExplosion(const int& idx) const {
				assert(idx >= 0 && idx < 7);
				return mExplosionGH[idx];
			}
			void clear();
		private:
			int mExplosionGH[7];
			std::vector<Animation*> mStateFixAnims;
			std::vector<Animation*> mNormalAnims;
		};

		class Animation {
		public:
			Animation() {}
			virtual ~Animation() {}
			virtual int update() = 0;
			virtual void draw() const = 0;
		};

		class Explosion : public Animation {
		public:
			Explosion(AnimationHandler* handler, int x, int y, int page_repeat);
			~Explosion() {}
			int update();
			void draw() const;
		private:
			AnimationHandler* mHandler;
			const int mX, mY;
			const int mPageRepeat;
			const int mSize;
			int idx;
		};
	}
}
