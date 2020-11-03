#pragma once
#include <vector>
#include <unordered_map>
#include "PlayerId.hpp"

namespace kanji {
namespace chara {
    class IParameterizedCharacter;
}
namespace battle {

struct BattlePlayerDesc {
public: // public function
    const std::vector<std::shared_ptr<chara::IParameterizedCharacter>>& characters() const {
        return m_characters;
    }
    std::vector<std::shared_ptr<chara::IParameterizedCharacter>>& characters() {
        return m_characters;
    }
private: // field
    std::vector<std::shared_ptr<chara::IParameterizedCharacter>> m_characters;
};

class BattleDesc {
public: // static_const/enum
public: // static
public: // public function
    const std::shared_ptr<BattlePlayerDesc>& playerDesc(dx::di::PlayerId id) { return m_players.at(id); }
    const std::shared_ptr<BattlePlayerDesc>& playerDesc(dx::di::PlayerId id) const { return m_players.at(id); }
    void setPlayerDesc(dx::di::PlayerId id, const std::shared_ptr<BattlePlayerDesc>& value);
    int timeLimitSec() const { return m_timeLimit_sec; }
    void setTimeLimitSec(int value) { m_timeLimit_sec = value; }
    int stageId() const { return m_stage_id; }
    void setStageId(int value) { m_stage_id = value; }
private: // field
    std::unordered_map<dx::di::PlayerId, std::shared_ptr<BattlePlayerDesc>> m_players;
    int m_timeLimit_sec;
    int m_stage_id;
private: // private function
public: // ctor/dtor
};

struct BattleResultDesc {
public:
    std::vector<dx::di::PlayerId> m_ranking;
};


}
}

