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
    
    SwitchBtn = std::make_unique<Button>("Resources/Textures/Back.png", "Resources/Textures/BackPressed.png", "Resources/Audio/Button.wav");
    
    SwitchBtn->SetPosition(Vector2{GetScreenWidth()-40.0f,20});
    
    BackgroundTexture = LoadTexture("Resources/Textures/BackgroundInfo.png");
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
       Stage = std::make_shared<MainStage>();
    }
}

void InfoStage::Draw()
{
    DrawTexture(BackgroundTexture, 0, 0, WHITE);
    
    SwitchBtn->Draw();
}

std::shared_ptr<Stage> InfoStage::GetStage()
{ 
    return Stage;
}




