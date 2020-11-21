#pragma once
#include "RelativePosition.hpp"
#include "Palette.hpp"
#include "UIComponent.hpp"

namespace dx {
namespace cmp {
class HotReloadableParameters;
}
}

namespace kanji {
namespace battle {
class BattlePlayer;
}
namespace ui {

class IHolderUI : public dx::ui::UIComponent {
public:
    virtual void update() = 0;
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
protected: // protected function
    void drawImpl() const override;
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

}
}
