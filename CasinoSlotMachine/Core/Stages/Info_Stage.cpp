//
//  Info_Stage.cpp
//  CasinoSlotMachine
//
//  Created by Nicolas U on 18.02.24.
//

#include "Info_Stage.hpp"
#include "../Stages/Main_Stage.hpp"


cInfo_Stage::cInfo_Stage()
{
    Stage = nullptr;
    
    SwitchBtn = make_unique<cButton>("Resources/Textures/Back.png", "Resources/Textures/BackPressed.png", "Resources/Audio/Button.wav");
    
    SwitchBtn->SetPosition(Vector2{GetScreenWidth()-40.0f,20});
    
    try {
        BackgroundTexture = LoadTexture("Resources/Textures/BackgroundInfo.png");
    } catch (const runtime_error& exc) {
        TraceLog(LOG_ERROR, "Texture failed to load");
    }
}

cInfo_Stage::~cInfo_Stage()
{
    UnloadTexture(BackgroundTexture);
}

void cInfo_Stage::Update()
{
    SwitchBtn->Update();
    if (SwitchBtn->IsPressed())
    {
        // Change scene to settings
       Stage = make_shared<cMain_Stage>();
    }
}

void cInfo_Stage::Draw() 
{
    DrawTexture(BackgroundTexture, 0, 0, WHITE);
    
    SwitchBtn->Draw();
}

shared_ptr<cStage> cInfo_Stage::GetStage() 
{ 
    return Stage;
}




