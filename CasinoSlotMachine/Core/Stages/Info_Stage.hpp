//
//  Info_Stage.hpp
//  CasinoSlotMachine
//
//  Created by Nicolas U on 18.02.24.
//

#include <stdio.h>
#include "Stage.hpp"
#include "../GUI/Button.hpp"

/**
    This stage displays information about the symbol values for payouts
 */
class cInfo_Stage : public cStage {
    
public:
    
    cInfo_Stage();
    ~cInfo_Stage();
    
    void Update() override;
    void Draw() override;
    shared_ptr<cStage> GetStage() override;
    
private:
    
    Texture2D BackgroundTexture;
    
    unique_ptr<cButton> SwitchBtn;
    
    shared_ptr<cStage> Stage;
    
};
