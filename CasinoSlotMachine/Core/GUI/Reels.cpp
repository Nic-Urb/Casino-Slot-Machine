//
//  Reels.cpp
//  CasinoSlotMachine
//
//  Created by Nicolas U on 15.02.24.
//

#include "Reels.hpp"


Reels::Reels(const std::string& ReelTexturePath) :
    ReelsManager(ReelsManager::GetInstance())
{
    Init(ReelTexturePath);
}

Reels::~Reels()
{
    // Unload textures
    UnloadTexture(ReelsTexture);
    ReelsManager.UnloadTextures();
}

void Reels::Update()
{
}

void Reels::Draw()
{
    const std::vector<std::vector<Symbol>> Reels = ReelsManager.GetReels();
    
    // Draw 3 reels from a middle point
    for (int i = 0; i < 3; i++) {
        DrawTexture(ReelsTexture, ReelsPositions[i].x, ReelsPositions[i].y, Color{255,255,255,200});
    }
    
    //Calculates the position of each new symbol for reels
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            const Texture2D Texture = Reels[j][i].Texture;
            const float y = ReelsPositions[i].y + (ReelsTexture.width / 3) * (2.33f * j) - Texture.height / 2 + 58;

            DrawTexture(Texture, ReelsPositions[i].x + (ReelsTexture.width - Texture.height) / 2, y, WHITE);
            
            if (ReelsManager.IsRunning())
            {
                MotionBlurTexture MotionBlur = MotionBlurTexture(Texture, 20, 0, 100);
                MotionBlur.SetPosition({ReelsPositions[i].x + (ReelsTexture.width - Texture.height) / 2,y});
                MotionBlur.Draw();
            }
        }
    }
    
    DrawLines();
}

void Reels::Init(const std::string& ReelTexturePath)
{
    // Load reels texture
    ReelsTexture = LoadTexture(ReelTexturePath.c_str());
    
    // Initialize reels positions
    ReelsPositions.push_back({ ((GetScreenWidth() / 2.0f) - ReelsTexture.width / 2.0f) - 200,
        (GetScreenHeight() / 2.0f) - ReelsTexture.height / 2.0f });
    ReelsPositions.push_back({ (GetScreenWidth() / 2.0f) - ReelsTexture.width / 2.0f,
        (GetScreenHeight() / 2.0f) - ReelsTexture.height / 2 });
    ReelsPositions.push_back({ ((GetScreenWidth() / 2.0f) - ReelsTexture.width / 2.0f) + 200,
        (GetScreenHeight() / 2.0f) - ReelsTexture.height / 2.0f });
    
    // Load all symbols textures
    ReelsManager.LoadTextures();
}

void Reels::DrawLines()
{
    std::vector<WinningLines> Lines = ReelsManager.GetWinningLines();
    
    const int ReelWidth = ReelsTexture.width;
    const int ReelHeight = ReelsTexture.height;

    for (const auto& Line : Lines)
    {
        switch (Line)
        {
            case HORIZONTAL_TOP:
                DrawLineEx({ReelsPositions[0].x,ReelsPositions[0].y+(ReelHeight/6)}, {ReelsPositions[2].x+ReelWidth,ReelsPositions[2].y+(ReelHeight/6)}, 5.0f, MAGENTA);
                break;
                
            case HORIZONTAL_MIDDLE:
                DrawLineEx({ReelsPositions[0].x,ReelsPositions[0].y+(ReelsTexture.height/2)}, {ReelsPositions[2].x+ReelsTexture.width,ReelsPositions[2].y+(ReelsTexture.height/2)}, 5.0f, PURPLE);
                break;
                
            case HORIZONTAL_BOTTOM:
                DrawLineEx({ReelsPositions[0].x,ReelsPositions[0].y+(ReelHeight/2)+(ReelHeight/3)}, {ReelsPositions[2].x+ReelWidth,(ReelsPositions[2].y+(ReelHeight/2))+(ReelHeight/3)}, 5.0f, PURPLE);
                break;
                
            case DIAGONAL_TOP:
                DrawLineEx({ReelsPositions[0].x, ReelsPositions[0].y}, {ReelsPositions[2].x+ReelWidth,ReelsPositions[2].y+ReelHeight}, 5.0f, GREEN);
                break;
                
            case DIAGONAL_BOTTOM:
                DrawLineEx({ReelsPositions[0].x, ReelsPositions[0].y+ReelHeight}, {ReelsPositions[2].x+ReelWidth,ReelsPositions[2].y}, 5.0f, RED);
                break;
    
            default:
                break;
        }
    }
}





