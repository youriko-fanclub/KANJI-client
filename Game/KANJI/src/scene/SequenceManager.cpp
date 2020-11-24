#include "SequenceManager.hpp"

#include "Scenes.hpp"
#include "HotReloadManager.hpp"
#include "SystemParams.hpp"

namespace kanji {
namespace seq {


/* ---------- SequenceManager ---------- */

// static ----------------------------------------
// public function -------------------------------
void SequenceManager::initialize() {
    // シーンと遷移時の色を設定
    m_manager
    //  .add<SplashScene>(State::Splash)
        .add<TitleScene>(State::Title)
        .add<CharacterSelectionScene>(State::CharacterSelection)
        .add<StageSelectionScene>(State::StageSelection)
        .add<BattleScene>(State::Battle)
        .add<ResultScene>(State::Result)
        .add<dx::di::InputDemoScene>(State::InputDemo)
        .setFadeColor(s3d::ColorF(1.0));
    
    const auto& params = dx::cmp::HotReloadManager::createParams<dx::app::SystemParams>(false);
    const auto& initial_scene = dx::denum::fromString<State>(params->initial_scene);
    m_manager.init(initial_scene ? *initial_scene : State::Title);
}

bool SequenceManager::update() {
    return m_manager.updateScene();
}

void SequenceManager::draw() const {
    m_manager.drawScene();
}

// private function ------------------------------
// ctor/dtor -------------------------------------


}
}
