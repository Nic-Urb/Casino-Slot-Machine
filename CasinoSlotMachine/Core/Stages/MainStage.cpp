//
//  Main_Stage.cpp
//  CasinoSlotMachine
//
//  Created by Nicolas U on 14.02.24.
//

#include "MainStage.hpp"
#include "../Stages/InfoStage.hpp"

MainStage::MainStage() :
    ReelsManager(ReelsManager::GetInstance())
{
    Stage = nullptr;
    
    SwitchBtn = make_unique<Button>("Resources/Textures/Back.png", "Resources/Textures/BackPressed.png", "Resources/Audio/ButtonSound.wav");
    PlayBtn = make_unique<Button>("Resources/Textures/Play.png", "Resources/Textures/PlayPressed.png", "Resources/Audio/ButtonSound.wav");
    SoundBtn = make_unique<Button>("Resources/Textures/Sound.png","Resources/Textures/SoundPressed.png", "Resources/Audio/ButtonSound.wav");
    IncBetBtn = make_unique<Button>("Resources/Textures/Inc.png","Resources/Textures/IncPressed.png","Resources/Audio/ButtonSound.wav");
    DecBetBtn = make_unique<Button>("Resources/Textures/Dec.png","Resources/Textures/DecPressed.png","Resources/Audio/ButtonSound.wav");
    
    ReelsPtr = make_unique<Reels>("Resources/Textures/Reel.png");
    
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

MainStage::~MainStage()
{
    // Unload textures
    TraceLog(LOG_INFO, "Main Stage: Destroyed");
    
    UnloadTexture(BackgroundTexture);
    UnloadTexture(MessageTexture);
    UnloadTexture(MessageTexture1);
    UnloadTexture(BottomBarTexture);
}

void MainStage::Update()
{
    // Update GUI
    SwitchBtn->Update();
    PlayBtn->Update();
    SoundBtn->Update();
    IncBetBtn->Update();
    DecBetBtn->Update();
    ReelsPtr->Update();
    
    // Change stage to info stage
    if (SwitchBtn->IsPressed())
    {
        Stage = make_shared<InfoStage>();
    }
    
    if ((PlayBtn->IsPressed() || IsKeyPressed(KEY_SPACE)) && ReelsManager.CheckCanPlay())
    {
        ReelsManager.SetRunning(true);
    }
    
    // Animate reels
    if (ReelsManager.IsRunning())
    {
        FramesCounter++;
        if (FramesCounter >= (60/FramesSpeed))
        {
            FramesCounter = 0;
            CurrentFrame++;
            ReelsManager.GenerateReels();
            
            if (CurrentFrame > 10) // Stop animation after frame 10
            {
                CurrentFrame = 0;
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
        ReelsManager.NextBet(true);
    }
    
    if (DecBetBtn->IsPressed())
    {
        ReelsManager.NextBet(false);
    }
}

void MainStage::Draw()
{
    // Draw background texture
    DrawTexture(BackgroundTexture, 0, 0, WHITE);
    
    // Draw bottom bar
    DrawTexture(BottomBarTexture, 30, GetScreenHeight()-55, Color{255,255,255,120});
    
    // Draw message frames
    DrawTexture(MessageTexture, 340, GetScreenHeight()-51.5f, WHITE);
    DrawTexture(MessageTexture1, 160, GetScreenHeight()-51.5f, WHITE);
    
    // Draw GUI
    SwitchBtn->Draw();
    PlayBtn->Draw();
    SoundBtn->Draw();
    IncBetBtn->Draw();
    DecBetBtn->Draw();
    ReelsPtr->Draw();
    
    // Draw a message indicating insufficient funds to play
    if (!ReelsManager.CheckCanPlay())
    {
        DrawText("Insufficient fund !", GetScreenWidth()/2, GetScreenWidth()/2, 40.0f, RED);
    }
    
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

shared_ptr<Stage> MainStage::GetStage() 
{ 
    return Stage;
}
