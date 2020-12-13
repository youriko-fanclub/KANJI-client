#pragma once

#include "SceneState.hpp"
#include "UIComponent.hpp"

namespace kanji {
namespace seq {


class ResultScene : public KanjiScene {
public: // static_const/enum
public: // static
public: // public function
    void update() override;
    void draw() const override;
private: // field
    dui::Button m_chara_select;
    dui::Button m_title;
    const std::shared_ptr<battle::BattleResultDesc>& m_battle_result_desc;
private: // private function
public: // ctor/dtor
    ResultScene(const InitData& init);
    ~ResultScene();
};
    
    
}
}

