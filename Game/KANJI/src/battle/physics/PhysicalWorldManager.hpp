#pragma once
#include <Siv3D.hpp>
#include "CharaPhysicsParameters.hpp"

namespace kanji {
namespace battle {

class PhysicalCharacter {
public: // static_const/enum
public: // static
public: // public function
    void update();
    void drawLegacy() const; // 近いうちに消す
private: // field
    P2Body m_body;
    std::shared_ptr<param::CharaPhysics> m_param;
private: // private function
public: // ctor/dtor
    PhysicalCharacter(s3d::P2World* world, const std::shared_ptr<param::CharaPhysics>& param);
};


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


class PhysicalWorldManager {
public: // static_const/enum
public: // static
public: // public function
    void update();
    void drawLegacy() const; // 近いうちに消す
private: // field
    std::shared_ptr<param::CharaPhysics> m_param;

    Camera2D m_camera;
    P2World m_world;
    std::shared_ptr<PhysicalCharacter> m_chara;
    std::shared_ptr<PhysicalStage> m_stage;
    
    // テスト用剛体球
    Array<P2Body> m_bodies;
private: // private function
public: // ctor/dtor
    PhysicalWorldManager();
    
};

}
}
