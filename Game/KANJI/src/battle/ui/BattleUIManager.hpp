#pragma once
#include "PlayerId.hpp"
#include "UIComponent.hpp"

namespace kanji {
namespace battle {
class IBattleManager;
}
namespace ui {
class IHolderUI;

class BattleUIManager : public dx::ui::UIComponent {
public: // static_const/enum
public: // static
public: // public function
    void update();
protected: // protected function
    void drawImpl() const override;
private: // field
    const battle::IBattleManager* const m_battle_manager;
    std::unordered_map<dx::di::PlayerId, std::shared_ptr<IHolderUI>> m_holders;
private: // private function
public: // ctor/dtor
    BattleUIManager(const battle::IBattleManager* battle_manager);
};


}
}

