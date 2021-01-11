#include "Ability.hpp"
#include "ParameterizedCharacter.hpp"
#include "Radical.hpp"

namespace kanji {
namespace chara {

/* ---------- KanjiAbility ---------- */

// static ----------------------------------------
// public function -------------------------------
int KanjiAbility::attack() const {
    Radical radical(RadicalID(100000));
    return m_md->attack() + m_ud->attack();// + radical.attack();
}
int KanjiAbility::defence() const {
    Radical radical(RadicalID(100000));
    return m_md->defence() + m_ud->defence();// + radical.defence();
}
int KanjiAbility::speed() const {
    Radical radical(RadicalID(100000));
    return m_md->speed() + m_ud->speed();// + radical.speed();
}
int KanjiAbility::jump() const {
    Radical radical(RadicalID(100000));
    return m_md->jump() + m_ud->jump();// + radical.jump();
}
int KanjiAbility::weight() const {
    Radical radical(RadicalID(100000));
    return m_md->weight() + m_ud->weight();// + radical.weight();
}

// private function ------------------------------
// ctor/dtor -------------------------------------


/* ---------- RadicalAbility ---------- */

// static ----------------------------------------
// public function -------------------------------
int RadicalAbility::attack() const {
    Radical radical(RadicalID(100000));
    return m_md->attack() + m_ud->attack();// + radical.attack();
}
int RadicalAbility::defence() const {
    Radical radical(RadicalID(100000));
    return m_md->defence() + m_ud->defence();// + radical.defence();
}
int RadicalAbility::speed() const {
    Radical radical(RadicalID(100000));
    return m_md->speed() + m_ud->speed();// + radical.speed();
}
int RadicalAbility::jump() const {
    Radical radical(RadicalID(100000));
    return m_md->jump() + m_ud->jump();// + radical.jump();
}
int RadicalAbility::weight() const {
    Radical radical(RadicalID(100000));
    return m_md->weight() + m_ud->weight();// + radical.weight();
}

// private function ------------------------------
// ctor/dtor -------------------------------------

}
}

