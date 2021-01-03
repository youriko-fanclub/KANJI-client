#include "HolderUI.hpp"
#include <Siv3D/FormatLiteral.hpp>
#include "HotReloadManager.hpp"
#include "PlayerId.hpp"
#include "BattlePlayer.hpp"
#include "ParameterizedCharacter.hpp"
#include "TomlAsset.hpp"

using namespace s3d::Literals::FormatLiterals;

namespace kanji {
namespace ui {

/* ---------- HolderUI ---------- */

// static ----------------------------------------
// public function -------------------------------
void HolderUI::update() {
    const auto player_nums = s3d::ToString(m_player_num);
    m_pos.set(
        m_toml.getVec2(m_toml_key + U"base.center" + player_nums)
            + s3d::Vec2(m_player_index * m_toml[m_toml_key + U"interval" + player_nums].get<int>(), 0),
        m_toml[dx::cmp::TomlKey(U"battle.ui.base.scale")].get<float>());
    
    for (const auto position : dx::denum::elems<CirclePosition>()) {
        const auto key = dx::denum::toLower(position);
        const auto key_circle = m_toml_key + U"circle" + key;
        // circle
        m_circles.insert_or_assign(position, s3d::Circle(
            m_pos.offset(m_toml.getVec2(key_circle + U"center")),
            m_pos.size(m_toml[key_circle + U"r"].get<int>())));

        // font
        const int fontsize = m_toml[key_circle + U"font.size"].get<int>();
        if (!m_fonts.contains(key) || m_fonts.at(key).fontSize() != fontsize) {
            m_fonts.insert(key, m_toml.getFont(key_circle + U"font"));
        }
    }
    {
        const auto key = U"radical";
        const int fontsize = m_toml[m_toml_key + key + U"font.size"].get<int>();
        if (!m_fonts.contains(key) || m_fonts.at(key).fontSize() != fontsize) {
            m_fonts.insert(key, m_toml.getFont(m_toml_key + key + U"font"));
        }
    }
}

// protected function ------------------------------
void HolderUI::drawImpl() const {
    s3d::RectF frame(
        s3d::Arg::center(m_pos.center()),
        m_pos.size(m_toml.getSize(m_toml_key + U"base.size")));
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
    
    const auto key = dx::denum::toLower(position);
    const auto& chara = m_player->characters().at(charaIndex);
    m_fonts.at(key)(chara->kanji().kanji)
        .draw(s3d::Arg::center = circle.center, s3d::Palette::Black);
    s3d::Circle damage(circle.center, circle.r * (1 - chara->hpRate()));
    damage.draw(m_colors.at(U"DamageFill"));
}
void HolderUI::drawRadical() const {
    s3d::RectF radical(
        s3d::Arg::center(m_pos.offset(m_toml.getVec2(m_toml_key + U"radical.base.center"))),
        m_pos.size(m_toml.getSize(m_toml_key + U"radical.base.size")));
    radical.draw(m_colors.at(U"Gray"));
    
    if (m_player->hasRadical()) {
        m_fonts.at(U"radical")(m_player->radical())
            .draw(s3d::Arg::center = radical.center(), s3d::Palette::White);
    }
}

// ctor/dtor -------------------------------------
HolderUI::HolderUI(int player_index, int player_num, const std::shared_ptr<battle::BattlePlayer>& player) :
m_player_index(player_index),
m_player_num(player_num),
m_toml_key(U"battle.ui.object.holder"),
m_toml(U"Battle"),
m_player(player) {
    dx::cmp::TomlKey key(m_toml_key);
    key += U"color";
    key += dx::denum::toString<dx::di::PlayerId>(m_player->pid());

    m_colors.insert(U"Base", m_toml.getColorF(key + U"base"));
    m_colors.insert(U"Gray", m_toml.getColorF(key + U"radical"));
    m_colors.insert(U"Highlight", m_toml.getColorF(key + U"circle"));
    m_colors.insert(U"DamageFill", m_toml.getColorF(key + U"damage"));
    update();
}

}
}

using CirclePosition = kanji::ui::HolderUI::CirclePosition;

namespace dx {
namespace denum {

template <>
std::vector<CirclePosition> elems() {
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
