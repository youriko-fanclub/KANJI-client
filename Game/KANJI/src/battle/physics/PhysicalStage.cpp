#include "PhysicalStage.hpp"
#include "HotReloadManager.hpp"

namespace kanji {
namespace battle {


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


}
}
