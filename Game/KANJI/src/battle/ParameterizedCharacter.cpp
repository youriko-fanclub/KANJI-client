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
    if (m_hp > amount) {
        m_hp -= amount;
    }
    else {
        m_hp = 0.f;
        m_is_burned_out = true;
    }
}

// private function ------------------------------
// ctor/dtor -------------------------------------
ParameterizedCharacter::ParameterizedCharacter(const KanjiID id) :
m_md(md::MasterKanjiParamRepository::instance()->at(id)),
m_ud({
    .hp = 10,
    .attack = 10,
    .defence = 10,
    .speed = 10,
    .jump = 10,
    .weight = 10,
}),
m_ability(std::make_unique<Ability>(m_md, &m_ud)),
m_initial_ability(std::make_unique<ConstantAbility>(*m_ability)) {}

}
}
