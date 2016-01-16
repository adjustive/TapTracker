#ifndef SECTIONTIME_H
#define SECTIONTIME_H

#include "game.h"

#define LEVEL_MAX      999

#define SECTION_LENGTH 100
#define SECTION_MAX    128
#define SECTION_COUNT  10

struct datapoint_t
{
        int level;
        int time;
};

struct section_t
{
        char label[8];

        struct datapoint_t data[SECTION_MAX];
        size_t size;

        int startTime; // Frame count for when this section began.
        int endTime;

        int lines[4];

        // Section PBs
        int masterST;
        int deathST;

        // Game time PBs
        int masterTime;
        int deathTime;
};

struct section_table_t
{
        struct section_t sections[SECTION_COUNT];
};

void section_table_init(struct section_table_t* table);
void section_table_terminate(struct section_table_t* table);

struct section_table_t* section_table_create();
void section_table_destroy(struct section_table_t* table);

void resetSectionTable(struct section_table_t* table);

void updateSectionTable(struct section_table_t* table, struct game_t* game);
void addDataPointToSection(struct section_t* section, struct game_t* game);

// Once the game is over, call this to update the PB table.
void updateRecords(struct section_table_t* table, unsigned int currentLevel, unsigned int gameMode);

void readSectionRecords(struct section_table_t* table, const char* filename);
void writeSectionRecords(struct section_table_t* table);

#endif /* SECTIONTIME_H */