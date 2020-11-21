#pragma once
#include <vector>
#include "PlayerId.hpp"

namespace kanji {
namespace chara {
class IParameterizedCharacter;
}
namespace battle {
class BattlePlayerDesc;

class BattlePlayer {
public: // static_const/enum
    using Radical = s3d::String;
public: // static
public: // public function
    dx::di::PlayerId pid() const { return m_pid; }
    std::shared_ptr<chara::IParameterizedCharacter> activeCharacter() {
        if (0 <= m_activeIndex && m_activeIndex < m_characters.size()) {
            return m_characters.at(m_activeIndex);
        }
        else { return nullptr; }
    }
    const std::vector<std::shared_ptr<chara::IParameterizedCharacter>>& characters() const {
        return m_characters;
    }
    bool hasRadical() const { return m_radical != U""; }
    const Radical& radical() const { return m_radical; }
    void setRadical(const Radical& value) { m_radical = value; }
    
private: // field
    dx::di::PlayerId m_pid;
    int m_activeIndex;
    std::vector<std::shared_ptr<chara::IParameterizedCharacter>> m_characters;
    Radical m_radical;
private: // private function
public: // ctor/dtor
    BattlePlayer(dx::di::PlayerId pid, const std::shared_ptr<BattlePlayerDesc>& desc);
};


}
}
