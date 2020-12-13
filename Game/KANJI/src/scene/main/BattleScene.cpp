#include "BattleScene.hpp"
#include "BattleManager.hpp"
#include "BattleUIManager.hpp"
#include "ParameterizedCharacter.hpp"

#include <Siv3D/TOMLReader.hpp>
#include "Input.hpp"
#include "Misc.hpp"
#include "HotReloadManager.hpp"


namespace {

std::shared_ptr<kanji::battle::BattleDesc> createBattleDescForDebug(const std::shared_ptr<kanji::battle::BattleDesc>& battle_desc) {
    {
        auto player_desc = std::make_shared<kanji::battle::BattlePlayerDesc>();
        player_desc->characters().push_back(
            std::make_shared<kanji::chara::ParameterizedCharacter>(0, U"山")
        );
        player_desc->characters().push_back(
            std::make_shared<kanji::chara::ParameterizedCharacter>(1, U"斬")
        );
        player_desc->characters().push_back(
            std::make_shared<kanji::chara::ParameterizedCharacter>(2, U"王")
        );
        battle_desc->setPlayerDesc(dx::di::PlayerId::_1P, player_desc);
    }
    {
        auto player_desc = std::make_shared<kanji::battle::BattlePlayerDesc>();
        player_desc->characters().push_back(
            std::make_shared<kanji::chara::ParameterizedCharacter>(3, U"包")
        );
        player_desc->characters().push_back(
            std::make_shared<kanji::chara::ParameterizedCharacter>(4, U"分")
        );
        player_desc->characters().push_back(
            std::make_shared<kanji::chara::ParameterizedCharacter>(5, U"鬼")
        );
        battle_desc->setPlayerDesc(dx::di::PlayerId::_2P, player_desc);
    }
    {
        auto player_desc = std::make_shared<kanji::battle::BattlePlayerDesc>();
        player_desc->characters().push_back(
            std::make_shared<kanji::chara::ParameterizedCharacter>(6, U"工")
        );
        player_desc->characters().push_back(
            std::make_shared<kanji::chara::ParameterizedCharacter>(7, U"詛")
        );
        player_desc->characters().push_back(
            std::make_shared<kanji::chara::ParameterizedCharacter>(8, U"寺")
        );
        battle_desc->setPlayerDesc(dx::di::PlayerId::_3P, player_desc);
    }
    {
        auto player_desc = std::make_shared<kanji::battle::BattlePlayerDesc>();
        player_desc->characters().push_back(
            std::make_shared<kanji::chara::ParameterizedCharacter>(9, U"白")
        );
        player_desc->characters().push_back(
            std::make_shared<kanji::chara::ParameterizedCharacter>(10, U"生")
        );
        player_desc->characters().push_back(
            std::make_shared<kanji::chara::ParameterizedCharacter>(11, U"田")
        );
        battle_desc->setPlayerDesc(dx::di::PlayerId::_4P, player_desc);
    }
    static auto param = dx::cmp::HotReloadManager::createParamsWithLoad(U"Battle");
    battle_desc->setTimeLimitSec(param->get<int>(U"battle.debug_desc.timelimit"));
    battle_desc->setStageId(param->get<int>(U"battle.debug_desc.stage_id"));
    return battle_desc;
}

}

namespace kanji {
namespace seq {

/* ---------- BattleScene ---------- */

// static ----------------------------------------
// public function -------------------------------
void BattleScene::initialize() {
    m_mgr = std::make_shared<battle::BattleManager>();
    if (!getData().readyToBattle()) { // 開発時にBattleSceneを直接開いたとき用
        getData().setBattleDesc(createBattleDescForDebug(getData().battleDesc()));
    }
    m_mgr->initialize(getData().battleDesc());
    m_ui = std::make_shared<ui::BattleUIManager>(m_mgr.get());
}
void BattleScene::update() {
    // TOdO: オブザーバにした方がよさそう
    // ほんとは試合終了後遷移前に演出入れる
    if (m_mgr->hasGameSet()) {
        getData().setBattleResultDesc(m_mgr->createResultDesc());
        changeScene(State::Result);
        return;
    }
    m_mgr->update();
    updateLegacy();
    m_ui->update();
}
void BattleScene::updateLegacy() {}
void BattleScene::draw() const {
    m_ui->draw();
    drawLegacy();
}
void BattleScene::drawLegacy() const {}

// private function ------------------------------
// ctor/dtor -------------------------------------
BattleScene::BattleScene(const InitData& init) : IScene(init) {
    initialize();
}

}
}
