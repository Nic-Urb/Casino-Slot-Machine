//
//  Engine.cpp
//  CasinoSlotMachine
//
//  Created by Nicolas U on 14.02.24.
//

#include "Engine.hpp"


Engine::Engine() :
    StageManager(StageManager::GetInstance())
{
}

Engine &Engine::GetInstance()
{
    static Engine Instance;
    return Instance;
}

void Engine::Run()
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



