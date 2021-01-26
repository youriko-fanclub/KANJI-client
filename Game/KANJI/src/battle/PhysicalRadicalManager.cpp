#include "PhysicalRadicalManager.hpp"
#include "MasterRadicalParamRepository.hpp"
#include "PhysicalCategory.hpp"
#include "PhysicalWorld.hpp"

namespace kanji {
namespace battle {


/* ---------- PhysicalRadical ---------- */

// static ----------------------------------------
// public function -------------------------------
RadicalID PhysicalRadical::id() const { return m_md->id(); }

const std::shared_ptr<s3d::P2Body>& PhysicalRadical::body() const {
    return obj()->body();
}

s3d::Vec2 PhysicalRadical::position() const { return body()->getPos(); }
s3d::Quad PhysicalRadical::rect() const {
    return body()->as<s3d::P2Rect>(0)->getQuad();
}

bool PhysicalRadical::update(dx::Time dt) {
    m_timer += dt;
    return m_has_vanished || m_timer > c_timelimit; // 消してほしいときにtrueを返す
}

// private function ------------------------------
// ctor/dtor -------------------------------------
PhysicalRadical::PhysicalRadical(
    RadicalID id,
    const std::shared_ptr<dx::phys::PhysicalWorld>& world,
    const s3d::Vec2& initial_pos) :
CollisionObserver(world->createRect(
    PhysicalCategory::Radical,
    initial_pos, s3d::SizeF(3, 3),
    s3d::P2Material(1.0, 0.0, 1.0))),
m_timer(0),
m_md(md::MasterRadicalParamRepository::instance()->at(id)) {}


/* ---------- PhysicalRadicalManager ---------- */

// static ----------------------------------------
s3d::Vec2 PhysicalRadicalManager::randomCreatePos() {
    return s3d::Vec2(0.f, -10.f); // TOdO: 適切かつランダムに
}
// public function -------------------------------
const std::shared_ptr<PhysicalRadical>& PhysicalRadicalManager::createRadical(RadicalID id) {
    m_radicals.push_back(std::make_shared<PhysicalRadical>(id, m_world, randomCreatePos()));
    return m_radicals.back();
}
void PhysicalRadicalManager::update(dx::Time dt) {
    for (auto it = m_radicals.begin(); it != m_radicals.end();) {
        if ((*it)->update(dt)) {
            it = m_radicals.erase(it);
        }
        else { ++it; }
    }
}

const s3d::Array<std::shared_ptr<PhysicalRadical>>& PhysicalRadicalManager::radicals() const {
    return m_radicals;
}
// private function ------------------------------
// ctor/dtor -------------------------------------


}
}
