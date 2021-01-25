#pragma once
#include <Siv3D/Rectangle.hpp>
#include <Siv3D/Physics2D.hpp>
#include "IDs.hpp"
#include "Timer.hpp"
#include "CollisionObserver.hpp"

namespace dx {
namespace phys {
class PhysicalWorld;
class IPhysicalObject;
}
}
namespace kanji {
namespace md {
class MasterRadicalParam;
}
namespace battle {


class PhysicalRadical : public dx::phys::CollisionObserver {
private: // static_const/enum
    static constexpr dx::Time c_timelimit = 10.f;
public: // static
public: // public function
    RadicalID id() const;
    const md::MasterRadicalParam* md() const { return m_md; }
    const std::shared_ptr<s3d::P2Body>& body() const;
    s3d::Vec2 position() const;
    s3d::Quad rect() const;

    // 終了したらtrueを返す
    bool update(dx::Time dt);
    void vanish() { m_has_vanished = true; } // 自然消滅
    void taken() { vanish(); } // プレイヤーに拾われる
private: // field
    dx::Time m_timer;
    const md::MasterRadicalParam* m_md;
    bool m_has_vanished = false;
private: // private function
public: // ctor/dtor
    PhysicalRadical(
        RadicalID id,
        const std::shared_ptr<dx::phys::PhysicalWorld>& world,
        const s3d::Vec2& initial_pos);
};


class PhysicalRadicalManager {
public: // static_const/enum
public: // static
    static s3d::Vec2 randomCreatePos();
public: // public function
    const std::shared_ptr<PhysicalRadical>& createRadical(RadicalID id);
    void update(dx::Time dt);
    void takenRadical(int i) { m_radicals.erase(m_radicals.begin() + i); }
    
    const std::vector<std::shared_ptr<PhysicalRadical>>& radicals() const;
private: // field
    std::vector<std::shared_ptr<PhysicalRadical>> m_radicals;
    std::shared_ptr<dx::phys::PhysicalWorld> m_world;
private: // private function
public: // ctor/dtor
    PhysicalRadicalManager(const std::shared_ptr<dx::phys::PhysicalWorld>& world) :
    m_world(world) {}
};



}
}

