#ifndef GAME_H
#define GAME_H

#include <stdbool.h>
#include <stdlib.h>

#include <stdint.h>

#include "history.h"

#include "tap_state.h"

#define LEVEL_MAX      999

#define SECTION_LENGTH 100
#define SECTION_MAX    100
#define SECTION_COUNT  10

#define TIMER_FPS      60.0f
#define TAP_FPS        61.618f

#define MASTER_S9_INTERNAL_GRADE 31
#define GRADE_COUNT 32

struct section_table_t;

extern const char* DISPLAYED_GRADE[GRADE_COUNT];

float frameTimeToSeconds(int frames);
int frameTime(float seconds);

enum tap_internal_state
{
    TAP_NONE         = 0,
    TAP_START        = 1,
    TAP_ACTIVE       = 2,
    TAP_LOCKING      = 3,  // Cannot be influenced anymore
    TAP_LINECLEAR    = 4,  // Tetromino is being locked to the playfield.
    TAP_ENTRY        = 5,
    TAP_GAMEOVER     = 7,  // "Game Over" is being shown on screen.
    TAP_IDLE         = 10, // No game has started, just waiting...
    TAP_FADING       = 11, // Blocks fading away when topping out (losing).
    TAP_COMPLETION   = 13, // Blocks fading when completing the game
    TAP_STARTUP      = 71
};

enum tap_mroll_flags
{
    M_FAIL_1   = 17,
    M_FAIL_2   = 19,
    M_FAIL_END = 31,

    M_NEUTRAL  = 48,
    M_PASS_1   = 49,
    M_PASS_2   = 51,
    M_SUCCESS  = 127,
};

enum tap_game_mode
{
    TAP_MODE_NULL           = 0,
    TAP_MODE_NORMAL         = 1,
    TAP_MODE_MASTER         = 2,
    TAP_MODE_DOUBLES        = 4,
    TAP_MODE_NORMAL_VERSUS  = 9,
    TAP_MODE_MASTER_VERSUS  = 10,
    TAP_MODE_MASTER_CREDITS = 18,
    TAP_MODE_TGMPLUS_VERSUS = 136,
    TAP_MODE_TGMPLUS        = 128,
    TAP_MODE_MASTER_ITEM    = 514,
    TAP_MODE_TGMPLUS_ITEM   = 640,
    TAP_MODE_DEATH          = 4096,
    TAP_MODE_DEATH_VERSUS   = 4104
};

struct datapoint_t
{
        int level;
        int time;
};

struct section_t
{
        struct datapoint_t data[SECTION_MAX];
        size_t size;

        int startTime; // Frame count for when this section began.
        int endTime;
        int lines[4];
};

int getSectionTime(struct section_t* section);

struct game_t
{
        struct section_t sections[SECTION_COUNT];
        int currentSection;

        // We want to detect change on each frame, so we'll keep track of how
        // things looked on the previous frame for comparison.
        struct tap_state curState;
        struct tap_state prevState;
};

// (Re)sets all game data. If passed NULL, allocate new game data.
struct game_t* createNewGame(struct game_t* game);
void destroyGame(struct game_t* game, bool freeMem);
void resetGame(struct game_t* game);

bool isGameComplete(struct game_t* game);
bool isInPlayingState(char game);

// Load game state from MAME into our game structure. This also handles adding
// data points to our section data.
void updateGameState(struct game_t* game, struct history_t* inputHistory, struct section_table_t* table,
                     struct tap_state* dataPtr);

// Adds datapoint to section data if level has incremented.
void pushCurrentState(struct game_t* game, struct section_table_t* table);
void addDataPointToSection(struct game_t* game, struct section_t* section);

// Returns section data for a single section.
struct section_t* getSection(struct game_t* game, int sectionIndex);

// Will return true if _currently_ not invalidated from getting M-rank.
bool testMasterConditions(struct game_t* game);

// Deprecated since we now pull the flag directly from MAME.
bool calculateMasterConditions_(struct game_t* game);

void printGameState(struct game_t* game);

#endif /* GAME_H */
