#pragma once
#include "PlayerId.hpp"
#include "RelativePosition.hpp"
#include "Palette.hpp"

namespace dx {
namespace cmp {
class HotReloadableParameters;
}
namespace ui {
class IUIObject {
public:
    virtual void update() = 0;
    virtual void draw() const = 0;
protected:
    IUIObject() = default;
    virtual ~IUIObject() = default;
};

}
}

namespace kanji {
namespace battle {
class IBattleManager;
class BattlePlayer;
}
namespace ui {

class IHolderUI : public dx::ui::IUIObject {
public:
protected:
    IHolderUI() = default;
    virtual ~IHolderUI() = default;
};

class HolderUI : public IHolderUI {
public: // static_const/enum
public: // static
    const s3d::String m_toml_key = U"battle.ui.object.holder";
    std::shared_ptr<dx::cmp::HotReloadableParameters> m_params;
public: // public function
    void update() override;
    void draw() const override;
private: // field
    dx::ui::RelativePosition m_pos;
    const int m_player_index; // 参加者のうち何人目か (Id若い順, 0 origin)
    const int m_player_num; // 参加者数
    const std::shared_ptr<battle::BattlePlayer> m_player;
    dx::ui::ColorPalette m_colors;
    dx::ui::FontPalette m_fonts;
private: // private function
    void drawCircle(const s3d::String& key, const int charaIndex) const;
    void drawRadical() const;
public: // ctor/dtor
    HolderUI(int player_index, int player_num, const std::shared_ptr<battle::BattlePlayer>& player);
};


class BattleUIManager {
public: // static_const/enum
public: // static
public: // public function
    void update();
    void draw() const;
private: // field
    const battle::IBattleManager* const m_battle_manager;
    std::unordered_map<dx::di::PlayerId, std::shared_ptr<IHolderUI>> m_holders;
private: // private function
public: // ctor/dtor
    BattleUIManager(const battle::IBattleManager* battle_manager);
};


}
}

