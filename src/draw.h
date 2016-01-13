#ifndef DRAW_H
#define DRAW_H

struct game_t;
struct font_t;
struct history_t;
struct button_spectrum_t;

struct draw_data_t
{
        struct game_t* game;
        struct font_t* font;

        struct history_t* history;
        struct button_spectrum_t* bspec;

        struct section_table_t* table;

        float scale;
};

void drawSectionGraph(struct draw_data_t* data, float width, float height);
void drawInputHistory(struct draw_data_t* data, float width, float height);
void drawSectionTable(struct draw_data_t* data, float width, float height);

#endif /* DRAW_H */
