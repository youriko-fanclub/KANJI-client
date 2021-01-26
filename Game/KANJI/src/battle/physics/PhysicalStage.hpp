#pragma once
#include <Siv3D/Vector2D.hpp>
#include <Siv3D/Physics2D.hpp>
#include "PlayerId.hpp"
#include "TomlAsset.hpp"
#include "IDs.hpp"
#include "CollisionObserver.hpp"

namespace dx {
namespace phys {
class PhysicalWorld;
class IPhysicalObject;
}
}
namespace kanji {
namespace md {
class MasterStage;
}
namespace battle {

class PhysicalStageObject : public dx::phys::CollisionObserver {
public: // static_const/enum
public: // static
public: // public function
    const std::shared_ptr<s3d::P2Body>& body() const;
private: // field
private: // private function
public: // ctor/dtor
    PhysicalStageObject(const std::shared_ptr<dx::phys::IPhysicalObject>& physical_obj) :
    CollisionObserver(physical_obj) {}
};


class PhysicalStage {
public: // static_const/enum
public: // static
public: // public function
    const s3d::String& name() const;
    void drawLegacy() const; // 近いうちに消す
    
    // player_num: 参加者人数 [1, 4]
    std::vector<s3d::Vec2> initialCharaPositions(int player_num) const;
private: // field
    const md::MasterStage* m_md;
    s3d::HashTable<s3d::String, std::shared_ptr<PhysicalStageObject>> m_objects;
private: // private function
    void initialize();
public: // ctor/dtor
    PhysicalStage(const std::shared_ptr<dx::phys::PhysicalWorld>& world, StageID id, const dx::toml::TomlAsset& physical);
};

}
}
