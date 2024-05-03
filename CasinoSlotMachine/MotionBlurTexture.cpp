//
//  MotionBlurTexture.cpp
//  CasinoSlotMachine
//
//  Created by Nicolas U on 18.02.24.
//

#include "MotionBlurTexture.hpp"

MotionBlurTexture::MotionBlurTexture(const Texture2D& Texture, float Radius, float Angle, int Points) : Texture(Texture)
{
   auto GetPointOverLine = [=]  {
        auto AngleOverX = Angle - PI / 2;  // Angle 0 is a vertical line, so I rotate it 45 degrees clockwise (subtract)
        if (GetRandomValue(0, 1))
        {
            AngleOverX += PI;   // Half of the points will be on the "first quadrant", the other half over the "third", if you consider (0,0) the center of the circle
        }
        auto l = Radius * GetRandomValue(0, 1000) / 1000.0f;
        auto x = cos(AngleOverX) * l;
        auto y = sin(AngleOverX) * l;

        return Vector2{x, y};
    };

    while (this->Points.size() < Points)
    {
        this->Points.push_back(GetPointOverLine());
    }
}

void MotionBlurTexture::Draw() const
{
    for (const auto& Point : Points) 
    {
        DrawTexture(Texture, Point.x, Point.y, Fade(WHITE, 0.1f));
    }
}

void MotionBlurTexture::SetPosition(const Vector2& Pos)
{
    for (auto& Point : Points)
    {
        Point = { Point.x + Pos.x, Point.y + Pos.y };
    }
}
