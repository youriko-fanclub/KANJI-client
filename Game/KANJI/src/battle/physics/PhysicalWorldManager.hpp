#pragma once
#include <unordered_map>
#include <Siv3D.hpp>
#include "PlayerId.hpp"
#include "CharaPhysicsParameters.hpp"

namespace kanji {
namespace battle {
class BattlePlayer;
class PhysicalCharacter;
class PhysicalStage;

class PhysicalWorldManager {
public: // static_const/enum
public: // static
public: // public function
    void initializeCharacters(const std::unordered_map<dx::di::PlayerId, std::shared_ptr<BattlePlayer>>& players);
    void update();

    const std::unordered_map<dx::di::PlayerId, std::shared_ptr<PhysicalCharacter>>& characters() const {
        return m_characters;
    }
    const std::shared_ptr<PhysicalStage>& stage() const {
        return m_stage;
    }
private: // field
    std::shared_ptr<param::CharaPhysics> m_param;

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
