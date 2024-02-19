//
//  Main_Stage.hpp
//  CasinoSlotMachine
//
//  Created by Nicolas U on 14.02.24.
//

#include <stdio.h>
#include <string>
#include "Stage.hpp"
#include "../GUI/Button.hpp"
#include "../GUI/Reels.hpp"
#include "ReelsManager.hpp"
#include "raylib.h"

using namespace std;


class cMain_Stage : public cStage //@TODO: Unload texture while destructing
{
public:
    
    cMain_Stage();
    ~cMain_Stage();
    
    void Update() override;
    void Draw() override;
    shared_ptr<cStage> GetStage() override;
    
private:
    
    cReelsManager& ReelsManager;
    
    Texture2D BackgroundTexture;
    Texture2D BottomBarTexture;
    Texture2D MessageTexture;
    Texture2D MessageTexture1;
    
    shared_ptr<cStage> Stage;
    
    unique_ptr<cButton> SwitchBtn;
    unique_ptr<cButton> PlayBtn;
    unique_ptr<cButton> SoundBtn;
    unique_ptr<cButton> IncBetBtn;
    unique_ptr<cButton> DecBetBtn;

    unique_ptr<cReels> Reels;
    
    bool SoundMuted = false;
    
    // Animation data for spinning reels
    int currentFrame = 0;
    int framesCounter = 0;
    int framesSpeed = 7;
};

