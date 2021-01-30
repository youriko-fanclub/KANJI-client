#pragma once
#include <Siv3D.hpp>
#include "PlayerId.hpp"
#include "TomlAsset.hpp"
#include "CollisionObserver.hpp"

namespace dx {
namespace phys {
class PhysicalWorld;
class IPhysicalObject;
}
}
namespace kanji {
namespace battle {
class BattlePlayer;

class PhysicalCharacter : public dx::phys::CollisionObserver {
public: // static_const/enum
public: // static
public: // public function
    bool isRight() const { return m_is_right; }
    const std::shared_ptr<battle::BattlePlayer>& status() const {
        return m_status;
    }
    s3d::Vec2 position() const;
    s3d::Quad rect() const;
    
    void shoot(const s3d::Circular& force);
    
    void update();
    
private: // field
    dx::di::PlayerId m_pid;
    bool m_is_right; // 右向きか否か
    const std::shared_ptr<battle::BattlePlayer> m_status;
    dx::toml::TomlAsset m_toml;
private: // private function
    const std::shared_ptr<s3d::P2Body>& body() const;
public: // ctor/dtor
    PhysicalCharacter(
        const std::shared_ptr<dx::phys::PhysicalWorld>& world,
        dx::di::PlayerId pid,
        const s3d::Vec2& initial_pos,
        bool is_right,
        const std::shared_ptr<battle::BattlePlayer>& player,
        const dx::toml::TomlAsset& toml);
};

}
}
