#pragma once

#include "KanjiScene.hpp"
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
    void draw() const override;
private: // field
    std::shared_ptr<battle::IBattleManager> m_mgr;
    std::shared_ptr<ui::BattleUIManager> m_ui;
private: // private function
public: // ctor/dtor
    BattleScene(const InitData& init);
    
};


}
}
