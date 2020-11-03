#pragma once
#include <memory>

namespace kanji {
namespace battle {
    class BattleDesc;
    class BattleResultDesc;
}

namespace seq {


// 各Scene間で共有するデータ
class DomainGameData {
public: // static_const/enum
public: // static
public: // public function
    const std::shared_ptr<battle::BattleDesc>& battleDesc() {
        return m_battle_desc;
    }
    const std::shared_ptr<battle::BattleResultDesc>& battleResultDesc() {
        return m_battle_result_desc;
    }
    void setBattleDesc(const std::shared_ptr<battle::BattleDesc>& value) {
        m_battle_desc = value;
    }
    void setBattleResultDesc(const std::shared_ptr<battle::BattleResultDesc>& value) {
        m_battle_result_desc = value;
    }
private: // field
    std::shared_ptr<battle::BattleDesc> m_battle_desc;
    std::shared_ptr<battle::BattleResultDesc> m_battle_result_desc;
private: // private function
public: // ctor/dtor
};


}
}
