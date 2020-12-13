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
    const std::unordered_map<dx::di::PlayerId, std::shared_ptr<BattlePlayer>>& alivePlayers() const {
        return m_alivePlayers;
    }
    
    void lose(dx::di::PlayerId pid) {
        if (m_alivePlayers.contains(pid)) {
            m_alivePlayers.erase(pid);
        }
    }
private: // field
    std::unordered_map<dx::di::PlayerId, std::shared_ptr<BattlePlayer>> m_players;
    std::unordered_map<dx::di::PlayerId, std::shared_ptr<BattlePlayer>> m_alivePlayers;
private: // private function
public: // ctor/dtor
    BattlePlayerManager(const std::unordered_map<dx::di::PlayerId, std::shared_ptr<BattlePlayerDesc>>& descs);
};


}
}

