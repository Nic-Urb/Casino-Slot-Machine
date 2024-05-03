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
class InfoStage : public Stage {
    
public:
    
    InfoStage();
    ~InfoStage();
    
    void Update() override;
    void Draw() override;
    std::shared_ptr<Stage> GetStage() override;
    
private:
    
    Texture2D BackgroundTexture;
    
    std::unique_ptr<Button> SwitchBtn;
    
    std::shared_ptr<Stage> Stage;
    
};
