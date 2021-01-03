#include "BattleScene.hpp"
#include "BattleManager.hpp"
#include "BattleUIManager.hpp"
#include "ParameterizedCharacter.hpp"

#include <Siv3D/TOMLReader.hpp>
#include "Input.hpp"
#include "Misc.hpp"
#include "HotReloadManager.hpp"
#include "IDs.hpp"
#include "Audio.hpp"
#include "MasterKanjiParamRepository.hpp"
#include "TomlAsset.hpp"
#include "Path.hpp"


namespace {

using KanjiID = kanji::KanjiID;
void createAndPushCharacter(
    const std::shared_ptr<kanji::battle::BattlePlayerDesc>& desc,
    const std::unique_ptr<kanji::md::MasterKanjiParamRepository>& repo,
    KanjiID id) {
    desc->characters().push_back(
        kanji::chara::ParameterizedCharacter::createShared(repo->at(KanjiID(id)))
    );
}
std::shared_ptr<kanji::battle::BattleDesc> createBattleDescForDebug(const std::shared_ptr<kanji::battle::BattleDesc>& battle_desc) {
    const auto& repo = kanji::md::MasterKanjiParamRepository::instance();
    {
        auto player_desc = std::make_shared<kanji::battle::BattlePlayerDesc>();
        createAndPushCharacter(player_desc, repo, KanjiID(0));
        createAndPushCharacter(player_desc, repo, KanjiID(1));
        createAndPushCharacter(player_desc, repo, KanjiID(2));
        battle_desc->setPlayerDesc(dx::di::PlayerId::_1P, player_desc);
    }
    {
        auto player_desc = std::make_shared<kanji::battle::BattlePlayerDesc>();
        createAndPushCharacter(player_desc, repo, KanjiID(3));
        createAndPushCharacter(player_desc, repo, KanjiID(4));
        createAndPushCharacter(player_desc, repo, KanjiID(5));
        battle_desc->setPlayerDesc(dx::di::PlayerId::_2P, player_desc);
    }
    {
        auto player_desc = std::make_shared<kanji::battle::BattlePlayerDesc>();
        createAndPushCharacter(player_desc, repo, KanjiID(6));
        createAndPushCharacter(player_desc, repo, KanjiID(7));
        createAndPushCharacter(player_desc, repo, KanjiID(8));
        battle_desc->setPlayerDesc(dx::di::PlayerId::_3P, player_desc);
    }
    {
        auto player_desc = std::make_shared<kanji::battle::BattlePlayerDesc>();
        createAndPushCharacter(player_desc, repo, KanjiID(9));
        createAndPushCharacter(player_desc, repo, KanjiID(10));
        createAndPushCharacter(player_desc, repo, KanjiID(11));
        battle_desc->setPlayerDesc(dx::di::PlayerId::_4P, player_desc);
    }
    static dx::cmp::TomlAsset toml(U"Battle");
    dx::cmp::TomlKey key(U"battle.debug_desc");
    battle_desc->setTimeLimitSec(toml[key + U"timelimit"].get<int>());
    battle_desc->setStageId(toml[key + U"stage_id"].get<int>());
    // battle_desc->setTimeLimitSec(param[U"battle"][U"debug_desc"][U"timelimit"].get<int>());
    // battle_desc->setStageId(param[U"battle"][U"debug_desc"][U"stage_id"].get<int>());
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
    
    auto* battle_audio = dx::aud::Audio::masterSource()->addSource(U"Battle");
    battle_audio->addClip(dx::aud::AudioType::BGM, U"BGM::Battle02", true);
    setOnDestructCallback([](State next){
        dx::aud::Audio::masterSource()->removeSource(U"Battle");
    });
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
    m_ui->update();
}
void BattleScene::draw() const {
    m_ui->draw();
}

// private function ------------------------------
// ctor/dtor -------------------------------------
BattleScene::BattleScene(const InitData& init) : KanjiScene(init, U"Battle") {
    initialize();
}

}
}
