#pragma once
#include <Siv3D/Vector2D.hpp>
#include <Siv3D/Circular.hpp>
#include <Siv3D/Rectangle.hpp>
#include "PlayerId.hpp"
#include "Move.hpp"

namespace kanji {
namespace battle {

struct MomentaryMove {
public: // field
    const float time;
    const int damage;
    const s3d::Circular shoot_force;
    const s3d::Rect hitbox;
public: // static
    static MomentaryMove divideLinear(float t, const MomentaryMove& from, const MomentaryMove& to) {
        const float s = t / (to.time - from.time);
        // TOdO: とりあえず全部線形補間してるけど変えたほうが良さそう
        return MomentaryMove(
            t,
            static_cast<int>(s * to.damage + (1-s) * from.damage),
            s3d::Circular(
                s * to.shoot_force.r + (1-s) * from.shoot_force.r,
                s * to.shoot_force.theta + (1-s) * from.shoot_force.theta),
            divideHitboxLinear(t, from, to)
        );
    }
    static s3d::RectF divideHitboxLinear(float t, const MomentaryMove& from, const MomentaryMove& to) {
        const float s = t / (to.time - from.time);
        return s3d::RectF(
            s3d::Arg::center(
                s * to.hitbox.center() + (1-s) * from.hitbox.center()),
            s3d::Size(
                static_cast<int>(s * to.hitbox.w + (1-s) * from.hitbox.w),
                static_cast<int>(s * to.hitbox.h + (1-s) * from.hitbox.h)));
    }
public: // ctor/dtor
    MomentaryMove(float time, int damage, const s3d::Circular& shoot_force, const s3d::Rect& hitbox) :
    time(time), damage(damage), shoot_force(shoot_force), hitbox(hitbox) {}
};

class Trajectory {
public: // static_const/enum
public: // static
public: // public function
    float totalTime() const { return m_moments.back().time; }
    MomentaryMove momentary(float time) const {
        int index = -1;
        for (int i = 0; i < m_moments.size(); ++i) {
            if (time <= m_moments.at(i).time) {
                index = i;
            }
        }
        // if (index < 0) { return; }
        return MomentaryMove::divideLinear(time, m_moments.at(index - 1), m_moments.at(index));
    }
    s3d::RectF momentaryHitbox(float time) const {
        int index = -1;
        for (int i = 0; i < m_moments.size(); ++i) {
            if (time <= m_moments.at(i).time) {
                index = i;
            }
        }
        // if (index < 0) { return; }
        return MomentaryMove::divideHitboxLinear(time, m_moments.at(index - 1), m_moments.at(index));
    }
private: // field
    std::vector<MomentaryMove> m_moments;
private: // private function
public: // ctor/dtor
    Trajectory(const std::vector<MomentaryMove>& moments) :
        m_moments(moments) {}
};

using Move = md::Move;

class PhysicalMove {
public: // static_const/enum
public: // static
public: // public function
    dx::di::PlayerId owner() const { return m_owner; }
    MomentaryMove currentMoment() const {
        return m_md->trajectory->momentary(m_timer);
    }
    s3d::RectF currentHitBox() const {
        return m_md->trajectory->momentaryHitbox(m_timer);
    }
    
    // 終了したらtrueを返す
    bool update(float dt) {
        m_timer += dt;
        return m_timer > m_md->trajectory->totalTime();
    }
private: // field
    dx::di::PlayerId m_owner;
    float m_timer;
    const std::shared_ptr<Move>& m_md;
private: // private function
public: // ctor/dtor
    PhysicalMove(dx::di::PlayerId owner, md::MoveId moveId) :
        m_owner(owner),
        m_timer(0),
        m_md(md::MasterRepository::instance()->get(moveId)) {}
};


}
}
