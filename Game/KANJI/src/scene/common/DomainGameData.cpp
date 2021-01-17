#include "DomainGameData.hpp"
#include "BattleDesc.hpp"

namespace kanji {
namespace seq {

/* ---------- DomainGameData ---------- */

// static ----------------------------------------
// public function -------------------------------
const std::shared_ptr<battle::BattleDesc>& DomainGameData::battleDesc() {
    if (!m_battle_desc) {
        m_battle_desc = std::make_shared<kanji::battle::BattleDesc>();
    }
    return m_battle_desc;
}
const std::shared_ptr<battle::BattleResultDesc>& DomainGameData::battleResultDesc() {
    return m_battle_result_desc;
}
void DomainGameData::setBattleDesc(const std::shared_ptr<battle::BattleDesc>& value) {
    m_battle_desc = value;
}
void DomainGameData::setBattleResultDesc(const std::shared_ptr<battle::BattleResultDesc>& value) {
    m_battle_result_desc = value;
}
bool DomainGameData::readyToBattle() const {
    return m_battle_desc && m_battle_desc->readyToBattle();
}

// private function ------------------------------
// ctor/dtor -------------------------------------


}
}
