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
BattlePlayerManager::BattlePlayerManager(const std::unordered_map<dx::di::PlayerId, std::shared_ptr<BattlePlayerDesc>>& descs) {
    for (const auto& desc : descs) {
        m_players.insert(std::make_pair(desc.first, std::make_shared<BattlePlayer>(desc.first, desc.second)));
    }
}


}
}

