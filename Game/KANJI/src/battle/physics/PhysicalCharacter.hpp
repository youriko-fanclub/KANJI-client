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

}
}
