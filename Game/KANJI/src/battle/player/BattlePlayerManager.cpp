#include "BattlePlayerManager.hpp"
#include "BattleDesc.hpp"
#include "BattlePlayer.hpp"

namespace kanji {
namespace battle {

/* ---------- BattlePlayerManager ---------- */

// static ----------------------------------------
// public function -------------------------------
// private function ------------------------------
// ctor/dtor -------------------------------------
BattlePlayerManager::BattlePlayerManager(const s3d::HashTable<dx::di::PlayerId, std::shared_ptr<BattlePlayerDesc>>& descs) {
    for (const auto& desc : descs) {
        auto battle_player =  std::make_shared<BattlePlayer>(desc.first, desc.second);
        m_players.emplace(desc.first, battle_player);
        m_alivePlayers.emplace(desc.first, battle_player);
    }
}


}
}

