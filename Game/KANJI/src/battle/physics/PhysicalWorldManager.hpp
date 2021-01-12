#pragma once
#include <unordered_map>
#include <Siv3D.hpp>
#include "PlayerId.hpp"
#include "TomlAsset.hpp"
#include "IDs.hpp"

namespace kanji {
namespace battle {
class BattlePlayer;
class PhysicalCharacter;
class PhysicalStage;
class PhysicalRadicalManager;

class PhysicalWorldManager {
public: // static_const/enum
public: // static
public: // public function
    void initializeCharacters(const std::unordered_map<dx::di::PlayerId, std::shared_ptr<BattlePlayer>>& players);
    void initializeStage(StageID id);
    void update();

    const std::unordered_map<dx::di::PlayerId, std::shared_ptr<PhysicalCharacter>>& characters() const {
        return m_characters;
    }
    const std::shared_ptr<PhysicalStage>& stage() const {
        return m_stage;
    }
    const std::shared_ptr<PhysicalRadicalManager>& radicalMgr() const {
        return m_radical_mgr;
    }
    void lose(dx::di::PlayerId pid);
private: // field
    dx::toml::TomlAsset m_toml;

    P2World m_world;
    std::unordered_map<dx::di::PlayerId, std::shared_ptr<PhysicalCharacter>> m_characters;
    std::shared_ptr<PhysicalStage> m_stage;
    std::shared_ptr<PhysicalRadicalManager> m_radical_mgr;
private: // private function
public: // ctor/dtor
    PhysicalWorldManager();
    
};

}
}
