#include "BattlePlayer.hpp"
#include "BattleDesc.hpp"
#include "ParameterizedCharacter.hpp"
#include "PhysicalMove.hpp"

namespace kanji {
namespace battle {


/* ---------- BattlePlayer ---------- */

// static ----------------------------------------
// public function -------------------------------
std::shared_ptr<chara::IParameterizedCharacter> BattlePlayer::activeCharacter() {
    if (0 <= m_activeIndex && m_activeIndex < m_characters.size()) {
        return m_characters.at(m_activeIndex);
    }
    else { return nullptr; }
}

void BattlePlayer::changeActiveCharacter() {
    const int source_index = m_activeIndex;
    while (true) {
        m_activeIndex = (m_activeIndex + 1) % m_characters.size();
        if (m_activeIndex == source_index) { return; }
        if (!m_characters.at(m_activeIndex)->isBurnedOut()) { return; }
    }
}

void BattlePlayer::damage(const MomentaryMove& move) {
    activeCharacter()->damage(move.damage);
    if (activeCharacter()->isBurnedOut()) {
        changeActiveCharacter();
    }
}
    
// private function ------------------------------
// ctor/dtor -------------------------------------
BattlePlayer::BattlePlayer(dx::di::PlayerId pid, const std::shared_ptr<BattlePlayerDesc>& desc) :
m_pid(pid),
m_activeIndex(0),
m_characters(desc->characters()) {}


}
}
