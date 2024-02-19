//
//  MotionBlurTexture.hpp
//  CasinoSlotMachine
//
//  Created by Nicolas U on 18.02.24.
//

#pragma once

#include <stdio.h>
#include <random>
#include "raylib.h"

using namespace std;

/**
 
 */
class cMotionBlurTexture
{
public:
    
    cMotionBlurTexture(Texture2D Texture, float Radius, float Angle, int Points);

    void Draw() const;
    void SetPosition(Vector2 Pos);

private:
    vector<Vector2> Points;
    Texture2D Texture;
};

