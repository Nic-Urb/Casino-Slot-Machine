//
//  StageManager.cpp
//  CasinoSlotMachine
//
//  Created by Nicolas U on 14.02.24.
//

#include "StageManager.hpp"


StageManager::StageManager()
{ 
}

StageManager &StageManager::GetInstance()
{
    static StageManager Instance;
    return Instance;
}

void StageManager::Init()
{ 
    // make_shared creates a pointer for shared_ptr<cStage>
    CurrentStage = make_shared<MainStage>();
}

void StageManager::Update()
{
    if (CurrentStage == nullptr)
    {
        Init();
        return;
    }
    
    GetStage();
    CurrentStage->Update();
}

void StageManager::Draw()
{
    BeginDrawing();
        CurrentStage->Draw();
        DrawFPS(10, GetScreenHeight()-20);
    EndDrawing();
}

bool StageManager::Close()
{
    // De-Initialization
        
    // Unload button texture
    // Unload sound
    return false;
}

void StageManager::GetStage()
{
    // Updates the stage to the one currently stored in CurrentStage
    shared_ptr<Stage> Stage = CurrentStage->GetStage();
    if (Stage!=nullptr)
    {
        CurrentStage = Stage;
    }
}






