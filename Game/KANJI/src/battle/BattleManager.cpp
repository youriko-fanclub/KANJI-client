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

namespace kanji {
namespace battle {

bool BattleManager::hasGameSet() const {
    return m_timer->hasTimeover();
}

std::shared_ptr<BattleResultDesc> BattleManager::createResultDesc() const {
    auto desc = std::make_shared<BattleResultDesc>();
    /* program here */
    return desc;
}

void BattleManager::initialize(const std::shared_ptr<BattleDesc>& desc) {
    m_timer = std::make_shared<BattleTimer>(desc->timeLimitSec() * 60);
    s3d::Print
        << U"// Battle Start --------------------";
    s3d::Print
        << U"// TEST ********************";
    dx::dbg::Log::info(U"Category01",U"msg{}-{}-{}",U"1",U"2.5",U"hoge");
    dx::dbg::Log::debug(U"Hoge.Fuga",U"msg{}-{}-{}",U"1",U"2.5",U"hoge");
    dx::dbg::Log::error(U"You.Riko",U"msg{}-{}-{}",U"1",U"2.5",U"hoge");
    s3d::Print
        << U"// TEST ********************";
    desc->dump();
    m_player_mgr = std::make_shared<BattlePlayerManager>(desc->playerDescs());
    m_player_mgr->players().at(dx::di::PlayerId::_1P)->setRadical(U"風");
    m_player_mgr->players().at(dx::di::PlayerId::_2P)->setRadical(U"土");
    m_player_mgr->players().at(dx::di::PlayerId::_3P)->setRadical(U"雨");
    m_player_mgr->players().at(dx::di::PlayerId::_4P)->setRadical(U"獣");
    m_world_mgr = std::make_shared<PhysicalWorldManager>();
    m_world_mgr->initializeCharacters(m_player_mgr->players());
    m_move_mgr = std::make_shared<PhysicalMoveManager>();
    for (auto& player : m_player_mgr->players()) {
        player.second->initializePhysical(m_world_mgr->characters().at(player.first));
    }
}

void BattleManager::update() {
    // debug  -----------------
    for (auto& player : m_player_mgr->players()) {
        const auto pid = player.first;
        if (dx::di::Input::get(pid).buttons().a().down()) {
            const auto& physical = player.second->physical();
            m_move_mgr->createMove(pid, physical, 0);
        }
        if (dx::di::Input::get(pid).buttons().b().down()) {
            m_player_mgr->players().at(pid)->characters().at(1)->damage(5);
        }
        if (dx::di::Input::get(pid).buttons().x().down()) {
            m_player_mgr->players().at(pid)->characters().at(2)->damage(5);
        }
    }
    // debug  -----------------
    m_world_mgr->update();
    m_move_mgr->update(Scene::DeltaTime());
    
    { // 技とキャラの衝突判定
        for (const auto& move : m_move_mgr->moves()) {
            for (auto& player : m_player_mgr->players()) {
                if (move->owner() == player.first) { continue; } // 発動者本人には影響なし
                if (move->currentHitBox().intersects(player.second->physical()->rect())) {
                    player.second->damage(move->currentMoment());
                }
            }
        }
    }
    m_timer->update();
}

void BattleManager::pause() {
    m_timer->pause();
}

void BattleManager::resume() {
    m_timer->resume();
}

void BattleManager::holdUp() {
}

BattleManager::BattleManager() {}

}
}
