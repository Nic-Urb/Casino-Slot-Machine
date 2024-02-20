//
//  Engine.hpp
//  CasinoSlotMachine
//
//  Created by Nicolas U on 14.02.24.
//


#include <stdio.h>
#include <string>
#include "StageManager.hpp"
#include "raylib.h"


using namespace std;

/**
    A core class responsible for running the entire game loop
 */
class cEngine
{
    // Singleton
    cEngine();
    
public:
    
    // Singleton get instance method
    static cEngine& GetInstance();
    
    void Run();
    
private:
    
    // Window size:
    const int WindowWidth = 800;
    const int WindowHeight = 450;
    
    // StageManager instance
    cStageManager& StageManager;
};
