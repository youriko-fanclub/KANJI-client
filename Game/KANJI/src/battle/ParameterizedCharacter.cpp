#include "ParameterizedCharacter.hpp"
#include "MasterKanjiParamRepository.hpp"
#include "Radical.hpp"

namespace kanji {
namespace chara {

/* ---------- ParameterizedCharacter ---------- */

// static ----------------------------------------
// public function -------------------------------
void ParameterizedCharacter::damage(int amount) {
    if (amount <= 0) { return; }
    if (m_status.hp() > amount) {
        m_status.damage(amount);
    }
    else {
        m_status.setHp(0.f);
        m_status.burnOut();
    }
}

void ParameterizedCharacter::setRadical(const RadicalHolder* radical_holder) {
    m_ability = std::make_unique<KanjiAbility>(m_md, &m_ud, radical_holder);
}

// private function ------------------------------
// ctor/dtor -------------------------------------
ParameterizedCharacter::ParameterizedCharacter(const KanjiID id) :
m_md(md::MasterKanjiParamRepository::instance()->at(id)),
m_ud(id, U"", 10, 10, 10, 10, 10),
m_ability(std::make_unique<ConstantAbility>(
    m_md->attack() + m_ud.attack(),
    m_md->defence() + m_ud.defence(),
    m_md->speed() + m_ud.speed(),
    m_md->jump() + m_ud.jump(),
    m_md->weight() + m_ud.weight()
)),
m_initial_ability(std::make_unique<ConstantAbility>(*m_ability)) {}

}
}
