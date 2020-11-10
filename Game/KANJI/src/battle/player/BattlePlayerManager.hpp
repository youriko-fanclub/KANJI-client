#pragma once
#include <unordered_map>
#include "PlayerId.hpp"

namespace kanji {
namespace battle {

class BattlePlayerDesc;
class BattlePlayer;

class BattlePlayerManager {
public: // static_const/enum
public: // static
public: // public function
    const std::unordered_map<dx::di::PlayerId, std::shared_ptr<BattlePlayer>>& players() const {
        return m_players;
    }
private: // field
    std::unordered_map<dx::di::PlayerId, std::shared_ptr<BattlePlayer>> m_players;
private: // private function
public: // ctor/dtor
    BattlePlayerManager(const std::unordered_map<dx::di::PlayerId, std::shared_ptr<BattlePlayerDesc>>& descs);
};


}
}

