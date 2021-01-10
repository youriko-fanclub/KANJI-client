#include "BattlePlayer.hpp"
#include "BattleDesc.hpp"
#include "ParameterizedCharacter.hpp"
#include "PhysicalMove.hpp"
#include "Radical.hpp"

namespace kanji {
namespace battle {


/* ---------- BattlePlayer ---------- */

// static ----------------------------------------
// public function -------------------------------
std::shared_ptr<chara::IParameterizedCharacter> BattlePlayer::activeCharacter() {
    if (0 <= m_active_index && m_active_index < m_characters.size()) {
        return m_characters.at(m_active_index);
    }
    else { return nullptr; }
}

bool BattlePlayer::changeActiveCharacter() {
    const int source_index = m_active_index;
    while (true) {
        m_active_index = (m_active_index + 1) % m_characters.size();
        if (m_active_index == source_index) { return false; }
        if (!m_characters.at(m_active_index)->isBurnedOut()) { return true; }
    }
}

bool BattlePlayer::hasRadical() const {
    return m_radical != nullptr;
}
const std::unique_ptr<chara::Radical>& BattlePlayer::radical() const {
    return m_radical;
}
void BattlePlayer::setRadical(RadicalID radical_id) {
    m_radical = std::make_unique<chara::Radical>(radical_id);
}

void BattlePlayer::attack(const MomentaryMove& move, bool is_from_left) {
    activeCharacter()->damage(move.damage);
    if (is_from_left) { // 左側から被弾したならそのまま
        m_physical->shoot(move.shoot_force);
    }
    else { // 右側からならy軸対称
        // y軸の正の方向が0[rad]
        m_physical->shoot(s3d::Circular(move.shoot_force.r, -move.shoot_force.theta));
    }
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
m_active_index(0),
m_characters(desc->characters()),
m_is_lost(false) {}


}
}
