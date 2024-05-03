//
//  Stage.hpp
//  CasinoSlotMachine
//
//  Created by Nicolas U on 14.02.24.
//
#pragma once

#include <stdio.h>
#include <memory>
#include <iostream>


/**
    This class contains a stage that can be rendered into a window. It serves as the base class; do not utilize it directly, instead use its subclasses
 */
class Stage {
    
public:
    
    virtual void Update() {}
    virtual void Draw() {}
    
    /** This method is utilized to establish the appropriate scene within a StageManager class, specifically intended to be invoked within the StageManager's update() function and returns either this stage or another stage **/
    virtual std::shared_ptr<Stage> GetStage();
};
