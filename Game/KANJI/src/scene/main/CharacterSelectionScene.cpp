#include "CharacterSelectionScene.hpp"
#include "Audio.hpp"

namespace kanji {
namespace seq {


/* ---------- TitleScene ---------- */

// static ----------------------------------------
// public function -------------------------------
void CharacterSelectionScene::update() {
    m_next.update();
    m_back.update();
}

void CharacterSelectionScene::draw() const {
    s3d::FontAsset(U"Title")(U"CharacterSelection").draw(0, 0);
    m_next.draw();
    m_back.draw();
}

// private function ------------------------------
// ctor/dtor -------------------------------------
CharacterSelectionScene::CharacterSelectionScene(const InitData& init) :
KanjiScene(init, U"CharacterSelection"),
m_next(
    Rect(Arg::center = Scene::Center().movedBy(0, 170), 300, 60),
    DrawableText(FontAsset(U"Menu"), U"次へ"),
    Transition(0.4s, 0.2s)),
m_back(
    Rect(Arg::center = Scene::Center().movedBy(0, 250), 300, 60),
    DrawableText(FontAsset(U"Menu"), U"戻る"),
    Transition(0.4s, 0.2s)) {
    m_next.setCallback([this](){ changeScene(State::StageSelection); });
    m_back.setCallback([this](){ changeScene(State::Title); });
    
    auto* menu_audio = dx::aud::Audio::masterSource()->addSource(U"Menu");
    menu_audio->addClip(dx::aud::AudioType::BGM, U"BGM::Menu", true);
    setOnDestructCallback([this](State next){
        switch (next) {
        case State::Title: {
            dx::aud::Audio::masterSource()->removeSource(U"Menu");
        } break;
        default: break;
        }
    });
}


}
}
