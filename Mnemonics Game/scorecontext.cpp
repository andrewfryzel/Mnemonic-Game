/* Author: Brian Schnepp */

#include <stdint.h>

#include "scorecontext.h"

#define NUM_LEVELS (6)

/* Prevent name resolution outside this at link time. */
static uint64_t Scores[NUM_LEVELS]; /* 5 total levels */

void ScoreContext::SetScore(uint8_t LevelID, uint64_t Score)
{
	/* validate */
	if (LevelID > NUM_LEVELS)
	{
		return;
	}
	Scores[LevelID] = Score;
}

uint64_t ScoreContext::GetScore(uint8_t LevelID)
{
	/* validate */
	if (LevelID > NUM_LEVELS)
	{
		return 0;
	}
	return Scores[LevelID];
}

uint64_t ScoreContext::GetTotalScore()
{
	uint8_t Index = 0;
	uint64_t RetVal = 0;
	for (Index = 0; Index < NUM_LEVELS; ++Index)
	{
		RetVal += Scores[Index];
	}
	return RetVal;
}