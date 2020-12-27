#include "KanjiScene.hpp"
#include "Audio.hpp"

namespace kanji {
namespace seq {


/* ---------- TransitionInfo ---------- */
void KanjiScene::TransitionInfo::onFadeOutBegin(State next, const Duration& transition_time, bool is_cross_fade) {
    next_state = next;
    if (on_fadeout_began) {
        (*on_fadeout_began)(next, transition_time, is_cross_fade);
    }
}
void KanjiScene::TransitionInfo::onDestruct() {
    if (on_destruct) {
        (*on_destruct)(next_state);
    }
}

/* ---------- KanjiScene ---------- */

// static ----------------------------------------
// public function -------------------------------
// protected function -------------------------------
void KanjiScene::setOnDestructCallback(const std::function<void(State)>& callback) {
    m_transition_info.on_destruct = std::make_unique<std::function<void(State)>>(callback);
}
bool KanjiScene::changeScene(const State_t& state, const Duration& transition_time, bool is_cross_fade) {
    m_transition_info.onFadeOutBegin(state, transition_time, is_cross_fade);
    return SceneWithData::changeScene(state, transition_time, is_cross_fade);
}

// private function ------------------------------
// ctor/dtor -------------------------------------
KanjiScene::KanjiScene(const InitData& init, const s3d::String& name) :
IScene(init),
m_name(name) {}

KanjiScene::~KanjiScene() {
    dx::aud::Audio::masterSource()->removeSource(U"Scene::" + m_name);
    m_transition_info.onDestruct();
}

    
}
}
