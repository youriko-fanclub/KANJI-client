#pragma once
#include <unordered_map>
#include <Siv3D/Vector2D.hpp>
#include <Siv3D/Physics2D.hpp>
#include "PlayerId.hpp"
#include "TomlAsset.hpp"
#include "IDs.hpp"

namespace kanji {
namespace md {
class MasterStage;
}
namespace battle {

class PhysicalStage {
public: // static_const/enum
public: // static
public: // public function
    void drawLegacy() const; // 近いうちに消す
    
    // player_num: 参加者人数 [1, 4]
    std::vector<s3d::Vec2> initialCharaPositions(int player_num) const;
private: // field
    const md::MasterStage* m_md;
    const s3d::P2Body m_floor;
    const s3d::P2Body m_ceiling;
    const s3d::P2Body m_wall_left;
    const s3d::P2Body m_wall_right;
private: // private function
    void initialize();
public: // ctor/dtor
    PhysicalStage(s3d::P2World* world, StageID id, const dx::toml::TomlAsset& physical);
};

}
}
