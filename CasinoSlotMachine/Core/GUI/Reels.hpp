//
//  Reels.hpp
//  CasinoSlotMachine
//
//  Created by Nicolas U on 15.02.24.
//

#include <stdio.h>
#include <string>
#include "../ReelsManager.hpp"
#include "MotionBlurTexture.hpp"
#include "raylib.h"

using namespace std;

/**
    This class contains a reels , which can be rendered within a window
 */
class cReels
{
    
public:
    
    cReels(string ReelTexturePath);
    ~cReels();
    
    void Update();
    void Draw();
    
private:
    
    // Instance to ReelsManager class
    cReelsManager& ReelsManager;
    
    vector<Vector2> ReelsPositions;
    
    Texture2D ReelsTexture;
    
    /**
        Initialize three reels columns and save them in the 'Reels' variable
     */
    void Init(string ReelTexturePath);
    
    void DrawLines();
};
