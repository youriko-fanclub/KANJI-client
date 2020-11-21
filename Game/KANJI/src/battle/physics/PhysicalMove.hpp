#pragma once
#include <Siv3D/Vector2D.hpp>
#include <Siv3D/Circular.hpp>
#include <Siv3D/Rectangle.hpp>
#include "PlayerId.hpp"
#include "Move.hpp"
#include "PhysicalCharacter.hpp"

namespace kanji {
namespace battle {

struct MomentaryMove {
public: // field
    const float time;
    const int damage;
    const s3d::Circular shoot_force;
    const s3d::RectF hitbox;
public: // static
    static MomentaryMove divideLinear(float t, const MomentaryMove& from, const MomentaryMove& to, bool is_right, const s3d::Vec2& origin);
    static s3d::RectF divideHitboxLinear(float t, const MomentaryMove& from, const MomentaryMove& to, bool is_right, const s3d::Vec2& origin);
public: // ctor/dtor
    MomentaryMove(float time, int damage, const s3d::Circular& shoot_force, const s3d::RectF& hitbox);
};

class Trajectory {
public: // static_const/enum
public: // static
public: // public function
    float totalTime() const { return m_moments.back().time; }
    MomentaryMove momentary(float time, bool is_right, const s3d::Vec2& origin) const;
    s3d::RectF momentaryHitbox(float time, bool is_right, const s3d::Vec2& origin) const;
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
    MomentaryMove currentMoment() const;
    s3d::RectF currentHitBox() const;
    
    // 終了したらtrueを返す
    bool update(float dt);
private: // field
    float m_timer;
    dx::di::PlayerId m_owner;
    bool m_is_right;
    std::shared_ptr<PhysicalCharacter> m_ownerChara;
    const std::shared_ptr<Move>& m_md;
private: // private function
public: // ctor/dtor
    PhysicalMove(dx::di::PlayerId owner, const std::shared_ptr<battle::PhysicalCharacter>& ownerChara, md::MoveId moveId);
};


class PhysicalMoveManager {
public: // static_const/enum
public: // static
public: // public function
    const std::shared_ptr<PhysicalMove>& createMove(dx::di::PlayerId owner, const std::shared_ptr<PhysicalCharacter>& ownerChara, md::MoveId moveId);
    void update(float dt);
    
    const std::vector<std::shared_ptr<PhysicalMove>>& moves() const;
private: // field
    std::vector<std::shared_ptr<PhysicalMove>> m_moves;
private: // private function
public: // ctor/dtor
};


}
}
