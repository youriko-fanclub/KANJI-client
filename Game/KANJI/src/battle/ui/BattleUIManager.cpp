#include "BattleUIManager.hpp"
#include "BattleManager.hpp"
#include "BattlePlayerManager.hpp"
#include "BattlePlayer.hpp"
#include "PhysicalWorldManager.hpp"
#include "PhysicalMove.hpp"
#include "HolderUI.hpp"

namespace kanji {
namespace ui {


/* ---------- MoveUIManager ---------- */

// static ----------------------------------------
// public function -------------------------------
void MoveUIManager::update() {}
// protected function ------------------------------
void MoveUIManager::drawImpl() const {
    m_move_mgr->drawLegacy();
}
// private function ------------------------------
// ctor/dtor -------------------------------------
MoveUIManager::MoveUIManager(const battle::PhysicalMoveManager* move_mgr) :
m_move_mgr(move_mgr) {}



/* ---------- PhysicalWorldUIManager ---------- */

// static ----------------------------------------
// public function -------------------------------
void PhysicalWorldUIManager::update() {}
// protected function ------------------------------
void PhysicalWorldUIManager::drawImpl() const {
    m_world_mgr->drawLegacy();
}
// private function ------------------------------
// ctor/dtor -------------------------------------
PhysicalWorldUIManager::PhysicalWorldUIManager(const battle::PhysicalWorldManager* world_mgr) :
m_world_mgr(world_mgr) {}



/* ---------- BattleUIManager ---------- */

// static ----------------------------------------
// public function -------------------------------
void BattleUIManager::update() {
    m_camera.update();
    for (auto& holder : m_holders) {
        holder.second->update();
    }
}

void BattleUIManager::drawImpl() const {
    for (const auto& holder : m_holders) {
        holder.second->draw();
    }
    {
        const auto t = m_camera.createTransformer();
        m_world->draw();
        m_moves->draw();
    }
    m_camera.draw();
}

// private function ------------------------------
// ctor/dtor -------------------------------------
BattleUIManager::BattleUIManager(const battle::IBattleManager* battle_mgr) :
m_camera(Vec2(0, -8), 20.0, s3d::Camera2DParameters::MouseOnly()),
m_battle_manager(battle_mgr),
m_world(std::make_shared<PhysicalWorldUIManager>(battle_mgr->worldMgr().get())),
m_moves(std::make_shared<MoveUIManager>(battle_mgr->moveMgr().get())) {
    const auto& players = m_battle_manager->playerMgr()->players();
    const int player_num = static_cast<int>(players.size());
    for (int i = 0; const auto& player : players) {
        m_holders.insert(std::make_pair(player.first,
            std::make_shared<HolderUI>(i, player_num, player.second)));
        ++i;
    }
}


}
}
