//
//  main.cpp
//  CasinoSlotMachine
//
//  Created by Nicolas U on 14.02.24.
//

#include "Core/Engine.hpp"

int main(int argc, const char * argv[])
{
    Engine& Engine = Engine::GetInstance();
    
    Engine.Run();
    
    return 0;
}
