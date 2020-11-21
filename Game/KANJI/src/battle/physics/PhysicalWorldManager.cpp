#include "PhysicalWorldManager.hpp"
#include "HotReloadManager.hpp"
#include "Input.hpp"
#include "Misc.hpp"
#include "BattlePlayer.hpp"
#include "ParameterizedCharacter.hpp"

namespace kanji {
namespace battle {

/* ---------- PhysicalCharacter ---------- */

// static ----------------------------------------
// public function -------------------------------
void PhysicalCharacter::update() {
    const auto& input = dx::di::Input::get(m_pid);
    s3d::Vec2 velocity(
        m_param->force_horizontal * input.arrowL().x,
        input.dpad().up().down() || input.buttons().b().down() ? -m_param->force_jump : 0.0);
    // m_body.applyForce(force);
    const auto& v = m_body.getVelocity();
    if (dx::misc::approximatelyZero(velocity)) {
        velocity.x = v.x * m_param->air_resistance;
        velocity.y = v.y;
    }
    else {
        if (dx::misc::approximatelyZero(velocity.x)) {
            velocity.x = v.x;
        }
        if (dx::misc::approximatelyZero(velocity.y)) {
            velocity.y = v.y;
        }
        velocity.x *= m_param->air_resistance;
    }
    m_body.setVelocity(velocity);
}

void PhysicalCharacter::drawLegacy() const {
    m_body.draw();
}
    
// private function ------------------------------
// ctor/dtor -------------------------------------
PhysicalCharacter::PhysicalCharacter(
    s3d::P2World* world,
    dx::di::PlayerId pid,
    const std::shared_ptr<chara::IParameterizedCharacter>& status,
    const std::shared_ptr<param::CharaPhysics>& param) :
m_pid(pid),
m_body(world->createRect(Vec2(0, -5), SizeF(2, 3), P2Material(1.0, 0.0, param->chara_friction))),
m_status(status),
m_param(param) {
    m_body.setFixedRotation(true);
}


/* ---------- PhysicalStage ---------- */

// static ----------------------------------------
// public function -------------------------------
void PhysicalStage::drawLegacy() const {
    m_floor.draw(Palette::Skyblue);
    m_ceiling.draw(Palette::Skyblue);
    m_wall_left.draw(Palette::Skyblue);
    m_wall_right.draw(Palette::Skyblue);
}
// private function ------------------------------
// ctor/dtor -------------------------------------
PhysicalStage::PhysicalStage(s3d::P2World* world, const std::shared_ptr<param::CharaPhysics>& param) :
m_floor     (world->createStaticLine(Vec2(  0,  0), Line(-25, 0, 25, 0), P2Material(1.0, 0.0, param->floor_friction))),
m_ceiling   (world->createStaticLine(Vec2(  0,-25), Line(-25, 0, 25, 0), P2Material(1.0, 0.0, param->ceiling_friction))),
m_wall_left (world->createStaticLine(Vec2(-25,  0), Line(0, -25, 0, 10), P2Material(1.0, 0.0, param->wall_friction))),
m_wall_right(world->createStaticLine(Vec2( 25,  0), Line(0, -25, 0, 10), P2Material(1.0, 0.0, param->wall_friction))) {}


/* ---------- PhysicalWorldManager ---------- */

// static ----------------------------------------
// public function -------------------------------
void PhysicalWorldManager::initializeCharacters(const std::unordered_map<dx::di::PlayerId, std::shared_ptr<BattlePlayer>>& players) {
    for (const auto& player : players) {
        m_characters.insert(std::make_pair(player.first,
            std::make_shared<PhysicalCharacter>(
                &m_world,
                player.first,
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
    m_camera.update();
    {
        // 2D カメラの設定から Transformer2D を作成・適用
        const auto t = m_camera.createTransformer();
        for (auto& chara : m_characters) {
            chara.second->update();
        }
        
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
