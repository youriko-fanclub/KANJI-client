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

// private function ------------------------------
// ctor/dtor -------------------------------------
ParameterizedCharacter::ParameterizedCharacter(const KanjiID id) :
m_md(md::MasterKanjiParamRepository::instance()->at(id)),
m_ud(id, 10, 10, 10, 10, 10),
m_ability(std::make_unique<KanjiAbility>(m_md, &m_ud)),
m_initial_ability(std::make_unique<ConstantAbility>(*m_ability)) {}

}
}
