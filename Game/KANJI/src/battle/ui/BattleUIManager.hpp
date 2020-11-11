#pragma once
#include "PlayerId.hpp"

namespace dx {
namespace cmp {
class HotReloadableParameters;
}
}

namespace kanji {
namespace battle {
class IBattleManager;
class BattlePlayer;
}
namespace ui {

class BattleUIManager {
public: // static_const/enum
public: // static
public: // public function
    void update();
    void draw() const;
private: // field
    const battle::IBattleManager* const m_battle_manager;
    // holder
    std::shared_ptr<dx::cmp::HotReloadableParameters> m_params;
    std::shared_ptr<s3d::Font> m_font_holder_above;
    std::shared_ptr<s3d::Font> m_font_holder_bottom;
    std::shared_ptr<s3d::Font> m_font_holder_radical;
private: // private function
    // index : 参加者のうちId若い順、 0 origin
    // player_num : 参加者数
    // e.g. 参加者={ 1P, 3P, 4P} : index1=3P, player_num=3
    void drawHolder(int index, int player_num, const std::shared_ptr<battle::BattlePlayer>& player) const;
public: // ctor/dtor
    BattleUIManager(const battle::IBattleManager* battle_manager);
};


}
}

