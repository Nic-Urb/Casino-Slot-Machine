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
    // make_shared creates a pointer for shared_ptr<Stage>
    CurrentStage = make_shared<MainStage>();
}

void StageManager::UpdateTransition()
{
    // Update transition alpha
    TransitionAlpha += 0.05;
    if (TransitionAlpha >= 1.0f)
    {
        TransitionAlpha = 0.0f;
        
        Transition = false;
    }
}

void StageManager::Update()
{
    if (CurrentStage == nullptr)
    {
        Init();
        return;
    }
    
    if (Transition)
    {
        UpdateTransition();
    }
    
    GetStage();
    CurrentStage->Update();
}

void StageManager::Draw()
{
    BeginDrawing();
        if (Transition)
        {
            DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(BLACK, TransitionAlpha));
            
        }
        else
        {
            CurrentStage->Draw();
        }
        DrawFPS(10, GetScreenHeight()-20);
    EndDrawing();
}

bool StageManager::Close()
{
    // De-Initialization
    return false;
}

void StageManager::GetStage()
{
    // Updates the stage to the one currently stored in CurrentStage
    shared_ptr<Stage> NewStage = CurrentStage->GetStage();
    if (NewStage != nullptr)
    {
        if (CurrentStage != NewStage) // If new stage is different from current - do transition
        {
            Transition = true;
            CurrentStage = NewStage;
        }
    }
}








