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

using namespace std;

/**
    This class manages which stage (cStage) is currently being displayed and rendered within the window
 */
class StageManager //@TODO: Add transition while changing; if(current != new) -> do transition
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
    shared_ptr<Stage> CurrentStage;
    
    /**
        Initialize the stage to being displayed and rendered within the window - this function is only called if there is no current stag
     */
    void Init();
    
    // Gets a current stage
    void GetStage();
};

