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

using namespace std;

/**
    Display main stage
 */
class MainStage : public Stage
{
public:
    
    MainStage();
    ~MainStage();
    
    void Update() override;
    void Draw() override;
    shared_ptr<Stage> GetStage() override;
    
private:
    
    shared_ptr<Stage> Stage;
    
    ReelsManager& ReelsManager;
    
    Texture2D BackgroundTexture;
    Texture2D BottomBarTexture;
    Texture2D MessageTexture;
    Texture2D MessageTexture1;
    
    unique_ptr<Button> SwitchBtn; // Switch stage to InfoStage
    
    unique_ptr<Button> PlayBtn;
    
    unique_ptr<Button> SoundBtn;
    
    unique_ptr<Button> IncBetBtn;
    unique_ptr<Button> DecBetBtn;

    unique_ptr<Reels> ReelsPtr;
    
    bool SoundMuted = false;
    
    // Animation data for spinning reels
    int CurrentFrame = 0;
    int FramesCounter = 0;
    int FramesSpeed = 7;
};

