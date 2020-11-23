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

bool BattlePlayer::changeActiveCharacter() {
    const int source_index = m_activeIndex;
    while (true) {
        m_activeIndex = (m_activeIndex + 1) % m_characters.size();
        if (m_activeIndex == source_index) { return false; }
        if (!m_characters.at(m_activeIndex)->isBurnedOut()) { return true; }
    }
}

void BattlePlayer::damage(const MomentaryMove& move) {
    activeCharacter()->damage(move.damage);
    m_score.given_damage = move.damage;
    if (activeCharacter()->isBurnedOut()) {
        ++m_score.dead_count;
        if (!changeActiveCharacter()) {
            lose();
        }
    }
}

const BattlePlayer::Score& BattlePlayer::scoreForRanked() {
    m_score.left_hp_rate = 0.f;
    if (m_is_lost) { return m_score; }
    for (const auto& chara : m_characters) {
        m_score.left_hp_rate += chara->hpRate();
    }
    return m_score;
}
    
// private function ------------------------------
void BattlePlayer::lose() {
    if (m_is_lost) { return; }
    m_is_lost = true;
    m_physical.reset();
}

// ctor/dtor -------------------------------------
BattlePlayer::BattlePlayer(dx::di::PlayerId pid, const std::shared_ptr<BattlePlayerDesc>& desc) :
m_pid(pid),
m_activeIndex(0),
m_characters(desc->characters()),
m_is_lost(false) {}


}
}
