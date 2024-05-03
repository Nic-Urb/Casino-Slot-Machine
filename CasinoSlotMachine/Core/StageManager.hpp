//
//  StageManager.hpp
//  CasinoSlotMachine
//
//  Created by Nicolas U on 14.02.24.
//

#include <stdio.h>
#include <memory>
#include "Stage.hpp"
#include "raylib.h"

#include "MainStage.hpp"


/**
    This class manages which stage (Stage) is currently being displayed and rendered within the window
 */
class StageManager
{
    //Singleton
    StageManager();

public:
    
    // Singleton get instance method
    static StageManager& GetInstance();
    
    void Update();
    void Draw();
    bool Close();
    
private:
    
    // Tracks which stage is currently used
    std::shared_ptr<Stage> CurrentStage;
    
    // Flags indicating if a transition should be triggered
    bool Transition = false;
    
    float TransitionAlpha = 0.0f;
    
    void UpdateTransition();
    
    /**
        Initialize the stage to being displayed and rendered within the window - this function is only called if there is no current stag
     */
    void Init();
    
    // Gets a current stage
    void GetStage();
};

