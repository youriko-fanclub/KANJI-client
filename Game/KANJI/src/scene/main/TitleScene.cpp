#include "TitleScene.hpp"

namespace kanji {
namespace seq {


/* ---------- TitleScene ---------- */

// static ----------------------------------------
// public function -------------------------------
void TitleScene::update() {
    m_start.update();
    m_exit.update();
    m_battle4debug.update();
}

void TitleScene::draw() const {
    Scene::Rect()(TextureAsset(U"Title::Bg")).draw();
    TextureAsset(U"Title::Logo").drawAt(Scene::Center().movedBy(55, -90));
    
    const Vec2 center(Scene::Center().x, 120);
    m_title.first.drawAt(center.movedBy(4, 6), ColorF(0.0, 0.5));
    m_title.second.drawAt(center);
    
    m_start.draw();
    m_exit.draw();
    m_battle4debug.draw();
    
    Rect(0, 500, Scene::Width(), Scene::Height() - 500)
        .draw(Arg::top = ColorF(0.0, 0.0), Arg::bottom = ColorF(0.0, 0.5));
}

// private function ------------------------------
// ctor/dtor -------------------------------------
TitleScene::TitleScene(const InitData& init) :
IScene(init),
m_start(
    Rect(Arg::center = Scene::Center().movedBy(-165, 170), 300, 60),
    DrawableText(FontAsset(U"Menu"), U"はじめる"),
    Transition(0.4s, 0.2s)),
m_exit(
    Rect(Arg::center = Scene::Center().movedBy(-165, 250), 300, 60),
    DrawableText(FontAsset(U"Menu"), U"おわる"),
    Transition(0.4s, 0.2s)),
m_battle4debug(
    Rect(Arg::center = Scene::Center().movedBy(165, 170), 300, 60),
    DrawableText(FontAsset(U"Menu"), U"試合開始debug"),
    Transition(0.4s, 0.2s)) {
    
    m_start.setCallback([this](){ changeScene(State::CharacterSelection); });
    m_battle4debug.setCallback([this](){ changeScene(State::Battle); });
    m_exit.setCallback([](){ System::Exit(); });
    getData().clearBattleData();
}


}
}
