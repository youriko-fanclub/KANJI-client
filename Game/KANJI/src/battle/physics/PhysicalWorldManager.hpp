#pragma once
#include <Siv3D.hpp>
#include "CharaPhysicsParameters.hpp"

namespace kanji {
namespace battle {

class PhysicalWorldManager {
public: // static_const/enum
public: // static
public: // public function
    void update();
    // void updateLegacy(); // 近いうちに消す
    void drawLegacy() const; // 近いうちに消す
private: // field
    // ↓ここから下は試し書きの無法地帯
    std::shared_ptr<param::CharaPhysics> param;

    // 2Dカメラ
    Camera2D m_camera;
    // 物理演算用のワールド
    P2World m_world;
    // 物体
    P2Body m_chara;
    Array<P2Body> m_bodies;
    // 床
    const P2Body m_floor;
    const P2Body m_ceiling;
    const P2Body m_wall_left;
    const P2Body m_wall_right;
private: // private function
public: // ctor/dtor
    PhysicalWorldManager();
    
};

}
}
