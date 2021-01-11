#include "Ability.hpp"
#include "ParameterizedCharacter.hpp"
#include "Radical.hpp"

namespace kanji {
namespace chara {

/* ---------- KanjiAbility ---------- */

// static ----------------------------------------
// public function -------------------------------
int KanjiAbility::attack() const {
    return m_md->attack() + m_ud->attack() + m_radical_holder->ability()->attack();
}
int KanjiAbility::defence() const {
    return m_md->defence() + m_ud->defence() + m_radical_holder->ability()->defence();
}
int KanjiAbility::speed() const {
    return m_md->speed() + m_ud->speed() + m_radical_holder->ability()->speed();
}
int KanjiAbility::jump() const {
    return m_md->jump() + m_ud->jump() + m_radical_holder->ability()->jump();
}
int KanjiAbility::weight() const {
    return m_md->weight() + m_ud->weight() + m_radical_holder->ability()->weight();
}

// private function ------------------------------
// ctor/dtor -------------------------------------


/* ---------- RadicalAbility ---------- */

// static ----------------------------------------
// public function -------------------------------
int RadicalAbility::attack() const {
    return m_md->attack() + m_ud->attack();
}
int RadicalAbility::defence() const {
    return m_md->defence() + m_ud->defence();
}
int RadicalAbility::speed() const {
    return m_md->speed() + m_ud->speed();
}
int RadicalAbility::jump() const {
    return m_md->jump() + m_ud->jump();
}
int RadicalAbility::weight() const {
    return m_md->weight() + m_ud->weight();
}

// private function ------------------------------
// ctor/dtor -------------------------------------

}
}

