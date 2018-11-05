#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <windows.h>
#include <conio.h>
#include <math.h>

#include "renderSystem.h"
#include "input.h"

// Logic variables
bool isGameActive = true;
clock_t clockLastFrame = 0;

int framesCounter = 0;
float framesTimeCounter = 0;
int fps = 0;
float offset = 0;
int selecter = 0;

// Functions

void SetupSystem()
{
    srand(time(0));

    RenderSystemInitialize();
}

void Initialize()
{
    clockLastFrame = clock();
}

void Render()
{
    // Start frame
    RenderSystemClear();

    // Draw frame

    if (IsKeyDown(VK_UP))
        RenderSystemDrawChar(10, 35, 24, ConsoleColor_Red, ConsoleColor_Gray);

    if (IsKeyDown(VK_DOWN))
        RenderSystemDrawChar(12, 35, 25, ConsoleColor_Blue, ConsoleColor_White);

    if (IsKeyDown(VK_RIGHT))
        RenderSystemDrawChar(12, 37, 26, ConsoleColor_Yellow, ConsoleColor_DarkGray);

    if (IsKeyDown(VK_LEFT))
        RenderSystemDrawChar(12, 33, 27, ConsoleColor_Green, ConsoleColor_DarkCyan);

    if (IsKeyDown(0x54)) // virtual code T
        RenderSystemDrawText(8, 30, "Some test drawing text",ConsoleColor_Green, ConsoleColor_Black);

    if (IsKeyDown(0x44)) // virtual code D
        offset += 0.01;

    if (IsKeyDown(0x41)) // virtual code A
        offset -= 0.01;

    if (IsKeyDown(0x31)) // virtual code 1
        selecter = 0;

    if (IsKeyDown(0x32)) // virtual code 2
        selecter = 1;

    if (IsKeyDown(0x33)) // virtual code 3
        selecter = 2;

    if (IsKeyDown(0x34)) // virtual code 4
        selecter = 3;

    if (IsKeyDown(0x35)) // virtual code 5
        selecter = 4;

    // Draw func
    int y = 0;
    for (float i = 0; i < screenColumns; i += 0.5)
    {
        switch(selecter)
        {
            case 0: y = int(round(sin(offset+i/4)*5)); break;
            case 1: y = int(round(cos(offset+i/4)*5)); break;
            case 2: y = int(round(1/tan(offset+i/5)*3)); break;
            case 3: y = int(round(tan(offset+i/5)*3)); break;
            default: y = int(round(sin(offset+i/4)*5));
        }

        if (y >= screenRows-11)
        {
            y = screenRows-12;
        }
        else if (y < -10)
        {
            y = 0;
        }

        RenderSystemDrawChar(10+y, i, 160, ConsoleColor_Cyan, ConsoleColor_Cyan);
    }

    // Draw FPS
    char textBuffer[32];
    sprintf(textBuffer, "FPS: %d", fps);
    RenderSystemDrawText(0, 0, textBuffer, ConsoleColor_Red, ConsoleColor_Black);

    // End frame
    RenderSystemFlush();
}

void Update()
{
    clock_t clockNow = clock();
    clock_t deltaClock = clockNow - clockLastFrame;
    float deltaTime = float(deltaClock) / CLOCKS_PER_SEC;
    clockLastFrame = clockNow;

    framesCounter++;
    framesTimeCounter += deltaTime;
    if(framesTimeCounter >= 1.0)
    {
        framesTimeCounter -= 1.0;
        fps = framesCounter;
        framesCounter = 0;
    }
}

void Shutdown()
{

}

int main()
{
    SetupSystem();
    Initialize();

    do
    {
        Render();
        Update();
    }
    while(isGameActive);

    Shutdown();

    return 0;
}
