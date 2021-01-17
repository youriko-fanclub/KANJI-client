#pragma once
#include <Siv3D/Circle.hpp>
#include <Siv3D/Polygon.hpp>
#include "Enum.hpp"
#include "RelativePosition.hpp"
#include "Palette.hpp"
#include "UIComponent.hpp"
#include "TomlAsset.hpp"

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
    enum class CirclePosition : int {
        Above = 0, Left = 1, Right = 2,
    };
public: // static
    const dx::toml::TomlKey m_toml_key;
    dx::toml::TomlAsset m_toml;
public: // public function
    void update() override;
protected: // protected function
    void drawImpl() const override;
private: // field
    dx::ui::RelativePosition m_pos;
    const int m_player_index; // 参加者のうち何人目か (Id若い順, 0 origin)
    const int m_player_num; // 参加者数
    const std::shared_ptr<battle::BattlePlayer> m_player;
    std::unordered_map<CirclePosition, s3d::Circle> m_circles;
    dx::ui::ColorPalette m_colors;
    dx::ui::FontPalette m_fonts;
    std::unique_ptr<s3d::Polygon> m_default_ability;
    std::unique_ptr<s3d::Polygon> m_ability;
private: // private function
    void drawCircle(CirclePosition position, int charaIndex) const;
    void drawRadical() const;
    void drawPolygon() const;
public: // ctor/dtor
    HolderUI(int player_index, int player_num, const std::shared_ptr<battle::BattlePlayer>& player);
};

}
}

namespace dx {
namespace denum {

template <>
std::vector<kanji::ui::HolderUI::CirclePosition> elems();
template <>
s3d::String toLower(kanji::ui::HolderUI::CirclePosition value);

}
}
