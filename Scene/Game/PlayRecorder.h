#pragma once

#include <utility>
#include <vector>

namespace Scene {
	namespace Game {
		class PlayRecorder {
		public:
			PlayRecorder() {}
			~PlayRecorder() {}
			void record(int clock, unsigned int input);
			// const std::vector<unsigned int>& getRecord() const { return mRecord; }
			const std::vector<std::pair<int, unsigned int>>& getRecord() const { return mRecord; }
			void clear() { mRecord.clear(); }
		private:
			// std::vector<unsigned int> mRecord;
			std::vector<std::pair<int, unsigned int>> mRecord;
		};
	}
}
