#include "PhysicalCharacter.hpp"
#include "Input.hpp"
#include "Misc.hpp"
#include "BattlePlayer.hpp"
#include "ParameterizedCharacter.hpp"
#include "PhysicalCategory.hpp"
#include "PhysicalWorld.hpp"

namespace kanji {
namespace battle {

/* ---------- PhysicalCharacter ---------- */

// static ----------------------------------------
// public function -------------------------------
s3d::Vec2 PhysicalCharacter::position() const { return body()->getPos(); }
s3d::Quad PhysicalCharacter::rect() const { return body()->as<s3d::P2Rect>(0)->getQuad(); }

void PhysicalCharacter::shoot(const s3d::Circular& force) {
    // TOdO: 要検討: 力の与え方
    body()->applyLinearImpulse(force.toVec2());
    // m_body->setVelocity(force.toVec2());
    // m_body->applyForce(force.toVec2());
}

void PhysicalCharacter::update() {
    const auto& input = dx::di::Input::get(m_pid);
    const dx::toml::TomlKey key(U"physics.chara");
    s3d::Vec2 force(
        m_toml[key + U"force.horizontal"].get<double>() * input.arrowL().x,
        input.dpad().up().down() || input.buttons().b().down() ? -m_toml[key + U"force.jump"].get<double>() : 0.0);
    body()->applyLinearImpulse(force); // 入力による速度変化
    
    auto velocity = body()->getVelocity();
    constexpr float vx_max = 15;
    if (velocity.x > vx_max) {
        body()->setVelocity(s3d::Vec2(vx_max, velocity.y));
    }
    if (velocity.x < -vx_max) {
        body()->setVelocity(s3d::Vec2(-vx_max, velocity.y));
    }
    body()->applyForce(-m_toml[key + U"air_resistance"].get<double>() * velocity); // 空気抵抗
    body()->applyForce(s3d::Vec2(0, 9.80665)); // 重力
    
    constexpr float threshold = 0.1f;
    if (m_is_right && velocity.x < -threshold) { m_is_right = false; }
    else if (!m_is_right && velocity.x > threshold) { m_is_right = true; }
}

// private function ------------------------------
const std::shared_ptr<s3d::P2Body>& PhysicalCharacter::body() const {
    return obj()->body();
}

// ctor/dtor -------------------------------------
PhysicalCharacter::PhysicalCharacter(
    const std::shared_ptr<dx::phys::PhysicalWorld>& world,
    dx::di::PlayerId pid,
    const s3d::Vec2& initial_pos,
    bool is_right,
    const std::shared_ptr<battle::BattlePlayer>& player,
    const dx::toml::TomlAsset& toml) :
CollisionObserver(world->createRect(
    PhysicalCategory::Character,
    initial_pos, SizeF(3, 3),
    P2Material(1.0, 0.0, toml[dx::toml::TomlKey(U"physics.chara.friction")].get<double>()))),
m_pid(pid),
m_is_right(is_right),
m_status(player),
m_toml(toml) {
    body()->setFixedRotation(true);
}


}
}
