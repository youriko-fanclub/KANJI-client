#include "StageSelectionScene.hpp"
#include "BattleDesc.hpp"
#include "Audio.hpp"
#include "IDs.hpp"


namespace kanji {
namespace seq {

/* ---------- StageSelectionScene ---------- */

// static ----------------------------------------
// public function -------------------------------
void StageSelectionScene::update() {
    m_battle_start.update();
    m_back.update();
}

void StageSelectionScene::draw() const {
    s3d::FontAsset(U"Title")(U"StageSelection").draw(0, 0);
    m_battle_start.draw();
    m_back.draw();
}

// private function ------------------------------
void StageSelectionScene::selectStage() const {
    getData().battleDesc()->setStageId(StageID(300000));
}

// ctor/dtor -------------------------------------
StageSelectionScene::StageSelectionScene(const InitData& init) :
KanjiScene(init, U"StageSelection"),
m_battle_start(
    Rect(Arg::center = Scene::Center().movedBy(65, 170), 300, 60),
    DrawableText(FontAsset(U"Menu"), U"試合開始"),
    Transition(0.4s, 0.2s)),
m_back(
    Rect(Arg::center = Scene::Center().movedBy(65, 250), 300, 60),
    DrawableText(FontAsset(U"Menu"), U"戻る"),
    Transition(0.4s, 0.2s)) {
    
    m_battle_start.setCallback([this](){
        selectStage();
        changeScene(State::Battle);
    });
    m_back.setCallback([this](){ changeScene(State::CharacterSelection); });
    
    setOnDestructCallback([this](State next){
        switch (next) {
        case State::Battle: {
            dx::aud::Audio::masterSource()->removeSource(U"Menu");
        } break;
        default: break;
        }
    });
}


}
}
