//
//  ReelsManager.cpp
//  CasinoSlotMachine
//
//  Created by Nicolas U on 14.02.24.
//

#include "ReelsManager.hpp"



cReelsManager::cReelsManager() :
            Reels(3,vector<sSymbol>(3)) // Init 3x3 vector matrix - 3 reels with 3 slots on each
{
    // Fill symbols vector - insert objects at the end of vector
    Symbols.push_back({"S", Texture(), "Resources/Textures/Symbols/Symbol1.png", 50.0, 0, 300});
    Symbols.push_back({"A", Texture(), "Resources/Textures/Symbols/Symbol2.png", 10.0, 301, 1000});
    Symbols.push_back({"K", Texture(), "Resources/Textures/Symbols/Symbol3.png", 5.0, 1001, 3500});
    Symbols.push_back({"Q", Texture(), "Resources/Textures/Symbols/Symbol6.png", 2.0, 3501, 6500});
    Symbols.push_back({"J", Texture(), "Resources/Textures/Symbols/Symbol7.png" ,1.0, 6501, 10000});
}


cReelsManager &cReelsManager::GetInstance()
{
    static cReelsManager Instance;
    return Instance;
}

void cReelsManager::Play()
{
    // Check these conditions, before we proced to check the winning cond.
    if (Money >= Bet && Bet > 0.0)
    {
        CheckLinesCond();
        Money-=Bet;
    }
    else
    {
        // If the player does not meet the conditions, display a message indicating insufficient funds or invalid bet amount
    }
}

void cReelsManager::LoadTextures()
{
    for (auto& Symbol : Symbols)
    {
        Symbol.Texture = LoadTexture(Symbol.TexturePath.c_str());
    }
}

void cReelsManager::UnloadTextures() 
{
    for (auto& Symbol : Symbols) 
    {
        UnloadTexture(Symbol.Texture);
    }
}

int cReelsManager::BiniarySearch(int Target)
{
    const size_t Size = Symbols.size();
    
    int Idx_min = 0; // left half
    int Idx_max = static_cast<int>(Size)-1; // right half

    while (Idx_min <= Idx_max)
    {
        const int Idx_mid = Idx_min + (Idx_max - Idx_min) / 2;
        
        // check if target is present at mid
        if (Symbols[Idx_mid].MinRandom <= Target && Symbols[Idx_mid].MaxRandom >= Target) {
            return Idx_mid;
        }
        
        // if target greater, ignore left half
        if (Symbols[Idx_mid].MinRandom < Target) {
            Idx_min = Idx_mid + 1;
        }
        
        // if target is smaller, ignore right half
        else {
            Idx_max = Idx_mid - 1;
        }
    }
    // if we're reaching here, then value is higher then last element
    return Idx_max;
}

int cReelsManager::GenerateRandomNumber(int Min, int Max)
{
    random_device rd; // Random device, gives some initial randomness to help initialize things
    mt19937 gen(rd()); // Algorithm to generate the random number
    uniform_int_distribution<int> dis(Min,Max);
    return dis(gen);
}

const sSymbol& cReelsManager::PickRandomSymbol() 
{
    const int RandNumber = GenerateRandomNumber(0, 10000);
    return Symbols[BiniarySearch(RandNumber)];
}

void cReelsManager::GenerateReels() 
{
    // Iterate through Reels and set random value for each
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++) 
        {
            Reels[i][j] = PickRandomSymbol();
        }
    }
}

void cReelsManager::CheckLinesCond()
{
    float Payout = 0;
    // Before checking the line conditions, verify if the map is empty so that we can fill it with data
    if (!WinningLines.empty()) {
        WinningLines.clear();
    }
    
    // Check horizontal lines
    for (int i = 0; i < 3; i++)
    {
        if (Reels[i][0].Name.compare(Reels[i][1].Name) == 0 && Reels[i][1].Name.compare(Reels[i][2].Name) == 0) 
        {
            if (i == 0)
            {
                WinningLines.push_back(eWinningLines::HORIZONTAL_TOP);
            } else if (i == 1)
            {
                WinningLines.push_back(eWinningLines::HORIZONTAL_MIDDLE);
            } else {
                WinningLines.push_back(eWinningLines::HORIZONTAL_BOTTOM);
            }
            Payout += Reels[i][0].WinValue*Bet;
        }
    }
    // Check diagonal lines
    if (Reels[0][0].Name.compare(Reels[1][1].Name) == 0 && Reels[1][1].Name.compare(Reels[2][2].Name) == 0)
    {
        WinningLines.push_back(eWinningLines::DIAGONAL_TOP);
        Payout += Reels[0][0].WinValue*Bet;
    }
    if (Reels[2][0].Name.compare(Reels[1][1].Name) == 0 && Reels[1][1].Name.compare(Reels[0][2].Name) == 0) 
    {
        WinningLines.push_back(eWinningLines::DIAGONAL_BOTTOM);
        Payout += Reels[2][0].WinValue*Bet;
    }
    
    // Update PayoutPrize and Money
    PayoutPrize=Payout;
    Money+=Payout;
}



