#pragma once
#include <unordered_map>
#include <Siv3D.hpp>
#include "PlayerId.hpp"
#include "CharaPhysicsParameters.hpp"

namespace kanji {
namespace battle {
class BattlePlayer;

class PhysicalCharacter {
public: // static_const/enum
public: // static
public: // public function
    bool isRight() const { return m_is_right; }
    const std::shared_ptr<battle::BattlePlayer>& status() const {
        return m_status;
    }
    s3d::Vec2 position() const { return m_body.getPos(); }
    s3d::Quad rect() const { return m_body.as<s3d::P2Rect>(0)->getQuad(); }
    
    void shoot(const s3d::Circular& force);
    
    void update();
private: // field
    dx::di::PlayerId m_pid;
    P2Body m_body;
    bool m_is_right; // 右向きか否か
    const std::shared_ptr<battle::BattlePlayer> m_status;
    std::shared_ptr<param::CharaPhysics> m_param;
private: // private function
public: // ctor/dtor
    PhysicalCharacter(
        s3d::P2World* world,
        dx::di::PlayerId pid,
        const s3d::Vec2& initial_pos,
        bool is_right,
        const std::shared_ptr<battle::BattlePlayer>& player,
        const std::shared_ptr<param::CharaPhysics>& param);
};

}
}
