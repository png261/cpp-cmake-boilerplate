#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <iostream>

using namespace std;
int main(int argc, char* argv[])
{
    const int SCREEN_WIDTH = 800;
    const int SCREEN_HEIGHT = 800;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        cout << "Couldn't initialize SDL. SDL_Error: " << SDL_GetError();
        return -1;
    }

    if (!(SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))) {
        cout << "Warning: Linear Texture Filtering not enabled.\n";
    }

    SDL_Window* const window = SDL_CreateWindow(
        "Sorting Visualizer",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        SDL_WINDOW_SHOWN);

    if (window == nullptr) {
        cout << "Couldn't create window. SDL_Error: " << SDL_GetError();
        return -1;
    }

    SDL_Renderer* const renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        cout << "Couldn't create renderer. SDL_Error: " << SDL_GetError();
        return -1;
    }

    SDL_RenderPresent(renderer);
    SDL_Delay(2000);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
