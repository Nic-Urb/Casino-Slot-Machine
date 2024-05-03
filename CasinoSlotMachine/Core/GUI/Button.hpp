//
//  Button.hpp
//  CasinoSlotMachine
//
//  Created by Nicolas U on 14.02.24.
//

#pragma once

#include <stdio.h>
#include <string>
#include "raylib.h"

/**
    This class contains a button along with its logic, which can be rendered within a window
 */
class Button
{
    
public:
    
    Button();
    Button(const std::string& TexturePath, const std::string& HoveredTexturePath, const std::string& SfxPath);
    ~Button();
    
    
    void Update();
    void Draw();
    
    bool IsPressed() { return Action; }
    
    void SetPosition(Vector2 Position);
    
private:
    
    // Button texture
    Texture2D BtnTexture;
    
    // Hovered button texture
    Texture2D BtnHoveredTexture;
    
    // Button sound effect
    Sound BtnSFX;
    
    /**
        0 = NOT_PRESSED
        1 = MOUSE_HOVERED
        2 = PRESSED
     */
    int State = 0;
    
    // True indicates that the button is pressed, allowing us to trigger an action
    bool Action = false;
    
    // True indicates that the button texture should be changed
    bool SwitchTexture = false;
    
    // Collision on screen
    Rectangle Collision;
    
};

