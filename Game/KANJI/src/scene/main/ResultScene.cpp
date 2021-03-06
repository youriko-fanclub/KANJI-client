#include "ResultScene.hpp"
#include "BattleDesc.hpp"
#include "Audio.hpp"


namespace kanji {
namespace seq {

/* ---------- ResultScene ---------- */

// static ----------------------------------------
// public function -------------------------------
void ResultScene::update() {
    m_chara_select.update();
    m_title.update();
}

void ResultScene::draw() const {
    const auto& ranking = m_battle_result_desc->ranking();
    int rank = 1;
    for (auto it = ranking->rbegin();
        it != ranking->rend(); ++rank, ++it) {
        s3d::FontAsset(U"Title")(U"{}位.{}"_fmt(rank, dx::denum::toString(*it))).draw(100, 100 * rank, dx::di::Id::ToColorDark(*it));
    }

    m_chara_select.draw();
    m_title.draw();
}

// private function ------------------------------
// ctor/dtor -------------------------------------
ResultScene::ResultScene(const InitData& init) :
KanjiScene(init, U"Result"),
m_chara_select(
    Rect(Arg::center = Scene::Center().movedBy(65, 170), 300, 60),
    DrawableText(FontAsset(U"Menu"), U"キャラ選(未)"),
    Transition(0.4s, 0.2s)),
m_title(
    Rect(Arg::center = Scene::Center().movedBy(65, 250), 300, 60),
    DrawableText(FontAsset(U"Menu"), U"タイトルに戻る"),
    Transition(0.4s, 0.2s)),
m_battle_result_desc(getData().battleResultDesc()) {
    m_chara_select.setCallback([this](){ changeScene(State::CharacterSelection); });
    m_title.setCallback([this](){ changeScene(State::Title); });
    
    auto* result_audio = dx::aud::Audio::masterSource()->addSource(U"Result");
    result_audio->addClip(dx::aud::AudioType::BGM, U"BGM::Result", true);
    setOnDestructCallback([](State next){
        dx::aud::Audio::masterSource()->removeSource(U"Result");
    });
}

ResultScene::~ResultScene() {
    getData().clearBattleData();
}


}
}
