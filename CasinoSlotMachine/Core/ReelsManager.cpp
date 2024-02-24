//
//  ReelsManager.cpp
//  CasinoSlotMachine
//
//  Created by Nicolas U on 14.02.24.
//

#include "ReelsManager.hpp"



ReelsManager::ReelsManager() :
            Reels(3,vector<Symbol>(3)) // Init 3x3 vector matrix - 3 reels with 3 slots on each
{
    // Fill symbols vector - insert objects at the end of vector
    Symbols.push_back({"S", Texture(), "Resources/Textures/Symbols/Symbol1.png", 100.0, 0, 200});
    Symbols.push_back({"A", Texture(), "Resources/Textures/Symbols/Symbol2.png", 25.0, 201, 500});
    Symbols.push_back({"K", Texture(), "Resources/Textures/Symbols/Symbol3.png", 10.0, 501, 1200});
    Symbols.push_back({"Q", Texture(), "Resources/Textures/Symbols/Symbol4.png", 5.0, 1201, 2500});
    Symbols.push_back({"J", Texture(), "Resources/Textures/Symbols/Symbol6.png", 2.0, 2501, 3800});
    Symbols.push_back({"10", Texture(), "Resources/Textures/Symbols/Symbol7.png", 0.5, 3801, 6500});
    Symbols.push_back({"9", Texture(), "Resources/Textures/Symbols/Symbol8.png", 0.2, 6501 ,10000});
}


ReelsManager &ReelsManager::GetInstance()
{
    static ReelsManager Instance;
    return Instance;
}

void ReelsManager::Play()
{
    // Check these conditions, before we proced to check the winning cond.
    if (CheckCanPlay())
    {
        CheckLinesCond();
        Money-=Bet;
    }
    else
    {
        // If the player does not meet the conditions, display a message indicating insufficient funds or invalid bet amount
    }
}

bool ReelsManager::CheckCanPlay()
{
    // Check these conditions, before we call play function
    return (Money >= Bet && Bet > 0.0) ? true : false;
}


void ReelsManager::NextBet(bool Fwd)
{    
    // First we need to find location of current bet
    int FoundIndex = -1;
    for (int i = 0; i < Bets.size(); i++)
    {
        if (Bets[i] == Bet*100)
        {
            FoundIndex = i;
            break; // Exit loop once the index is found
        }
    }
    
    // Check if FoundIndex is valid
    if (FoundIndex == -1)
    {
        return;
    }
    
    // Calculate the direction of cycling
    const int Offset = (Fwd ? 1 : -1);
    
    // Use modulo for wrapping the value around
    const int NextIndex = (FoundIndex + Offset + Bets.size()) % Bets.size();
    
    
    // Update bet values base on the next index
    Bet = Bets[NextIndex] / 100.0;
}


void ReelsManager::LoadTextures()
{
    for (auto& Symbol : Symbols)
    {
        Symbol.Texture = LoadTexture(Symbol.TexturePath.c_str());
    }
}

void ReelsManager::UnloadTextures()
{
    for (auto& Symbol : Symbols) 
    {
        UnloadTexture(Symbol.Texture);
    }
}

int ReelsManager::BiniarySearch(int Target)
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

int ReelsManager::GenerateRandomNumber(int Min, int Max)
{
    random_device rd; // Random device, gives some initial randomness to help initialize things
    mt19937 gen(rd()); // Algorithm to generate the random number
    uniform_int_distribution<int> dis(Min,Max);
    return dis(gen);
}

const Symbol& ReelsManager::PickRandomSymbol()
{
    const int RandNumber = GenerateRandomNumber(0, 10000);
    return Symbols[BiniarySearch(RandNumber)];
}

void ReelsManager::GenerateReels()
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

void ReelsManager::CheckLinesCond()
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
                WinningLines.push_back(WinningLines::HORIZONTAL_TOP);
            } else if (i == 1)
            {
                WinningLines.push_back(WinningLines::HORIZONTAL_MIDDLE);
            } else {
                WinningLines.push_back(WinningLines::HORIZONTAL_BOTTOM);
            }
            Payout += Reels[i][0].WinValue*Bet;
        }
    }
    // Check diagonal lines
    if (Reels[0][0].Name.compare(Reels[1][1].Name) == 0 && Reels[1][1].Name.compare(Reels[2][2].Name) == 0)
    {
        WinningLines.push_back(WinningLines::DIAGONAL_TOP);
        Payout += Reels[0][0].WinValue*Bet;
    }
    if (Reels[2][0].Name.compare(Reels[1][1].Name) == 0 && Reels[1][1].Name.compare(Reels[0][2].Name) == 0) 
    {
        WinningLines.push_back(WinningLines::DIAGONAL_BOTTOM);
        Payout += Reels[2][0].WinValue*Bet;
    }
    
    // Update PayoutPrize and Money
    PayoutPrize=Payout;
    Money+=Payout;
}




