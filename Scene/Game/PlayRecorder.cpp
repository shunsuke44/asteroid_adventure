#include "Scene/Game/PlayRecorder.h"

namespace Scene {
	namespace Game {
		void PlayRecorder::record(int clock, unsigned int input) {
			mRecord.emplace_back(clock, input);
		}
	}
}
