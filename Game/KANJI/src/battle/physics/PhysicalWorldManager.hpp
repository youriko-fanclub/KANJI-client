#pragma once
#include <unordered_map>
#include <Siv3D.hpp>
#include "PlayerId.hpp"
#include "TomlAsset.hpp"

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
    void lose(dx::di::PlayerId pid);
private: // field
    dx::cmp::TomlAsset m_toml;

    P2World m_world;
    std::unordered_map<dx::di::PlayerId, std::shared_ptr<PhysicalCharacter>> m_characters;
    std::shared_ptr<PhysicalStage> m_stage;
private: // private function
public: // ctor/dtor
    PhysicalWorldManager();
    
};

}
}
