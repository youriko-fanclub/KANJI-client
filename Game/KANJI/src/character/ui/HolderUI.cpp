#include "HolderUI.hpp"
#include <Siv3D/FormatLiteral.hpp>
#include <Siv3D/Circular.hpp>
#include <Siv3D/MathConstants.hpp>
#include "PlayerId.hpp"
#include "BattlePlayer.hpp"
#include "ParameterizedCharacter.hpp"
#include "TomlAsset.hpp"

using namespace s3d::Literals::FormatLiterals;
using s3d::operator""_deg;

namespace {

std::unique_ptr<s3d::Polygon> createAbilityIndicator(const std::unique_ptr<kanji::chara::IAbility>& ability) {
    const float angle = s3d::Math::Constants::TwoPiF / 5.f;
    const float factor = 0.3f;
    return std::unique_ptr<s3d::Polygon>(new s3d::Polygon({
        s3d::Circular(factor * ability->attack (), angle * 0).toVec2(),
        s3d::Circular(factor * ability->defence(), angle * 1).toVec2(),
        s3d::Circular(factor * ability->speed  (), angle * 2).toVec2(),
        s3d::Circular(factor * ability->jump   (), angle * 3).toVec2(),
        s3d::Circular(factor * ability->weight (), angle * 4).toVec2()
    }));
}

}

namespace kanji {
namespace ui {

/* ---------- HolderUI ---------- */

// static ----------------------------------------
// public function -------------------------------
void HolderUI::update() {
    const auto player_nums = s3d::ToString(m_player_num);
    m_pos.set(
        dx::toml::vec2(m_toml[m_toml_key + U"base.center" + player_nums])
            + s3d::Vec2(m_player_index * dx::toml::getInt(m_toml[m_toml_key + U"interval" + player_nums]), 0),
        m_toml[dx::toml::TomlKey(U"battle.ui.base.scale")].get<float>());
    
    for (const auto position : dx::denum::elems<CirclePosition>()) {
        const auto key = dx::denum::toLower(position);
        const auto key_circle = m_toml_key + U"circle" + key;
        // circle
        m_circles.insert_or_assign(position, s3d::Circle(
            m_pos.offset(dx::toml::vec2(m_toml[key_circle + U"center"])),
            m_pos.size(m_toml[key_circle + U"r"].get<int>())));

        // font
        const int fontsize = m_toml[key_circle + U"font.size"].get<int>();
        if (!m_fonts.contains(key) || m_fonts.at(key).fontSize() != fontsize) {
            m_fonts.insert(key, dx::toml::font(m_toml[key_circle + U"font"]));
        }
    }
    {
        const auto key = U"radical";
        const int fontsize = m_toml[m_toml_key + key + U"font.size"].get<int>();
        if (!m_fonts.contains(key) || m_fonts.at(key).fontSize() != fontsize) {
            m_fonts.insert(key, dx::toml::font(m_toml[m_toml_key + key + U"font"]));
        }
    }
}

// protected function ------------------------------
void HolderUI::drawImpl() const {
    s3d::RectF frame(
        s3d::Arg::center(m_pos.center()),
        m_pos.size(dx::toml::size(m_toml[m_toml_key + U"base.size"])));
    frame.draw(m_colors.at(U"Base"));
    
    drawCircle(CirclePosition::Above, 0);
    drawCircle(CirclePosition::Right, 1);
    drawCircle(CirclePosition::Left, 2);
    drawRadical();
}

// private function ------------------------------
void HolderUI::drawCircle(const CirclePosition position, const int charaIndex) const {
    const auto& circle = m_circles.at(position);
    circle.draw(m_colors.at(U"Highlight"));
    
    if (position == CirclePosition::Above) {
        drawPolygon();
    }
    
    const auto key = dx::denum::toLower(position);
    const auto& chara = m_player->characters().at(charaIndex);
    m_fonts.at(key)(chara->chara())
        .draw(s3d::Arg::center = circle.center, s3d::Palette::Black);
    s3d::Circle damage(circle.center, circle.r * (1 - chara->hpRate()));
    damage.draw(m_colors.at(U"DamageFill"));
}
void HolderUI::drawRadical() const {
    s3d::RectF radical(
        s3d::Arg::center(m_pos.offset(dx::toml::vec2(m_toml[m_toml_key + U"radical.base.center"]))),
        m_pos.size(dx::toml::size(m_toml[m_toml_key + U"radical.base.size"])));
    radical.draw(m_colors.at(U"Gray"));
    
    if (m_player->hasRadical()) {
        m_fonts.at(U"radical")(m_player->radical()->chara())
            .draw(s3d::Arg::center = radical.center(), s3d::Palette::White);
    }
}
void HolderUI::drawPolygon() const {
    m_ability->draw(m_circles.at(CirclePosition::Above).center, dx::di::Id::ToColorLight(m_player->pid()));
    m_default_ability->drawFrame(m_circles.at(CirclePosition::Above).center, 2.0, dx::di::Id::ToColorDark(m_player->pid()));
}

// ctor/dtor -------------------------------------
HolderUI::HolderUI(int player_index, int player_num, const std::shared_ptr<battle::BattlePlayer>& player) :
m_player_index(player_index),
m_player_num(player_num),
m_toml_key(U"battle.ui.object.holder"),
m_toml(U"Battle"),
m_player(player) {
    dx::toml::TomlKey key(m_toml_key);
    key += U"color";
    key += dx::denum::toString<dx::di::PlayerId>(m_player->pid());

    m_colors.insert(U"Base"      , dx::toml::colorF(m_toml[key + U"base"]));
    m_colors.insert(U"Gray"      , dx::toml::colorF(m_toml[key + U"radical"]));
    m_colors.insert(U"Highlight" , dx::toml::colorF(m_toml[key + U"circle"]));
    m_colors.insert(U"DamageFill", dx::toml::colorF(m_toml[key + U"damage"]));
    
    m_ability = createAbilityIndicator(m_player->activeCharacter()->ability());
    m_default_ability = createAbilityIndicator(m_player->activeCharacter()->initialAbility());
    
    update();
}

}
}

using CirclePosition = kanji::ui::HolderUI::CirclePosition;

namespace dx {
namespace denum {

template <>
s3d::Array<CirclePosition> elems() {
    return {
        CirclePosition::Above,
        CirclePosition::Left,
        CirclePosition::Right,
    };
}
template <>
s3d::String toLower(CirclePosition value) {
    switch (value) {
    case CirclePosition::Above: return U"above";
    case CirclePosition::Left: return U"left";
    case CirclePosition::Right: return U"right";
    }
}

}
}
