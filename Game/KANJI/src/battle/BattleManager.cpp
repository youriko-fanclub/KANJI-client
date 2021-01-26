#include "BattleManager.hpp"
#include <Siv3D/Print.hpp>
#include "BattlePlayerManager.hpp"
#include "BattlePlayer.hpp"
#include "ParameterizedCharacter.hpp"
#include "PhysicalWorldManager.hpp"
#include "PhysicalMove.hpp"
#include "PhysicalCharacter.hpp"
#include "Log.hpp"
#include "Input.hpp"
#include "Audio.hpp"
#include "Stage.hpp"
#include "PhysicalCategory.hpp"
#include "PhysicalRadicalManager.hpp"

namespace kanji {
namespace battle {

/* ---------- BattleManager ---------- */

// static ----------------------------------------
// public function -------------------------------
bool BattleManager::hasGameSet() const {
    return m_has_gameset;
}

std::shared_ptr<BattleResultDesc> BattleManager::createResultDesc() const {
    auto* ranking = m_result_desc->ranking(); // 順位低い順
    if (m_player_mgr->alivePlayers().size() == 1) {
        for (const auto& winner : m_player_mgr->alivePlayers()) {
            ranking->push_back(winner.first);
        }
    }
    else if (m_player_mgr->alivePlayers().size() > 1) {
        s3d::Array<std::pair<BattlePlayer::Score, dx::di::PlayerId>> survivors;
        for (const auto& survivor : m_player_mgr->alivePlayers()) {
            survivors.emplace_back(survivor.second->scoreForRanked(), survivor.first);
        }
        std::sort(survivors.begin(), survivors.end(),
            [](const std::pair<BattlePlayer::Score, dx::di::PlayerId>& a, const std::pair<BattlePlayer::Score, dx::di::PlayerId>& b) {
            // TOdO: 勝敗決定 (要仕様確認)
            // 全滅→全滅したのが早いほど下位
            // 生存→残りHPの割合が多いほど上位
            // 同率→要実装 (ひとまずPlayerId降順になってるはず)
            return a.first.left_hp_rate < b.first.left_hp_rate;
        });
        for (const auto& survivor : survivors) {
            ranking->emplace_back(survivor.second);
        }
    }
    // log -----
    s3d::String log = U"";
    int rank = 1;
    for (auto it = ranking->rbegin();
        it != ranking->rend(); ++rank, ++it) {
        log += U"{}位.{}, "_fmt(rank, dx::denum::toString(*it));
    }
    dx::dbg::Log::info(U"Battle", log);
    // ----------
    return m_result_desc;
}

void BattleManager::initialize(const std::shared_ptr<BattleDesc>& desc) {
    desc->dump();
    
    m_timer = std::make_shared<BattleTimer>(desc->timeLimitSec());
    
    m_player_mgr = std::make_shared<BattlePlayerManager>(desc->playerDescs());

    dx::aud::Audio::masterSource()->addSource(U"Battle");
    dx::aud::Audio::source(U"Battle")->addClip(dx::aud::AudioType::SE, U"SE::Battle::Move::Normal"/* + s3d::ToString(move_id)*/);
    
    m_stage = std::make_shared<Stage>(desc->stageId());
    m_stage->initialize();
    m_world_mgr = std::make_shared<PhysicalWorldManager>();
    m_world_mgr->initializeStage(desc->stageId());
    m_world_mgr->initializeCharacters(m_player_mgr->players());

    m_move_mgr = std::make_shared<PhysicalMoveManager>();
    
    for (auto& player : m_player_mgr->players()) {
        player.second->initializePhysical(m_world_mgr->characters().at(player.first));
    }
    
    m_result_desc = std::make_shared<BattleResultDesc>();
}

void BattleManager::update() {
    for (auto& player : m_player_mgr->alivePlayers()) {
        const auto pid = player.first;
        if (dx::di::Input::get(pid).buttons().a().down()) {
            const auto& physical = player.second->physical();
            const MoveID move_id(0); // TOdO
            m_move_mgr->createMove(pid, physical, move_id);
            dx::aud::Audio::source(U"Battle")->playOneShot(U"SE::Battle::Move::Normal"/* + s3d::ToString(move_id)*/);
        }
        if (dx::di::Input::get(pid).buttons().x().down()) {
            player.second->changeActiveCharacter();
        }
        if (dx::di::Input::get(pid).buttons().y().down()) {
            player.second->trashRadical();
        }
    }
    m_world_mgr->update();
    m_move_mgr->update(Scene::DeltaTime());
    
    // 技とキャラの衝突判定
    for (const auto& move : m_move_mgr->moves()) {
        for (auto& player : m_player_mgr->players()) {
            if (player.second->isLost()
                || move->owner() == player.first) {  // 発動者本人には影響なし
                continue;
            }
            if (move->currentHitBox().intersects(player.second->physical()->rect())) {
                const auto& move_moment = move->currentMoment();
                player.second->attack(move_moment, move->isToRight());
                auto& move_owner = m_player_mgr->players().at(move->owner());
                // TOdO: オーバーキル分も与ダメとして計算しているが良いか
                move_owner->addGaveDamage(move_moment.damage);
                if (player.second->isLost()) {
                    lose(player.first);
                    move_owner->addKOCount();
                    if (m_player_mgr->alivePlayers().size() <= 1) {
                        m_has_gameset = true;
                    }
                }
            }
        }
    }
    
    // 部首とキャラの衝突判定
    for (auto& player_pair : m_player_mgr->players()) {
        auto& player = player_pair.second;
        if (player->isLost() || player->hasRadical()) {
            continue;
        }
        const auto& chara = player->activeCharacter();
        const auto& hitbox = player->physical()->rect();
        for (const auto& radical : m_world_mgr->radicalMgr()->radicals()) {
            // TOdO: 合体可能か調べる
            // if (chara->canConposeWith(radical))
            if (hitbox.intersects(radical->rect())) {
                player->setRadical(radical->id());
                radical->taken();
            }
        }
    }
        
    m_timer->update(Scene::DeltaTime());
    if (m_timer->hasTimeover()) {
        m_has_gameset = true;
    }
}

void BattleManager::pause() {
    m_timer->pause();
}

void BattleManager::resume() {
    m_timer->resume();
}

void BattleManager::holdUp() {
}

// private function ------------------------------
void BattleManager::lose(dx::di::PlayerId pid) {
    m_player_mgr->lose(pid);
    m_world_mgr->lose(pid);
    m_result_desc->ranking()->push_back(pid);
}

// ctor/dtor -------------------------------------
BattleManager::BattleManager() {}

}
}
