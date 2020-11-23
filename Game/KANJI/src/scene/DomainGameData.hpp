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
    const std::shared_ptr<battle::BattleDesc>& battleDesc();
    const std::shared_ptr<battle::BattleResultDesc>& battleResultDesc();
    void setBattleDesc(const std::shared_ptr<battle::BattleDesc>& value);
    void setBattleResultDesc(const std::shared_ptr<battle::BattleResultDesc>& value);
    bool readyToBattle() const;
    void clearBattleData() { m_battle_desc.reset(); }
private: // field
    std::shared_ptr<battle::BattleDesc> m_battle_desc = nullptr;
    std::shared_ptr<battle::BattleResultDesc> m_battle_result_desc = nullptr;
private: // private function
public: // ctor/dtor
};


}
}
