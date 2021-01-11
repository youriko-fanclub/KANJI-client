#include "Radical.hpp"
#include "MasterRadicalParamRepository.hpp"

namespace kanji {
namespace chara {

/* ---------- Radical ---------- */

// static ----------------------------------------
// public function -------------------------------
const s3d::String& Radical::chara() const {
    return m_md->character();
}
// private function ------------------------------
// ctor/dtor -------------------------------------
Radical::Radical(RadicalID id) :
m_md(md::MasterRadicalParamRepository::instance()->at(id)),
m_ability() {}

}
}
