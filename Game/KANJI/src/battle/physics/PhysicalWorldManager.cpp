#include "PhysicalWorldManager.hpp"
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
                m_toml)
            ));
        ++index;
    }
}

void PhysicalWorldManager::update() {
    // 物理演算の精度
    static constexpr int32 velocity_iterations = 12;
    static constexpr int32 position_iterations = 4;
    m_world.update(Scene::DeltaTime(), velocity_iterations, position_iterations);
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
m_world(9.8) {
    m_stage = std::make_shared<PhysicalStage>(&m_world, StageID(300000), m_toml);
}
    
}
}
