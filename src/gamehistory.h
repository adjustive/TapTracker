#ifndef GAMEHISTORY_H
#define GAMEHISTORY_H

#include "tap_state.h"

#define MAX_GAME_HISTORY_COUNT 32

struct game_history_t
{
        struct tap_state data[MAX_GAME_HISTORY_COUNT];
        int start;
        int end;
};

void game_history_init(struct game_history_t* gh);
void game_history_terminate(struct game_history_t* gh);

struct game_history_t* game_history_create();
void game_history_destroy(struct game_history_t* gh);

void pushStateToGameHistory(struct game_history_t* gh, struct tap_state state);
void popGameHistoryElement(struct game_history_t* gh);

float averageHistoryStats(struct game_history_t* gh,
                          int (*getVar)(struct tap_state* state));

float averageDeathLevel(struct game_history_t* gh);
float averageMasterGrade(struct game_history_t* gh);

#endif /* GAMEHISTORY_H */