#pragma once
#include <unordered_map>
#include <Siv3D.hpp>
#include "PlayerId.hpp"
#include "CharaPhysicsParameters.hpp"

namespace kanji {
namespace chara {
class IParameterizedCharacter;
}
namespace battle {
class BattlePlayer;

class PhysicalCharacter {
public: // static_const/enum
public: // static
public: // public function
    void update();
    void drawLegacy() const; // 近いうちに消す
private: // field
    dx::di::PlayerId m_pid;
    P2Body m_body;
    const std::shared_ptr<chara::IParameterizedCharacter> m_status;
    std::shared_ptr<param::CharaPhysics> m_param;
private: // private function
public: // ctor/dtor
    PhysicalCharacter(
        s3d::P2World* world,
        dx::di::PlayerId pid,
        const std::shared_ptr<chara::IParameterizedCharacter>& status,
        const std::shared_ptr<param::CharaPhysics>& param);
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
    void initializeCharacters(const std::unordered_map<dx::di::PlayerId, std::shared_ptr<BattlePlayer>>& players);
    void update();
    void drawLegacy() const; // 近いうちに消す
private: // field
    std::shared_ptr<param::CharaPhysics> m_param;

    Camera2D m_camera;
    P2World m_world;
    std::unordered_map<dx::di::PlayerId, std::shared_ptr<PhysicalCharacter>> m_characters;
    std::shared_ptr<PhysicalStage> m_stage;
    
    // テスト用剛体球
    Array<P2Body> m_bodies;
private: // private function
public: // ctor/dtor
    PhysicalWorldManager();
    
};

}
}
