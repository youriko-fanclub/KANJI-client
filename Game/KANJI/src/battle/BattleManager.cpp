#include "BattleManager.hpp"
#include <Siv3D/Print.hpp>
#include "BattlePlayerManager.hpp"
#include "BattlePlayer.hpp"
#include "Log.hpp"

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
}

void BattleManager::update() {
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
