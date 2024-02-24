//
//  Button.cpp
//  CasinoSlotMachine
//
//  Created by Nicolas U on 14.02.24.
//

#include "Button.hpp"

Button::Button()
{
    // @TODO: Load some default texture
}

Button::Button(string TexturePath, string HoveredTexturePath, string SfxPath)
{
    try {
        BtnTexture = LoadTexture(TexturePath.c_str());
    } catch (const runtime_error& exc) {
        TraceLog(LOG_ERROR, "Texture failed to load");
    }
    
    try {
        BtnHoveredTexture = LoadTexture(HoveredTexturePath.c_str());
    } catch (const runtime_error& exc) {
        TraceLog(LOG_ERROR, "Texture failed to load");
    }
    
    try {
        BtnSFX = LoadSound(SfxPath.c_str());
    } catch (const runtime_error& exc) {
        TraceLog(LOG_ERROR, "Sound failed to load");
    }
}


Button::~Button()
{
    UnloadTexture(BtnTexture);
    UnloadTexture(BtnHoveredTexture);
    UnloadSound(BtnSFX);
    TraceLog(LOG_INFO, "Button: Destroyed");
}

void Button::SetPosition(Vector2 Position)
{
    Rectangle NewPosition = { Position.x, Position.y, static_cast<float>(BtnTexture.width), static_cast<float>(BtnTexture.height) };
    Collision = NewPosition;
}

void Button::Update()
{
    // Mouse position
    Vector2 MousePos = GetMousePosition();
    
    Action = false;
    SwitchTexture = false;
    
    // Check to determine if the mouse cursor is currently positioned within the boundary
    if (CheckCollisionPointRec(MousePos, Collision))
    {
        // Check if we're pressing or hovering the button
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            State = 2;
        } else {
            SwitchTexture = true;
            State = 1;
        }
        // If mouse button has been released, we perform an action
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
            PlaySound(BtnSFX);
            Action = true;
        }
    }
    else {
        Action = false;
    }
}

void Button::Draw()
{
    if (SwitchTexture)
    {
        DrawTexture(BtnHoveredTexture, Collision.x, Collision.y, WHITE);
    }
    DrawTexture(BtnTexture, Collision.x, Collision.y, WHITE);
}











