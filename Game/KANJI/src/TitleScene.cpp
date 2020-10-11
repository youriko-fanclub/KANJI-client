#include "TitleScene.hpp"

namespace kanji {
namespace seq {


TitleScene::TitleScene(const InitData& init) :
IScene(init),
m_start(
  Rect(Arg::center = Scene::Center().movedBy(0, 0), 300, 60),
  DrawableText(FontAsset(U"Menu"), U"はじめる"),
  Transition(0.4s, 0.2s)),
m_exit(
  Rect(Arg::center = Scene::Center().movedBy(0, 100), 300, 60),
  DrawableText(FontAsset(U"Menu"), U"おわる"),
  Transition(0.4s, 0.2s)) {
  {
    const String titleText = U"漢字発見! モジバトル";
    const Vec2 center(Scene::Center().x, 120);
    m_title.first = FontAsset(U"Title")(titleText);
    m_title.second = FontAsset(U"Title")(titleText);
  }
  
  m_start.setCallback([this](){ changeScene(State::Game); });
  m_exit.setCallback([](){ System::Exit(); });
}

void TitleScene::update() {
  m_start.update();
  m_exit.update();
}

void TitleScene::draw() const {
  const Vec2 center(Scene::Center().x, 120);
  m_title.first.drawAt(center.movedBy(4, 6), ColorF(0.0, 0.5));
  m_title.second.drawAt(center);
  
  m_start.draw();
  m_exit.draw();
  
  Rect(0, 500, Scene::Width(), Scene::Height() - 500)
  .draw(Arg::top = ColorF(0.0, 0.0), Arg::bottom = ColorF(0.0, 0.5));
  
  const int32 highScore = getData().highScore;
  FontAsset(U"Score")(U"High score: {}"_fmt(highScore)).drawAt(Vec2(620, 550));
}


}
}
