#include "PhysicalWorldManager.hpp"
#include "BattlePlayer.hpp"
#include "PhysicalCharacter.hpp"
#include "PhysicalStage.hpp"
#include "PhysicalRadicalManager.hpp"
#include "PhysicalWorld.hpp"
#include "PhysicalCategory.hpp"

namespace kanji {
namespace battle {


/* ---------- PhysicalWorldManager ---------- */

// static ----------------------------------------
// public function -------------------------------
void PhysicalWorldManager::initializeCharacters(const s3d::HashTable<dx::di::PlayerId, std::shared_ptr<BattlePlayer>>& players) {
    auto initial_positions = m_stage->initialCharaPositions(static_cast<int>(players.size()));
    std::vector<int> random_indices(players.size());
    { // 初期位置をランダムに
        std::iota(random_indices.begin(), random_indices.end(), 0);
        std::random_device seed;
        std::mt19937 engine(seed());
        std::shuffle(random_indices.begin(), random_indices.end(), engine);
    }
    for (int index = 0; const auto& player : players) {
        m_characters.emplace(player.first,
            std::make_shared<PhysicalCharacter>(
                m_world,
                player.first,
                initial_positions.at(random_indices.at(index)),
                true,
                player.second,
                m_toml)
            );
        ++index;
    }
}

void PhysicalWorldManager::initializeStage(StageID id) {
    m_stage = std::make_shared<PhysicalStage>(m_world, id, m_toml);
}
    
void PhysicalWorldManager::update() {
    const dx::Time dt = Scene::DeltaTime();
    // 物理演算の精度
    static constexpr s3d::int32 velocity_iterations = 12;
    static constexpr s3d::int32 position_iterations = 4;
    m_world->update(dt, velocity_iterations, position_iterations);
    m_radical_mgr->update(dt);
    const dx::Time temp_interval = 10.0;
    static dx::Time temp_timer = 0.0;
    static RadicalID temp_radical_id(100000);
    if ((temp_timer += dt) > temp_interval) {
        m_radical_mgr->createRadical(temp_radical_id);
        ++temp_radical_id;
        if (temp_radical_id.toInt() == 100020) {
            temp_radical_id = RadicalID(100000);
        }
        temp_timer -= temp_interval;
    }
    for (auto& chara : m_characters) {
        chara.second->update();
    }
}

void PhysicalWorldManager::lose(dx::di::PlayerId pid) {
    m_characters.erase(pid);
}

// private function ------------------------------
// ctor/dtor -------------------------------------
PhysicalWorldManager::PhysicalWorldManager() :
m_toml(U"Physics"),
m_world(std::make_shared<dx::phys::PhysicalWorld>(
    PhysicalCategory::categories(),
    PhysicalCategory::collisionMap(),
    9.8)),
m_radical_mgr(std::make_shared<PhysicalRadicalManager>(m_world)) {}
    
}
}
