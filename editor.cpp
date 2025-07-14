#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#define SDL_OPENGL_1_FUNCTION_TYPEDEFS
#include <SDL3/SDL_opengl.h>
#include <SDL3/SDL_video.h>

#include <iostream>

int main(int argc, char** argv)
{
    if (!SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO))
    {
        std::cerr << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
        return -1; 
    }

    SDL_Window* window = SDL_CreateWindow("BubbleGUM Editor", 1920, 1080, SDL_WINDOW_OPENGL);

    if (!window)
    {
        std::cerr << "Failed to create a window: " << SDL_GetError() << std::endl;
        return -1;
    }

    SDL_GLContext glcontext = SDL_GL_CreateContext(window);

    if (!glcontext)
    {
        std::cerr << "Failed to create GL context: " << SDL_GetError() << std::endl;
        return -1;
    }

    if (!SDL_GL_LoadLibrary(nullptr))
    {
        std::cerr << "Failed to load OpenGL: " << SDL_GetError() << std::endl;
        return -1;
    }

    bool done = false;
    while (!done)
    {
        SDL_Event event;

        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_EVENT_QUIT)
                done = true;
        }

        PFNGLCLEARCOLORPROC glClearColor = (PFNGLCLEARCOLORPROC)SDL_GL_GetProcAddress("glClearColor");
        PFNGLCLEARPROC glClear = (PFNGLCLEARPROC)SDL_GL_GetProcAddress("glClear");

        glClearColor(0.2, 0.1, 1, 1);
        glClear(GL_COLOR_BUFFER_BIT);

        SDL_GL_SwapWindow(window);
    }

    SDL_GL_DestroyContext(glcontext);
    SDL_DestroyWindow(window);
    SDL_Quit();

    std::cout << "Program success" << std::endl;

    return 0;
}
