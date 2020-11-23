#include "PhysicalWorldManager.hpp"
#include "HotReloadManager.hpp"
#include "BattlePlayer.hpp"
#include "PhysicalCharacter.hpp"
#include "PhysicalStage.hpp"

namespace kanji {
namespace battle {


/* ---------- PhysicalWorldManager ---------- */

// static ----------------------------------------
// public function -------------------------------
void PhysicalWorldManager::initializeCharacters(const std::unordered_map<dx::di::PlayerId, std::shared_ptr<BattlePlayer>>& players) {
    for (const auto& player : players) {
        m_characters.insert(std::make_pair(player.first,
            std::make_shared<PhysicalCharacter>(
                &m_world,
                player.first,
                true,
                player.second->activeCharacter(),
                m_param)
            ));
    }
}

void PhysicalWorldManager::update() {
    // 物理演算の精度
    static constexpr int32 velocityIterations = 12;
    static constexpr int32 positionIterations = 4;
    m_world.update(Scene::DeltaTime(), velocityIterations, positionIterations);
    for (auto& chara : m_characters) {
        chara.second->update();
    }
    // クリックした場所にボールを作成
    // m_bodies << m_world.createCircle(Cursor::PosF(), 0.5);
    // (y > 10) まで落下した P2Body は削除
    m_bodies.remove_if([](const P2Body& body) { return body.getPos().y > 10; });
}

// private function ------------------------------
// ctor/dtor -------------------------------------
PhysicalWorldManager::PhysicalWorldManager() :
m_param(dx::cmp::HotReloadManager::createParams<param::CharaPhysics>()),
m_world(9.8) {
    m_stage = std::make_shared<PhysicalStage>(&m_world, m_param);
}
    
}
}
