#define _USE_MATH_DEFINES
#include <cmath>
#include <cassert>
#include <iostream>

#include "DxLib.h"

#include "Scene/Game/State.h"
#include "Scene/Game/GameAssets.h"
#include "Scene/Game/Player.h"
#include "Window.h"

namespace Scene {
	namespace Game {
		Player::Player(int gh) : mGraphicHandle(gh), mRadius(50.0) {
			mX = WINDOW.width / 2;
			mY = WINDOW.height / 2;
			mSpeed = 10.0;
		}

		void Player::update(unsigned int input) {
			if ((input & State::MOVE_UP) && (input & State::MOVE_DOWN)) {
				input &= (State::MOVE_LEFT | State::MOVE_RIGHT);
			}
			if ((input & State::MOVE_LEFT) && (input & State::MOVE_RIGHT)) {
				input &= (State::MOVE_UP | State::MOVE_DOWN);
			}
			int num_input = 0;
			for (int bit = 1; bit < State::MOVE_INVALID; bit <<= 1) {
				if (input & bit) ++num_input;
			}
			if (num_input == 0) {
				return;
			}
			int dx = 0, dy = 0;
			if (num_input == 1) {
				if (input & State::MOVE_UP) {
					dy = -1 * static_cast<int>(mSpeed);
				}
				else if (input & State::MOVE_DOWN) {
					dy = static_cast<int>(mSpeed);
				}
				else if (input & State::MOVE_LEFT) {
					dx = -1 * static_cast<int>(mSpeed);
				}
				else if (input & State::MOVE_RIGHT) {
					dx = static_cast<int>(mSpeed);
				}
			}
			if (num_input == 2) {
				if (input & State::MOVE_UP) {
					dy = -1 * static_cast<int>(mSpeed * M_SQRT1_2);
				}
				if (input & State::MOVE_DOWN) {
					dy = static_cast<int>(mSpeed * M_SQRT1_2);
				}
				if (input & State::MOVE_LEFT) {
					dx = -1 * static_cast<int>(mSpeed * M_SQRT1_2);
				}
				if (input & State::MOVE_RIGHT) {
					dx = static_cast<int>(mSpeed * M_SQRT1_2);
				}

			}
			int nx, ny;
			nx = mX + dx;
			ny = mY + dy;
			if (nx < 0 || nx > WINDOW.width || ny < 0 || ny > WINDOW.height) {
				return;
			}
			mX = nx;
			mY = ny;
			return;
		}

		void Player::draw() const {
			DxLib::DrawGraph(mX - 30, mY - 30, mGraphicHandle, TRUE);
		}

		void Player::reset() {
			mX = WINDOW.width / 2;
			mY = WINDOW.height / 2;
		}
	}
}

