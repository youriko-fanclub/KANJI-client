#pragma once

#include "SceneState.hpp"
#include "UIComponent.hpp"

namespace kanji {
namespace battle {
    class IBattleManager;
}
namespace ui {
    class BattleUIManager;
}
namespace seq {


class BattleScene : public KanjiScene {
public: // static_const/enum
public: // static
public: // public function
    void initialize();
    void update() override;
    void updateLegacy(); // 近いうちに消す
    void draw() const override;
    void drawLegacy() const; // 近いうちに消す
private: // field
    std::shared_ptr<battle::IBattleManager> m_mgr;
    std::shared_ptr<ui::BattleUIManager> m_ui;
private: // private function
public: // ctor/dtor
    BattleScene(const InitData& init);
    
};


}
}
