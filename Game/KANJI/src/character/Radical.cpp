#include "Radical.hpp"
#include "MasterRadicalParamRepository.hpp"

namespace kanji {
namespace chara {

/* ---------- Radical ---------- */

// static ----------------------------------------
// public function -------------------------------
s3d::String Radical::chara() const {
    return m_md->character();
}
// private function ------------------------------
// ctor/dtor -------------------------------------
Radical::Radical(RadicalID id) :
m_md(md::MasterRadicalParamRepository::instance()->at(id)),
m_ud(KanjiID(0), 30, 30, 30, 30, 30),
m_ability(m_md, &m_ud) {}


/* ---------- RadicalHolder ---------- */

// static ----------------------------------------
const ConstantAbility RadicalHolder::s_zero = ConstantAbility(0, 0, 0, 0, 0);
// public function -------------------------------
s3d::String RadicalHolder::chara() const {
    if (hasRadical()) {
        return m_radical->chara();
    }
    else {
        return U"";
    }
}
const IAbility* RadicalHolder::ability() const {
    if (hasRadical()) {
        return m_radical->ability();
    }
    else {
        return &s_zero;
    }
}
// private function ------------------------------
// ctor/dtor -------------------------------------
RadicalHolder::RadicalHolder() :
m_radical(nullptr) {}
RadicalHolder::RadicalHolder(RadicalID id) :
m_radical(std::make_unique<Radical>(id)) {}


}
}
