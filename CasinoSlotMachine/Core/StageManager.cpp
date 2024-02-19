//
//  StageManager.cpp
//  CasinoSlotMachine
//
//  Created by Nicolas U on 14.02.24.
//

#include "StageManager.hpp"


cStageManager::cStageManager()
{ 
}

cStageManager &cStageManager::GetInstance()
{
    static cStageManager Instance;
    return Instance;
}

void cStageManager::Init()
{ 
    // make_shared creates a pointer for shared_ptr<cStage>
    CurrentStage = make_shared<cMain_Stage>();
}

void cStageManager::Update() 
{
    if (CurrentStage == nullptr)
    {
        Init();
        return;
    }
    
    GetStage();
    CurrentStage->Update();
}

void cStageManager::Draw()
{
    BeginDrawing();
        CurrentStage->Draw();
        DrawFPS(10, GetScreenHeight()-20);
    EndDrawing();
}

bool cStageManager::Close()
{
    // De-Initialization
        
    // Unload button texture
    // Unload sound
    return false;
}

void cStageManager::GetStage()
{
    // Updates the stage to the one currently stored in CurrentStage
    shared_ptr<cStage> Stage = CurrentStage->GetStage();
    if (Stage!=nullptr)
    {
        CurrentStage = Stage;
    }
}






