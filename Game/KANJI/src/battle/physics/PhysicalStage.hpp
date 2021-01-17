#pragma once
#include <unordered_map>
#include <Siv3D/Vector2D.hpp>
#include <Siv3D/Physics2D.hpp>
#include "PlayerId.hpp"
#include "TomlAsset.hpp"
#include "IDs.hpp"

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
    const std::shared_ptr<dx::phys::IPhysicalObject> m_floor;
    const std::shared_ptr<dx::phys::IPhysicalObject> m_ceiling;
    const std::shared_ptr<dx::phys::IPhysicalObject> m_wall_left;
    const std::shared_ptr<dx::phys::IPhysicalObject> m_wall_right;
private: // private function
    void initialize();
public: // ctor/dtor
    PhysicalStage(const std::shared_ptr<dx::phys::PhysicalWorld>& world, StageID id, const dx::toml::TomlAsset& physical);
};

}
}
