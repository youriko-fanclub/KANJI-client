#include "SequenceManager.hpp"

#include "Scenes.hpp"

namespace kanji {
namespace seq {


/* ---------- SequenceManager ---------- */

// static ----------------------------------------
// public function -------------------------------
void SequenceManager::initialize() {
  // シーンと遷移時の色を設定
  //m_manager
  //  .add<SplashScene>(State::Splash)
  //  .add<TitleScene>(State::Title)
  //  .setFadeColor(s3d::ColorF(1.0));
  m_manager
    .add<TitleScene>(State::Title)
    .add<GameScene>(State::Game)
    .setFadeColor(s3d::ColorF(1.0));
    
  // （ゲームシーンから開始する場合はコメントを外す）
  //manager.init(State::Game);
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
