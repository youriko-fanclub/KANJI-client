#include "Ability.hpp"
#include "ParameterizedCharacter.hpp"
#include "Radical.hpp"

namespace kanji {
namespace chara {

/* ---------- Ability ---------- */

// static ----------------------------------------
// public function -------------------------------
int Ability::attack() const {
    Radical radical(RadicalID(100000));
    return m_md->attack() + m_ud->attack;// + radical.attack();
}
int Ability::defence() const {
    Radical radical(RadicalID(100000));
    return m_md->defence() + m_ud->defence;// + radical.defence();
}
int Ability::speed() const {
    Radical radical(RadicalID(100000));
    return m_md->speed() + m_ud->speed;// + radical.speed();
}
int Ability::jump() const {
    Radical radical(RadicalID(100000));
    return m_md->jump() + m_ud->jump;// + radical.jump();
}
int Ability::weight() const {
    Radical radical(RadicalID(100000));
    return m_md->weight() + m_ud->weight;// + radical.weight();
}

// private function ------------------------------
// ctor/dtor -------------------------------------

}
}

