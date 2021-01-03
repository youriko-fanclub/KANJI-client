#pragma once
#include <unordered_map>
#include <Siv3D/Vector2D.hpp>
#include <Siv3D/Physics2D.hpp>
#include "PlayerId.hpp"
#include "CharaPhysicsParameters.hpp"
#include "TomlAsset.hpp"

namespace kanji {
namespace battle {

using StageId = int; // TOdO
struct PhysicalStageDesc {
public:
    StageId id;
    s3d::String name;
    std::unordered_map<int, std::shared_ptr<std::vector<s3d::Vec2>>> initial_positions;
public:
    static PhysicalStageDesc createFromToml(const s3d::String& name);
private:
    PhysicalStageDesc() = default;
};


class PhysicalStage {
public: // static_const/enum
public: // static
public: // public function
    void drawLegacy() const; // 近いうちに消す
    
    // player_num: 参加者人数 [1, 4]
    const std::vector<s3d::Vec2>& initialCharaPositions(int player_num) const;
private: // field
    const PhysicalStageDesc m_desc;
    const s3d::P2Body m_floor;
    const s3d::P2Body m_ceiling;
    const s3d::P2Body m_wall_left;
    const s3d::P2Body m_wall_right;
private: // private function
    void initialize();
public: // ctor/dtor
    PhysicalStage(s3d::P2World* world, const dx::cmp::TomlAsset& toml);
};

}
}
