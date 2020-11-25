#include "ParameterizedCharacter.hpp"

namespace kanji {
namespace chara {

/* ---------- ParameterizedCharacter ---------- */

// static ----------------------------------------
// public function -------------------------------
void ParameterizedCharacter::damage(int amount) {
    if (amount <= 0) { return; }
    if (m_params.hp > amount) {
        m_params.hp -= amount;
    }
    else {
        m_params.hp = 0.f;
        m_isBurnedOut = true;
    }
}

// private function ------------------------------
// ctor/dtor -------------------------------------

}
}
