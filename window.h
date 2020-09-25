#pragma once

#include <SDL2/SDL.h>
#include <glm/vec3.hpp>
#include "texture.h"

class Window {
public:
    Window(int width, int height);
    ~Window();

    SDL_Renderer* get_renderer() {
        return _renderer;
    };

    int main_loop();

    void draw_texture(Texture<glm::vec3>* texture);
private:
    int _width;
    int _height;
    SDL_Window* _window;
    SDL_Renderer* _renderer;
};
