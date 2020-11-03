#include "BattleManager.hpp"

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
