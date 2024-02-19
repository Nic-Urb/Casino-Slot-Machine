//
//  Engine.cpp
//  CasinoSlotMachine
//
//  Created by Nicolas U on 14.02.24.
//

#include "Engine.hpp"


cEngine::cEngine() :
    StageManager(cStageManager::GetInstance())
{
}

cEngine &cEngine::GetInstance() 
{
    static cEngine Instance;
    return Instance;
}

void cEngine::Run()
{
    InitWindow(WindowWidth, WindowHeight, "raylib [core] example - basic window");
    InitAudioDevice();
    SetTargetFPS(60);
    
    while (!WindowShouldClose())
    {
        if (StageManager.Close())
        {
            CloseWindow();
        }
        
        StageManager.Update();
        StageManager.Draw();
    }
}



