#include "DxLib.h"

#include "Scene/Game/AnimationHandler.h"

namespace Scene {
	namespace Game {
		AnimationHandler::AnimationHandler() {
			DxLib::LoadDivGraph("data/img/explosion.png", 7, 7, 1, 120, 120, mExplosionGH);
		}

		AnimationHandler::~AnimationHandler() {
			for (int i = 0; i < 7; ++i) {
				DxLib::DeleteGraph(mExplosionGH[i]);
			}
		}

		void AnimationHandler::explode(int x, int y, int page_repeat, int repeat, bool fix_state) {
			if (fix_state) {
				mStateFixAnims.push_back(new Explosion(this, x, y, page_repeat));
			}
			else {
				mNormalAnims.push_back(new Explosion(this, x, y, page_repeat));
			}
		}

		void AnimationHandler::update() {
			for (auto iter = mStateFixAnims.begin(); iter != mStateFixAnims.end();) {
				if ((*iter)->update() == 1) {
					delete (*iter);
					iter = mStateFixAnims.erase(iter);
				}
				else ++iter;
			}
			for (auto iter = mNormalAnims.begin(); iter != mNormalAnims.end();) {
				if ((*iter)->update() == 1) {
					delete (*iter);
					iter = mNormalAnims.erase(iter);
				}
				else ++iter;
			}
		}

		void AnimationHandler::draw() const {
			for (auto iter = mStateFixAnims.begin(); iter != mStateFixAnims.end(); ++iter) {
				(*iter)->draw();
			}
			for (auto iter = mNormalAnims.begin(); iter != mNormalAnims.end(); ++iter) {
				(*iter)->draw();
			}
		}

		void AnimationHandler::clear() {
			for (Animation* a : mStateFixAnims) {
				delete a;
				a = nullptr;
			}
			for (Animation* a : mNormalAnims) {
				delete a;
				a = nullptr;
			}
			mStateFixAnims.clear();
			mNormalAnims.clear();
		}

		Explosion::Explosion(AnimationHandler* handler, int x, int y, int page_repeat) : mHandler(handler), 
		mX(x), mY(y), mPageRepeat(page_repeat), mSize(7), idx(0) {}

		int Explosion::update() {
			++idx;
			if (idx >= mSize * mPageRepeat) return 1;
			return 0;
		}

		void Explosion::draw() const {
			DxLib::DrawGraph(mX-60, mY-60, mHandler->getExplosion(idx / mPageRepeat), TRUE);
		}
	}
}

