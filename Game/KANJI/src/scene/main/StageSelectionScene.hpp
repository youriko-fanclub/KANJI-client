#pragma once

#include "KanjiScene.hpp"
#include "UIComponent.hpp"

namespace kanji {
namespace seq {


class StageSelectionScene : public KanjiScene {
public: // static_const/enum
public: // static
public: // public function
    void update() override;
    void draw() const override;
private: // field
    dui::Button m_battle_start;
    dui::Button m_back;
private: // private function
    void selectStage() const;
public: // ctor/dtor
    StageSelectionScene(const InitData& init);
};
    
    
}
}


