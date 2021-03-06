#ifndef WINDOW_H
#define WINDOW_H

#include "layout.h"

struct GLFWwindow;

struct window_t
{
        struct GLFWwindow* handle;
        unsigned int width;
        unsigned int height;
        struct layout_container_t layout;
};

void window_init(struct window_t* w,
                 const char* title,
                 const unsigned int width, const unsigned int height,
                 struct window_t* parent);
void window_terminate(struct window_t* w);

struct window_t* window_create(const char* title,
                               const unsigned int width, const unsigned int height,
                               struct window_t* parent);
void window_destroy(struct window_t* w);

void setupOpenGL(struct window_t* window, const unsigned int width, const unsigned int height);
void drawWindowLayout(struct window_t* window);

bool windowSetShouldClose(struct window_t** windows, size_t windowCount);
void drawWindowSet(struct window_t** windows, size_t windowCount);

void windowSet_destroy(struct window_t** windowset, size_t windowCount);

#endif /* WINDOW_H */
