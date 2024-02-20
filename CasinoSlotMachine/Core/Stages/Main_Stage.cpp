//
//  Main_Stage.cpp
//  CasinoSlotMachine
//
//  Created by Nicolas U on 14.02.24.
//

#include "Main_Stage.hpp"
#include "../Stages/Info_Stage.hpp"

cMain_Stage::cMain_Stage() :
    ReelsManager(cReelsManager::GetInstance())
{
    Stage = nullptr;
    
    SwitchBtn = make_unique<cButton>("Resources/Textures/Back.png", "Resources/Textures/BackPressed.png", "Resources/Audio/ButtonSound.wav");
    PlayBtn = make_unique<cButton>("Resources/Textures/Play.png", "Resources/Textures/PlayPressed.png", "Resources/Audio/ButtonSound.wav");
    SoundBtn = make_unique<cButton>("Resources/Textures/Sound.png","Resources/Textures/SoundPressed.png", "Resources/Audio/ButtonSound.wav");
    IncBetBtn = make_unique<cButton>("Resources/Textures/Inc.png","Resources/Textures/IncPressed.png","Resources/Audio/ButtonSound.wav");
    DecBetBtn = make_unique<cButton>("Resources/Textures/Dec.png","Resources/Textures/DecPressed.png","Resources/Audio/ButtonSound.wav");
    
    Reels = make_unique<cReels>("Resources/Textures/Reel.png");
    
    SwitchBtn->SetPosition(Vector2{GetScreenWidth()-40.0f,20});
    PlayBtn->SetPosition(Vector2{598.0f,GetScreenHeight()-51.5f});
    SoundBtn->SetPosition(Vector2{520.0f, GetScreenHeight()-51.5f});
    IncBetBtn->SetPosition(Vector2{40.0f,GetScreenHeight()-51.5f});
    DecBetBtn->SetPosition(Vector2{90.0f,GetScreenHeight()-51.5f});
    
    // Try to load the textures

    try {
        BackgroundTexture = LoadTexture("Resources/Textures/Background.png");
    } catch (const runtime_error& exc) {
        TraceLog(LOG_ERROR, "Texture failed to load");
    }
    
    try {
        MessageTexture = LoadTexture("Resources/Textures/Message.png");
    } catch (const runtime_error& exc) {
        TraceLog(LOG_ERROR, "Texture failed to load");
    }
    
    try {
        MessageTexture1 = LoadTexture("Resources/Textures/Message.png");
    } catch (const runtime_error& exc) {
        TraceLog(LOG_ERROR, "Texture failed to load");
    }
    
    try {
        BottomBarTexture = LoadTexture("Resources/Textures/BottomBar.png");
    } catch (const runtime_error& exc) {
        TraceLog(LOG_ERROR, "Texture failed to load");
    }

}

cMain_Stage::~cMain_Stage()
{
    // Unload textures
    TraceLog(LOG_INFO, "Main Stage: Destroyed");
    
    UnloadTexture(BackgroundTexture);
    UnloadTexture(MessageTexture);
    UnloadTexture(BottomBarTexture);
}

void cMain_Stage::Update()
{
    SwitchBtn->Update();
    PlayBtn->Update();
    SoundBtn->Update();
    IncBetBtn->Update();
    DecBetBtn->Update();
    Reels->Update();
    
    if (SwitchBtn->IsPressed())
    {
        // Change scene to settings
        Stage = make_shared<cInfo_Stage>();
    }
    
    if (PlayBtn->IsPressed())
    {
        ReelsManager.SetRunning(true);
    }
    
    if (ReelsManager.IsRunning())
    {
        framesCounter++;
        if (framesCounter >= (60/framesSpeed))
        {
            framesCounter = 0;
            currentFrame++;
            ReelsManager.GenerateReels();
            
            if (currentFrame > 10)
            {
                currentFrame = 0;
                ReelsManager.Play();
                ReelsManager.SetRunning(false);
            }
        }
    }
    
    if (SoundBtn->IsPressed())
    {
        if (SoundMuted)
        {
            SetMasterVolume(1);
            SoundMuted = false;
        } else
        {
            SetMasterVolume(0);
            SoundMuted = true;
        }
    }
    
    if (IncBetBtn->IsPressed())
    {
        if (ReelsManager.GetBet() > 1)
        {
            ReelsManager.SetBet(0.50);
        } else {
            ReelsManager.SetBet(0.10);
        }
    }
    
    if (DecBetBtn->IsPressed())
    {
        if (ReelsManager.GetBet() >= 1.50) {
            ReelsManager.SetBet(-0.50);
        } else {
            ReelsManager.SetBet(-0.10);
        }
    }
}

void cMain_Stage::Draw()
{
    // Draw background texture
    DrawTexture(BackgroundTexture, 0, 0, WHITE);
    
    // Draw bottom bar
    DrawTexture(BottomBarTexture, 30, GetScreenHeight()-55, Color{255,255,255,120});
    
    // Draw message frames
    DrawTexture(MessageTexture, 340, GetScreenHeight()-51.5f, WHITE);
    DrawTexture(MessageTexture1, 160, GetScreenHeight()-51.5f, WHITE);
    
    // Draw buttons
    SwitchBtn->Draw();
    PlayBtn->Draw();
    SoundBtn->Draw();
    IncBetBtn->Draw();
    DecBetBtn->Draw();
    Reels->Draw();
    
    // Draw payout
    const float Payout = ReelsManager.GetPayoutPrize();
    if (Payout > 0.0) {
        Vector2 Measure = MeasureTextEx(GetFontDefault(), TextFormat("Win: %02.02f",Payout), 20.0f, 1);
        DrawText(TextFormat("Win: %02.02f",Payout), (340+MessageTexture.width/2)-Measure.x/2, (GetScreenHeight()-51)+Measure.y/2, 20.0f, WHITE);
    }
    
    // Draw Money and Bet
    DrawText(TextFormat("Money: %02.02f",ReelsManager.GetMoney()), 0, 0, 20.0f, WHITE);
    DrawText(TextFormat("Bet: %02.02f",ReelsManager.GetBet()), (160+MessageTexture1.width/2)-40, (GetScreenHeight()-41), 20.0f, WHITE);
}

shared_ptr<cStage> cMain_Stage::GetStage() 
{ 
    return Stage;
}
