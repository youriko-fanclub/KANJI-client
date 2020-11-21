#include "BattleUIManager.hpp"
#include "BattleManager.hpp"
#include "BattlePlayerManager.hpp"
#include "BattlePlayer.hpp"
#include "PhysicalWorldManager.hpp"
#include "HolderUI.hpp"

namespace kanji {
namespace ui {


/* ---------- BattleUIManager ---------- */

// static ----------------------------------------
// public function -------------------------------
void BattleUIManager::update() {
    for (auto& holder : m_holders) {
        holder.second->update();
    }
}

void BattleUIManager::drawImpl() const {
    for (const auto& holder : m_holders) {
        holder.second->draw();
    }
    m_battle_manager->worldMgr()->drawLegacy();
}

// private function ------------------------------
// ctor/dtor -------------------------------------
BattleUIManager::BattleUIManager(const battle::IBattleManager* battle_manager) :
m_battle_manager(battle_manager) {
    const auto& players = m_battle_manager->playerMgr()->players();
    const int player_num = static_cast<int>(players.size());
    for (int i = 0; const auto& player : players) {
        m_holders.insert(std::make_pair(player.first,
            std::make_shared<HolderUI>(i, player_num, player.second)));
        ++i;
    }
}


}
}
