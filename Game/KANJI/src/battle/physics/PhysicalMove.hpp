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
    static MomentaryMove divideLinear(float t, const MomentaryMove& from, const MomentaryMove& to, bool is_right, const s3d::Vec2& origin) {
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
    static s3d::RectF divideHitboxLinear(float t, const MomentaryMove& from, const MomentaryMove& to, bool is_right, const s3d::Vec2& origin) {
        const float s = t / (to.time - from.time);
        return s3d::RectF(
            s3d::Arg::center(origin + (is_right ? 1 : -1) *
                (s * to.hitbox.center() + (1-s) * from.hitbox.center())),
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
    MomentaryMove momentary(float time, bool is_right, const s3d::Vec2& origin) const {
        int index = -1;
        for (int i = 0; i < m_moments.size(); ++i) {
            if (time <= m_moments.at(i).time) {
                index = i;
            }
        }
        // if (index < 0) { return; }
        return MomentaryMove::divideLinear(time, m_moments.at(index - 1), m_moments.at(index), is_right, origin);
    }
    s3d::RectF momentaryHitbox(float time, bool is_right, const s3d::Vec2& origin) const {
        int index = -1;
        for (int i = 0; i < m_moments.size(); ++i) {
            if (time <= m_moments.at(i).time) {
                index = i;
            }
        }
        // if (index < 0) { return; }
        return MomentaryMove::divideHitboxLinear(time, m_moments.at(index - 1), m_moments.at(index), is_right, origin);
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
        return m_md->trajectory->momentary(m_timer, m_is_right, m_origin);
    }
    s3d::RectF currentHitBox() const {
        return m_md->trajectory->momentaryHitbox(m_timer, m_is_right, m_origin);
    }
    
    // 終了したらtrueを返す
    bool update(float dt) {
        m_timer += dt;
        return m_timer > m_md->trajectory->totalTime();
    }
private: // field
    float m_timer;
    dx::di::PlayerId m_owner;
    bool m_is_right;
    s3d::Vec2 m_origin;
    const std::shared_ptr<Move>& m_md;
private: // private function
public: // ctor/dtor
    PhysicalMove(dx::di::PlayerId owner, bool is_right, const s3d::Vec2& origin, md::MoveId moveId) :
        m_timer(0),
        m_owner(owner),
        m_is_right(is_right),
        m_origin(origin),
        m_md(md::MasterRepository::instance()->get(moveId)) {}
};


class PhysicalMoveManager {
public: // static_const/enum
public: // static
public: // public function
    const std::shared_ptr<PhysicalMove>& createMove(dx::di::PlayerId owner, bool is_right, const s3d::Vec2& origin, md::MoveId moveId) {
        m_moves.push_back(std::make_shared<PhysicalMove>(owner, is_right, origin, moveId));
        return m_moves.back();
    }
    void update(float dt) {
        for (auto it = m_moves.begin(); it != m_moves.end();) {
            if ((*it)->update(dt)) {
                it = m_moves.erase(it);
            }
            else { ++it; }
        }
    }
    void drawLegacy() const {
        for (const auto& move : m_moves) {
            const auto box = move->currentHitBox();
            box.draw(s3d::Palette::Red);
            // move->currentHitBox().draw(s3d::Palette::Red);
        }
    }
private: // field
    std::vector<std::shared_ptr<PhysicalMove>> m_moves;
private: // private function
public: // ctor/dtor
};


}
}
