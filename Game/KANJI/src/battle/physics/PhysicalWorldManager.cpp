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
    auto initial_positions = m_stage->initialCharaPositions(static_cast<int>(players.size()));
    std::vector<int> random_indices(players.size());
    { // 初期位置をランダムに
        std::iota(random_indices.begin(), random_indices.end(), 0);
        std::random_device seed;
        std::mt19937 engine(seed());
        std::shuffle(random_indices.begin(), random_indices.end(), engine);
    }
    for (int index = 0; const auto& player : players) {
        m_characters.insert(std::make_pair(player.first,
            std::make_shared<PhysicalCharacter>(
                &m_world,
                player.first,
                initial_positions.at(random_indices.at(index)),
                true,
                player.second,
                m_param)
            ));
        ++index;
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

void PhysicalWorldManager::lose(dx::di::PlayerId pid) {
    m_characters.erase(pid);
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
