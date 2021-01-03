#include "PhysicalCharacter.hpp"
#include "Input.hpp"
#include "Misc.hpp"
#include "BattlePlayer.hpp"
#include "ParameterizedCharacter.hpp"

namespace kanji {
namespace battle {

/* ---------- PhysicalCharacter ---------- */

// static ----------------------------------------
// public function -------------------------------
void PhysicalCharacter::shoot(const s3d::Circular& force) {
    // TOdO: 要検討: 力の与え方
    m_body.applyLinearImpulse(force.toVec2());
    // m_body.setVelocity(force.toVec2());
    // m_body.applyForce(force.toVec2());
}

void PhysicalCharacter::update() {
    const auto& input = dx::di::Input::get(m_pid);
    const dx::cmp::TomlKey key(U"physics.chara");
    s3d::Vec2 force(
        m_toml[key + U"force.horizontal"].get<double>() * input.arrowL().x,
        input.dpad().up().down() || input.buttons().b().down() ? -m_toml[key + U"force.jump"].get<double>() : 0.0);
    m_body.applyLinearImpulse(force); // 入力による速度変化
    
    auto velocity = m_body.getVelocity();
    constexpr float vx_max = 15;
    if (velocity.x > vx_max) {
        m_body.setVelocity(s3d::Vec2(vx_max, velocity.y));
    }
    if (velocity.x < -vx_max) {
        m_body.setVelocity(s3d::Vec2(-vx_max, velocity.y));
    }
    m_body.applyForce(-m_toml[key + U"air_resistance"].get<double>() * velocity); // 空気抵抗
    m_body.applyForce(s3d::Vec2(0, 9.80665)); // 重力
    
    constexpr float threshold = 0.1f;
    if (m_is_right && velocity.x < -threshold) { m_is_right = false; }
    else if (!m_is_right && velocity.x > threshold) { m_is_right = true; }
}

// private function ------------------------------
// ctor/dtor -------------------------------------
PhysicalCharacter::PhysicalCharacter(
    s3d::P2World* world,
    dx::di::PlayerId pid,
    const s3d::Vec2& initial_pos,
    bool is_right,
    const std::shared_ptr<battle::BattlePlayer>& player,
    const dx::cmp::TomlAsset& toml) :
m_pid(pid),
m_body(world->createRect(initial_pos, SizeF(3, 3), P2Material(1.0, 0.0, toml[dx::cmp::TomlKey(U"physics.chara.friction")].get<double>()))),
m_is_right(is_right),
m_status(player),
m_toml(toml) {
    m_body.setFixedRotation(true);
}


}
}
