#pragma once
#include <Siv3D/HashTable.hpp>
#include "PlayerId.hpp"
#include "IDs.hpp"

namespace kanji {
namespace chara {
    class IParameterizedCharacter;
}
namespace battle {

struct BattlePlayerDesc {
public: // public function
    const s3d::Array<std::shared_ptr<chara::IParameterizedCharacter>>& characters() const {
        return m_characters;
    }
    s3d::Array<std::shared_ptr<chara::IParameterizedCharacter>>& characters() {
        return m_characters;
    }
    s3d::String toString() const;
private: // field
    s3d::Array<std::shared_ptr<chara::IParameterizedCharacter>> m_characters;
};

class BattleDesc {
public: // static_const/enum
public: // static
public: // public function
    const std::shared_ptr<BattlePlayerDesc>& playerDesc(dx::di::PlayerId id) { return m_players.at(id); }
    // const std::shared_ptr<BattlePlayerDesc>& playerDesc(dx::di::PlayerId id) const { return m_players.at(id); }
    const s3d::HashTable<dx::di::PlayerId, std::shared_ptr<BattlePlayerDesc>>& playerDescs() const {
        return m_players;
    }
    void setPlayerDesc(dx::di::PlayerId id, const std::shared_ptr<BattlePlayerDesc>& value);
    int timeLimitSec() const { return m_timeLimit_sec; }
    void setTimeLimitSec(int value) { m_timeLimit_sec = value; }
    StageID stageId() const { return m_stage_id; }
    void setStageId(StageID value) { m_stage_id = value; }
    bool readyToBattle() const;
    void dump() const;
private: // field
    s3d::HashTable<dx::di::PlayerId, std::shared_ptr<BattlePlayerDesc>> m_players;
    int m_timeLimit_sec;
    StageID m_stage_id;
private: // private function
public: // ctor/dtor
    BattleDesc() : m_stage_id(0) {}
};

class BattleResultDesc {
public: // static_const/enum
public: // static
public: // public function
    s3d::Array<dx::di::PlayerId>* ranking() { return &m_ranking; }
private: // field
    // 順位低い順
    s3d::Array<dx::di::PlayerId> m_ranking;
private: // private function
public: // ctor/dtor
};


}
}

