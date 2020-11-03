#pragma once

namespace kanji {
namespace battle {
    class IBattleManager;
}
namespace ui {

class BattleUIManager {
public: // static_const/enum
public: // static
public: // public function
    void draw() const {}
private: // field
    const battle::IBattleManager* const m_battle_manager;
private: // private function
public: // ctor/dtor
    BattleUIManager(const battle::IBattleManager* battle_manager) :
    m_battle_manager(battle_manager) {}
};


}
}

