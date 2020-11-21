#pragma once
#include <unordered_map>
#include <Siv3D.hpp>
#include "PlayerId.hpp"
#include "CharaPhysicsParameters.hpp"

namespace kanji {
namespace battle {

class PhysicalStage {
public: // static_const/enum
public: // static
public: // public function
    void drawLegacy() const; // 近いうちに消す
private: // field
    const P2Body m_floor;
    const P2Body m_ceiling;
    const P2Body m_wall_left;
    const P2Body m_wall_right;
private: // private function
public: // ctor/dtor
    PhysicalStage(s3d::P2World* world, const std::shared_ptr<param::CharaPhysics>& param);
};

}
}
