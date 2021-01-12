#pragma once
#include <Siv3D/Rectangle.hpp>
#include <Siv3D/Physics2D.hpp>
#include "IDs.hpp"
#include "Timer.hpp"

namespace kanji {
namespace md {
class MasterRadicalParam;
}
namespace battle {


class PhysicalRadical {
public: // static_const/enum
public: // static
public: // public function
    s3d::RectF currentHitBox() const;
    const s3d::P2Body& body() const { return m_body; }

    // 終了したらtrueを返す
    bool update(dx::Time dt);
private: // field
    dx::Time m_timer;
    const md::MasterRadicalParam* m_md;
    s3d::P2Body m_body;
private: // private function
public: // ctor/dtor
    PhysicalRadical(
        RadicalID id,
        s3d::P2World* world,
        const s3d::Vec2& initial_pos);
};


class PhysicalRadicalManager {
public: // static_const/enum
public: // static
    static s3d::Vec2 randomCreatePos();
public: // public function
    const std::shared_ptr<PhysicalRadical>& createRadical(RadicalID id);
    void update(dx::Time dt);
    
    const std::vector<std::shared_ptr<PhysicalRadical>>& radicals() const;
private: // field
    std::vector<std::shared_ptr<PhysicalRadical>> m_radicals;
    s3d::P2World* m_p2world;
private: // private function
public: // ctor/dtor
    PhysicalRadicalManager(s3d::P2World* p2world) :
    m_p2world(p2world) {}
};



}
}

