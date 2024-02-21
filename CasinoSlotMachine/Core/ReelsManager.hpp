//
//  ReelsManager.hpp
//  CasinoSlotMachine
//
//  Created by Nicolas U on 14.02.24.
//

#pragma once

#include <stdio.h>
#include <string>
#include <vector>
#include <random>

#include "raylib.h"

using namespace std;

/**
    A custom data structure containing symbol data
 */
struct sSymbol
{
    string Name;
    Texture2D Texture;
    string TexturePath;
    float WinValue;
    int MinRandom;
    int MaxRandom;
};

/**
    Enumeration of winning lines
 */
enum eWinningLines
{
    HORIZONTAL_TOP,
    HORIZONTAL_MIDDLE,
    HORIZONTAL_BOTTOM,
    /** Diagonal line tracing from top to bottom **/
    DIAGONAL_TOP,
    /** Diagonal line tracing from bottom to top **/
    DIAGONAL_BOTTOM
};

/**
    Enumeration of bet values
    The values are in cents because enumerations do not support float values.
 */
enum BetValues
{
    ZERO_TEN = 10,
    ZERO_TWENTY = 20,
    ZERO_FOURTY = 40,
    ZERO_FIFTY = 50,
    ZERO_EIGHTY = 80,
    ONE = 100,
    ONE_FIFTY = 150,
    FIVE = 500,
    TEN = 1000,
    FIFTY = 5000,
    HUNDRED = 10000
};

class cReelsManager
{
    // Singleton
    cReelsManager();
    
public:
    
    // Singleton get instance method
    static cReelsManager& GetInstance();
    
    void Play();
    bool CheckCanPlay();
    
    void GenerateReels();
    
    /**
        Cycles through bets values - Fwd set to false cycles slots backward, else forward
     */
    void NextBet(bool Fwd);
    
    void LoadTextures();
    void UnloadTextures();
    
    // --------- Getters & Setters ---------- //
    float GetMoney() const { return Money; }
    float GetBet() const { return Bet; }
    float GetPayoutPrize() const { return PayoutPrize; }
    bool IsRunning() const { return Running; }
    vector<sSymbol> GetSymbols() const { return Symbols; }
    vector<vector<sSymbol>> GetReels() const { return Reels; }
    vector<eWinningLines> GetWinningLines() const { return WinningLines;}
    
    void SetMoney(float NewMoney)
    {
        Money = NewMoney;
    }
    
    void SetRunning(bool Value)
    {
        Running = Value;
    }
    
private:
 
    float Money = 200.0;
    float Bet = 0.20;
    
    float PayoutPrize;
    
    // Vector containing all possible bet values
    vector<BetValues> Bets = { ZERO_TEN, ZERO_TWENTY, ZERO_FOURTY, ZERO_FIFTY, ZERO_EIGHTY, ONE, ONE_FIFTY, FIVE, TEN, FIFTY, HUNDRED };
    
    // True, if the reels are still spinning, else false
    bool Running = false;
    
    // True, if we met conditions to play
    bool CanPlay = false;
    
    // Vector containing all possible symbol data
    vector<sSymbol> Symbols;
    
    // 2D-Vector containing reels filled with symbols
    vector<vector<sSymbol>> Reels;
    
    // Winning lines map
    vector<eWinningLines> WinningLines;
    
    
    /**
        Do binary search and find closest location element
        @return index of Symbol where [0,Symbols.size]  {Target : 0 <= Target <= Symbol.size}
     */
    int BiniarySearch(int Target);
    
    /**
        Generates random number in Range [Min,Max]
     */
    static int GenerateRandomNumber(int Min, int Max);

    /**
        Generate random number in range [0, 10000] & return symbol found using a biniary search
     */
    const sSymbol& PickRandomSymbol();
    
    /**
        Tries to find a matching line, and if one is found, stores it in a WinningLines map
        Line with a matching symbol pays (value multiplied by the bet)
     */
    void CheckLinesCond();
    
};

