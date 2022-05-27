#include "SDL.h"
#include <stdio.h>

int SDL_RenderDrawCircle(SDL_Renderer* renderer, int x, int y, int radius);
int SDL_RenderFillCircle(SDL_Renderer* renderer, int x, int y, int radius);
//void SLD_RenderCreateRect(SDL_Renderer* renderer,int x, int y, int w, int h, SDL_Rect rect);

int main(int argc, char* argv[]) {

    SDL_Window* window;                    // Declare a pointer

    SDL_Init(SDL_INIT_VIDEO);              // Initialize SDL2

    // Create an application window with the following settings:
    window = SDL_CreateWindow(
        "An SDL2 window",                  // window title
        SDL_WINDOWPOS_UNDEFINED,           // initial x position
        SDL_WINDOWPOS_UNDEFINED,           // initial y position
        640,                               // width, in pixels 
        480,                               // height, in pixels
        SDL_WINDOW_OPENGL                  // flags - see below
    );

    SDL_Renderer* renderer;
    renderer = SDL_CreateRenderer(window, -1, 0);

    // Select the color for drawing.
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);            // test

    // Clear the entire screen to our selected color.
    SDL_RenderClear(renderer);

    SDL_Rect rect;
    // select the position and the dimension of the rect
    rect.x = 250;
    rect.y = 150;
    rect.w = 100;
    rect.h = 100;

    // Select the color for drawing.
    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);                // test

    //Fill the rect on the renderer
    //SDL_RenderFillRect(renderer, &rect);                          //commenter

    //Draw the rect on the renderer
    SDL_RenderDrawRect(renderer, &rect);

    //It is set to red here.
    //SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);             //commenter

    int x = 100;
    int y = 200;
    int radius = 50;
    SDL_RenderDrawCircle(renderer, x, y, radius);
    //SDL_RenderFillCircle(renderer, x, y, radius);                     //commenter


    // Up until now everything was drawn behind the scenes.
    // This will show the new, red contents of the window.
    SDL_RenderPresent(renderer);

    // The window is open: could enter program loop here (see SDL_PollEvent())

    SDL_Delay(3000);  // Pause execution for 3000 milliseconds, for example

    // Close and destroy the window
    SDL_DestroyWindow(window);

    // Clean up
    SDL_Quit();
    return 0;
}

int SDL_RenderDrawCircle(SDL_Renderer* renderer, int x, int y, int radius)
{
    int offsetx, offsety, d;
    int status;

    //CHECK_RENDERER_MAGIC(renderer, -1);

    offsetx = 0;
    offsety = radius;
    d = radius - 1;
    status = 0;

    while (offsety >= offsetx) {
        status += SDL_RenderDrawPoint(renderer, x + offsetx, y + offsety);
        status += SDL_RenderDrawPoint(renderer, x + offsety, y + offsetx);
        status += SDL_RenderDrawPoint(renderer, x - offsetx, y + offsety);
        status += SDL_RenderDrawPoint(renderer, x - offsety, y + offsetx);
        status += SDL_RenderDrawPoint(renderer, x + offsetx, y - offsety);
        status += SDL_RenderDrawPoint(renderer, x + offsety, y - offsetx);
        status += SDL_RenderDrawPoint(renderer, x - offsetx, y - offsety);
        status += SDL_RenderDrawPoint(renderer, x - offsety, y - offsetx);

        if (status < 0) {
            status = -1;
            break;
        }

        if (d >= 2 * offsetx) {
            d -= 2 * offsetx + 1;
            offsetx += 1;
        }
        else if (d < 2 * (radius - offsety)) {
            d += 2 * offsety - 1;
            offsety -= 1;
        }
        else {
            d += 2 * (offsety - offsetx - 1);
            offsety -= 1;
            offsetx += 1;
        }
    }

    return status;
}

int SDL_RenderFillCircle(SDL_Renderer* renderer, int x, int y, int radius)
{
    int offsetx, offsety, d;
    int status;

    //CHECK_RENDERER_MAGIC(renderer, -1);

    offsetx = 0;
    offsety = radius;
    d = radius - 1;
    status = 0;

    while (offsety >= offsetx) {

        status += SDL_RenderDrawLine(renderer, x - offsety, y + offsetx,
            x + offsety, y + offsetx);
        status += SDL_RenderDrawLine(renderer, x - offsetx, y + offsety,
            x + offsetx, y + offsety);
        status += SDL_RenderDrawLine(renderer, x - offsetx, y - offsety,
            x + offsetx, y - offsety);
        status += SDL_RenderDrawLine(renderer, x - offsety, y - offsetx,
            x + offsety, y - offsetx);

        if (status < 0) {
            status = -1;
            break;
        }

        if (d >= 2 * offsetx) {
            d -= 2 * offsetx + 1;
            offsetx += 1;
        }
        else if (d < 2 * (radius - offsety)) {
            d += 2 * offsety - 1;
            offsety -= 1;
        }
        else {
            d += 2 * (offsety - offsetx - 1);
            offsety -= 1;
            offsetx += 1;
        }
    }

    return status;
}

/*void SLD_RenderCreateRect(SDL_Renderer* renderer, int x, int y, int w, int h, SDL_Rect rect)
{
    SDL_Rect rect;
    // select the position and the dimension of the rect
    rect.x = 250;
    rect.y = 150;
    rect.w = 100;
    rect.h = 100;

    // Select the color for drawing.
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);


    //SDL_RenderFillRect(renderer, &rect);

    //Draw the rect on the renderer
    SDL_RenderDrawRect(renderer, &rect);
}*/
