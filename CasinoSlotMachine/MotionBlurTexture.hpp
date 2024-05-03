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



class MotionBlurTexture
{
public:
    
    MotionBlurTexture(const Texture2D& Texture, float Radius, float Angle, int Points);

    void Draw() const;
    void SetPosition(const Vector2& Pos);

private:
    std::vector<Vector2> Points;
    Texture2D Texture;
};

