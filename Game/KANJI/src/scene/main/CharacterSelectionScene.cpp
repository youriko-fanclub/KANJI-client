#include "CharacterSelectionScene.hpp"

namespace kanji {
namespace seq {


/* ---------- TitleScene ---------- */

// static ----------------------------------------
// public function -------------------------------
void CharacterSelectionScene::update() {
    m_next.update();
    
    m_cursorManager.update();
}

void CharacterSelectionScene::draw() const {
    m_next.draw();
  
    Rect(0, 500, Scene::Width(), Scene::Height() - 500)
      .draw(Arg::top = ColorF(0.0, 0.0), Arg::bottom = ColorF(0.0, 0.5));
    
    m_cursorManager.draw();
}

// private function ------------------------------
// ctor/dtor -------------------------------------
CharacterSelectionScene::CharacterSelectionScene(const InitData& init) :
IScene(init),
m_next(
    Rect(Arg::center = Scene::Center().movedBy(0, 170), 300, 60),
    DrawableText(FontAsset(U"Menu"), U"次へ"),
    Transition(0.4s, 0.2s)),
m_cursorManager() {
    m_next.setCallback([this](){ changeScene(State::Game); });
}


}
}
