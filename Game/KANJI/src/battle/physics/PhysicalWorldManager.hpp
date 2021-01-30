#pragma once
#include <Siv3D.hpp>
#include <Siv3D/HashTable.hpp>
#include "PlayerId.hpp"
#include "TomlAsset.hpp"
#include "IDs.hpp"

namespace dx {
namespace phys {
class PhysicalWorld;
}
}
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
    void initializeCharacters(const s3d::HashTable<dx::di::PlayerId, std::shared_ptr<BattlePlayer>>& players);
    void initializeStage(StageID id);
    void update();

    const s3d::HashTable<dx::di::PlayerId, std::shared_ptr<PhysicalCharacter>>& characters() const {
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

    std::shared_ptr<dx::phys::PhysicalWorld> m_world;
    s3d::HashTable<dx::di::PlayerId, std::shared_ptr<PhysicalCharacter>> m_characters;
    std::shared_ptr<PhysicalStage> m_stage;
    std::shared_ptr<PhysicalRadicalManager> m_radical_mgr;
private: // private function
public: // ctor/dtor
    PhysicalWorldManager();
    
};

}
}
