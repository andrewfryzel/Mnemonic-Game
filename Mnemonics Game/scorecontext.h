#include <stdint.h>

#ifndef SCORECONTEXT_H
#define SCORECONTEXT_H

namespace ScoreContext
{
	void SetScore(uint8_t LevelID, uint64_t Score);
	uint64_t GetScore(uint8_t LevelID);
	uint64_t GetTotalScore();
}; // namespace ScoreContext

#endif // SCORECONTEXT_H