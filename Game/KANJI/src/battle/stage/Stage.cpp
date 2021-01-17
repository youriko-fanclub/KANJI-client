#include "Stage.hpp"
#include "MasterStageRepository.hpp"
#include "Audio.hpp"

namespace kanji {
namespace battle {

/* ---------- Stage ---------- */

// static ----------------------------------------
// public function -------------------------------
void Stage::initialize() {
    dx::aud::Audio::source(U"Battle")->addClip(dx::aud::AudioType::BGM, U"BGM::" + m_md->bgm(), true);
}

// private function ------------------------------
// ctor/dtor -------------------------------------
Stage::Stage(StageID id) :
m_md(md::MasterStageRepository::instance()->at(id)) {}


}
}
