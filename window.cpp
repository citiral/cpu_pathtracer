#include "window.h"
#include <glm/glm.hpp>

Window::Window(int width, int height): _width(width), _height(height)
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(width, height, 0, &_window, &_renderer);
    SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 0);
    SDL_RenderClear(_renderer);
}

Window::~Window()
{
    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);
    SDL_Quit();
}

int Window::main_loop()
{
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
                SDL_DestroyRenderer(_renderer);
                SDL_DestroyWindow(_window);
                SDL_Quit();
                return 1;
        }
    }

    SDL_RenderPresent(_renderer);
    return 0;
}

void Window::draw_texture(Texture<glm::vec3>* texture)
{
    if (texture->width != _width || texture->height != _height) {
        return;
    }

    glm::vec3* buffer = texture->buffer;
    size_t offset = 0;


    float max = 1.0f;

    for (int y = 0; y < _height; y++) {
        for (int x = 0; x < _width; x++) {
            max = glm::max(max, (buffer[offset].x + buffer[offset].y + buffer[offset].z) / 3.0f);
            offset++;
        }
    }

    offset = 0;

    for (int y = 0; y < _height; y++) {
        for (int x = 0; x < _width; x++) {

            // tone mapping
            glm::vec3 mapped = buffer[offset] * (glm::vec3(1.0, 1.0, 1.0) + buffer[offset] / (max * max)) / (1.0f + max);

            // and gamma correction
            SDL_SetRenderDrawColor(_renderer, glm::min(255.0f, glm::pow(mapped.x, 1.0f/2.2f) * 255.0f),
                                              glm::min(255.0f, glm::pow(mapped.y, 1.0f/2.2f) * 255.0f),
                                              glm::min(255.0f, glm::pow(mapped.z, 1.0f/2.2f) * 255.0f),
                                              255);

            /*SDL_SetRenderDrawColor(_renderer, glm::min(255.0f, glm::pow((buffer[offset].x / (buffer[offset].x +1.0f)), 2.2f) * 255.0f),
                                              glm::min(255.0f, glm::pow((buffer[offset].y / (buffer[offset].y +1.0f)), 2.2f) * 255.0f),
                                              glm::min(255.0f, glm::pow((buffer[offset].z / (buffer[offset].z +1.0f)), 2.2f) * 255.0f),
                                              255);*/
            SDL_RenderDrawPoint(_renderer, x, y);
            offset++;
        }
    }
}