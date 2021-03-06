#include "buttonquads.h"

#include <stdint.h>
#include <stdlib.h>

#include <stb_image.h>
#include <GLFW/glfw3.h>

#include <incbin.h>

void button_spectrum_init(struct button_spectrum_t* bspec, const uint8_t* data, size_t size)
{
    const int tileSize = 8;

    int width, height, n;
    uint8_t* bitmap = stbi_load_from_memory(data, size, &width, &height, &n, 4);

    glGenTextures(1, &bspec->textureID);
    glBindTexture(GL_TEXTURE_2D, bspec->textureID);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
                 width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, bitmap);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_image_free(bitmap);

    // Setup coordinates
    for (size_t i = 0; i < BUTTON_QUAD_COUNT; ++i)
    {
        struct button_spectrum_quad_t* currentQuad = &bspec->quads[i];

        // This also accounts for padding in our texture atlas (since we're
        // using GL_LINEAR). Without the padding pixels, when we get some
        // texture bleeding.
        currentQuad->texCoords[0] = (float)(i * tileSize + i) / width;
        currentQuad->texCoords[1] = (float)0.0f;
        currentQuad->texCoords[2] = (float)(i * tileSize + i + tileSize) / width;
        currentQuad->texCoords[3] = (float)0.0f;
        currentQuad->texCoords[4] = (float)(i * tileSize + i + tileSize) / width;
        currentQuad->texCoords[5] = (float)1.0f;
        currentQuad->texCoords[6] = (float)(i * tileSize + i) / width;
        currentQuad->texCoords[7] = (float)1.0f;
    }
}

void button_spectrum_terminate(struct button_spectrum_t* bspec)
{
    glDeleteTextures(1, &bspec->textureID);
}

struct button_spectrum_t* button_spectrum_create(const uint8_t* data, size_t size)
{
    struct button_spectrum_t* bspec = malloc(sizeof(struct button_spectrum_t));
    if (bspec)
    {
        button_spectrum_init(bspec, data, size);
    }

    return bspec;
}

void button_spectrum_destroy(struct button_spectrum_t* bspec)
{
    button_spectrum_terminate(bspec);
    free(bspec);
}

uint8_t joystickButtonToQuadIndex(struct joystick_mapping_t jmap, uint8_t button)
{
    if (button == jmap.buttons[BUTTON_A])
        return BUTTON_QUAD_A;

    if (button == jmap.buttons[BUTTON_B])
        return BUTTON_QUAD_B;

    if (button == jmap.buttons[BUTTON_C])
        return BUTTON_QUAD_C;

    return BUTTON_QUAD_BLANK;
}
