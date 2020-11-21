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
    m_camera.update();
    { // 2D カメラの設定から Transformer2D を作成・適用
        const auto t = m_camera.createTransformer();
        if (MouseL.down()) {
            // クリックした場所にボールを作成
            m_bodies << m_world.createCircle(Cursor::PosF(), 0.5);
        }
    }
    // (y > 10) まで落下した P2Body は削除
    m_bodies.remove_if([](const P2Body& body) { return body.getPos().y > 10; });
}

void PhysicalWorldManager::drawLegacy() const {
    {
        // 2D カメラの設定から Transformer2D を作成・適用
        const auto t = m_camera.createTransformer();
        m_stage->drawLegacy();
        for (const auto& chara : m_characters) {
            chara.second->drawLegacy();
        }
        
        // 物体を描画
        for (const auto& body : m_bodies) {
            body.draw(HSV(body.id() * 10, 0.7, 0.9));
        }
    }
    m_camera.draw();
}
// private function ------------------------------
// ctor/dtor -------------------------------------
PhysicalWorldManager::PhysicalWorldManager() :
m_param(dx::cmp::HotReloadManager::createParams<param::CharaPhysics>()),
m_camera(Vec2(0, -8), 20.0, s3d::Camera2DParameters::MouseOnly()),
m_world(9.8) {
    m_stage = std::make_shared<PhysicalStage>(&m_world, m_param);
}
    
}
}
