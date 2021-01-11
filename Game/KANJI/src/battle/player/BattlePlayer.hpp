#pragma once
#include <vector>
#include "PlayerId.hpp"
#include "IDs.hpp"
#include "Radical.hpp"

namespace kanji {
namespace chara {
class IParameterizedCharacter;
class Radical;
}
namespace battle {
class PhysicalCharacter;
class BattlePlayerDesc;
class MomentaryMove;

class BattlePlayer {
public: // static_const/enum
    struct Score {
    public:
        int ko_count = 0;
        int dead_count = 0;
        int gave_damage = 0; // 与ダメ
        int given_damage = 0; // 被ダメ
        float left_hp_rate = 0.f;
    };
public: // static
public: // public function
    dx::di::PlayerId pid() const { return m_pid; }
    
    std::shared_ptr<chara::IParameterizedCharacter> activeCharacter();
    const std::vector<std::shared_ptr<chara::IParameterizedCharacter>>& characters() const {
        return m_characters;
    }
    // 変更先が無かった(生存キャラが1体以下)場合falseを返す
    bool changeActiveCharacter();

    bool hasRadical() const;
    const std::unique_ptr<chara::Radical>& radical() const;
    void setRadical(RadicalID radical_id);
    
    const std::shared_ptr<PhysicalCharacter>& physical() { return m_physical; }
    void initializePhysical(const std::shared_ptr<PhysicalCharacter>& physical) {
        m_physical = physical;
    }
    
    void addGaveDamage(int amount) { m_score.gave_damage += amount; }
    void attack(const MomentaryMove& move, bool is_from_left);
    bool isLost() const { return m_is_lost; }
    const Score& scoreForRanked();
    void addKOCount() { ++m_score.ko_count; }

private: // field
    dx::di::PlayerId m_pid;
    int m_active_index;
    std::vector<std::shared_ptr<chara::IParameterizedCharacter>> m_characters;
    chara::RadicalHolder m_radical;
    std::shared_ptr<PhysicalCharacter> m_physical;
    bool m_is_lost;
    Score m_score;
private: // private function
    void lose();
public: // ctor/dtor
    BattlePlayer(dx::di::PlayerId pid, const std::shared_ptr<BattlePlayerDesc>& desc);
};


}
}
