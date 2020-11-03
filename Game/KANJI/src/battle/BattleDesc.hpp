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
public:
    std::vector<std::shared_ptr<chara::IParameterizedCharacter>> m_characters;
};

struct BattleDesc {
public:
    std::unordered_map<dx::di::PlayerId, BattlePlayerDesc> m_players;
    int m_timelimit;
    int m_stage_id;
};

struct BattleResultDesc {
public:
    std::vector<dx::di::PlayerId> m_ranking;
};


}
}

