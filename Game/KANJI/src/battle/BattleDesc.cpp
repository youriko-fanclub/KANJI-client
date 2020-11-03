#include "BattleDesc.hpp"

namespace kanji {
namespace battle {

/* ---------- BattleDesc ---------- */

// static ----------------------------------------
// public function -------------------------------
void BattleDesc::setPlayerDesc(dx::di::PlayerId id, const std::shared_ptr<BattlePlayerDesc>& value) {
    if (m_players.contains(id)) {
        m_players.at(id) = value;
    }
    else {
        m_players.insert(std::make_pair(id, value));
    }
}
// private function ------------------------------
// ctor/dtor -------------------------------------


}
}
