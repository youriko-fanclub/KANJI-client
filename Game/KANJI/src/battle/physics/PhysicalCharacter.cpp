#include "PhysicalCharacter.hpp"
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
    
    constexpr float threshold = 0.1f;
    if (m_is_right && velocity.x < -threshold) { m_is_right = false; }
    else if (!m_is_right && velocity.x > threshold) { m_is_right = true; }
}

void PhysicalCharacter::drawLegacy() const {
    m_body.draw();
}
    
// private function ------------------------------
// ctor/dtor -------------------------------------
PhysicalCharacter::PhysicalCharacter(
    s3d::P2World* world,
    dx::di::PlayerId pid,
    const s3d::Vec2& initial_pos,
    bool is_right,
    const std::shared_ptr<battle::BattlePlayer>& player,
    const std::shared_ptr<param::CharaPhysics>& param) :
m_pid(pid),
m_body(world->createRect(initial_pos, SizeF(3, 3), P2Material(1.0, 0.0, param->chara_friction))),
m_is_right(is_right),
m_status(player),
m_param(param) {
    m_body.setFixedRotation(true);
}


}
}
