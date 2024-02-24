//
//  Info_Stage.cpp
//  CasinoSlotMachine
//
//  Created by Nicolas U on 18.02.24.
//

#include "InfoStage.hpp"
#include "../Stages/MainStage.hpp"


InfoStage::InfoStage()
{
    Stage = nullptr;
    
    SwitchBtn = make_unique<Button>("Resources/Textures/Back.png", "Resources/Textures/BackPressed.png", "Resources/Audio/Button.wav");
    
    SwitchBtn->SetPosition(Vector2{GetScreenWidth()-40.0f,20});
    
    try {
        BackgroundTexture = LoadTexture("Resources/Textures/BackgroundInfo.png");
    } catch (const runtime_error& exc) {
        TraceLog(LOG_ERROR, "Texture failed to load");
    }
}

InfoStage::~InfoStage()
{
    UnloadTexture(BackgroundTexture);
}

void InfoStage::Update()
{
    SwitchBtn->Update();
    if (SwitchBtn->IsPressed())
    {
        // Change scene to settings
       Stage = make_shared<MainStage>();
    }
}

void InfoStage::Draw()
{
    DrawTexture(BackgroundTexture, 0, 0, WHITE);
    
    SwitchBtn->Draw();
}

shared_ptr<Stage> InfoStage::GetStage()
{ 
    return Stage;
}




