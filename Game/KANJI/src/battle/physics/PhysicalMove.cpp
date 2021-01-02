#include "PhysicalMove.hpp"

namespace kanji {
namespace battle {

/* ---------- MomentaryMove ---------- */

// static ----------------------------------------
MomentaryMove MomentaryMove::divideLinear(float t, const MomentaryMove& from, const MomentaryMove& to, bool is_right, const s3d::Vec2& origin) {
    const float s = t / (to.time - from.time);
    // TOdO: とりあえず全部線形補間してるけど変えたほうが良さそう
    return MomentaryMove(
        t,
        static_cast<int>(s * to.damage + (1-s) * from.damage),
        s3d::Circular( // TOdO: theta を isRight によって切り替える
            s * to.shoot_force.r + (1-s) * from.shoot_force.r,
            s * to.shoot_force.theta + (1-s) * from.shoot_force.theta),
        divideHitboxLinear(t, from, to, is_right, origin)
    );
}
s3d::RectF MomentaryMove::divideHitboxLinear(float t, const MomentaryMove& from, const MomentaryMove& to, bool is_right, const s3d::Vec2& origin) {
    const float s = (t - from.time) / (to.time - from.time);
    return s3d::RectF(s3d::Arg::center(
        (s * to.hitbox.center().x + (1.f-s) * from.hitbox.center().x) * (is_right ? 1.f : -1.f) + origin.x,
        s * to.hitbox.center().y + (1.f-s) * from.hitbox.center().y + origin.y),
        s * to.hitbox.w + (1.f-s) * from.hitbox.w,
        s * to.hitbox.h + (1.f-s) * from.hitbox.h);
}
// public function -------------------------------
// private function ------------------------------
// ctor/dtor -------------------------------------
MomentaryMove::MomentaryMove(float time, int damage, const s3d::Circular& shoot_force, const s3d::RectF& hitbox) :
time(time), damage(damage), shoot_force(shoot_force), hitbox(hitbox) {}


/* ---------- Trajectory ---------- */

// static ----------------------------------------
// public function -------------------------------
MomentaryMove Trajectory::momentary(float time, bool is_right, const s3d::Vec2& origin) const {
    int index = -1;
    for (int i = 0; i < m_moments.size(); ++i) {
        if (time <= m_moments.at(i).time) {
            index = i;
        }
    }
    // if (index < 0) { return; }
    return MomentaryMove::divideLinear(time, m_moments.at(index - 1), m_moments.at(index), is_right, origin);
}

s3d::RectF Trajectory::momentaryHitbox(float time, bool is_right, const s3d::Vec2& origin) const {
    int index = -1;
    for (int i = 0; i < m_moments.size(); ++i) {
        if (time <= m_moments.at(i).time) {
            index = i;
            break;
        }
    }
    // if (index < 0) { return; }
    return MomentaryMove::divideHitboxLinear(time, m_moments.at(index - 1), m_moments.at(index), is_right, origin);
}

// private function ------------------------------
// ctor/dtor -------------------------------------


/* ---------- PhysicalMove ---------- */

// static ----------------------------------------
// public function -------------------------------
MomentaryMove PhysicalMove::currentMoment() const {
    return m_md->trajectory->momentary(m_timer, m_is_to_right, m_owner_chara->position());
}
s3d::RectF PhysicalMove::currentHitBox() const {
    return m_md->trajectory->momentaryHitbox(m_timer, m_is_to_right, m_owner_chara->position());
}

bool PhysicalMove::update(float dt) {
    m_timer += dt;
    return m_timer > m_md->trajectory->totalTime();
}
// private function ------------------------------
// ctor/dtor -------------------------------------
PhysicalMove::PhysicalMove(dx::di::PlayerId owner, const std::shared_ptr<battle::PhysicalCharacter>& owner_chara, MoveID move_id) :
    m_timer(0),
    m_owner(owner),
    m_is_to_right(owner_chara->isRight()),
    m_owner_chara(owner_chara),
    m_md(md::MasterRepository::instance()->get(move_id)) {}


/* ---------- PhysicalMoveManager ---------- */

// static ----------------------------------------
// public function -------------------------------
const std::shared_ptr<PhysicalMove>& PhysicalMoveManager::createMove(dx::di::PlayerId owner, const std::shared_ptr<PhysicalCharacter>& owner_chara, MoveID move_id) {
    m_moves.push_back(std::make_shared<PhysicalMove>(owner, owner_chara, move_id));
    return m_moves.back();
}
void PhysicalMoveManager::update(float dt) {
    for (auto it = m_moves.begin(); it != m_moves.end();) {
        if ((*it)->update(dt)) {
            it = m_moves.erase(it);
        }
        else { ++it; }
    }
}

const std::vector<std::shared_ptr<PhysicalMove>>& PhysicalMoveManager::moves() const {
    return m_moves;
}
// private function ------------------------------
// ctor/dtor -------------------------------------


}
}
