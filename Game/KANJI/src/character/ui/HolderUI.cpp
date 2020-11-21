#include "HolderUI.hpp"
#include <Siv3D/Circle.hpp>
#include <Siv3D/FormatLiteral.hpp>
#include "HotReloadManager.hpp"
#include "PlayerId.hpp"
#include "BattlePlayer.hpp"
#include "ParameterizedCharacter.hpp"

using namespace s3d::Literals::FormatLiterals;

namespace kanji {
namespace ui {

/* ---------- HolderUI ---------- */

// static ----------------------------------------
// public function -------------------------------
void HolderUI::update() {
    m_pos.set(
        m_params->getVec2(m_toml_key + U".base.center.{}"_fmt(m_player_num))
            + s3d::Vec2(m_player_index * m_params->get<int>(m_toml_key + U".interval.{}"_fmt(m_player_num)), 0),
        m_params->get<float>(U"battle.ui.base.scale"));
    for (const auto& key : { U"above", U"left", U"right" }) {
        const int fontsize = m_params->get<int>(m_toml_key + U".circle.{}.font.size"_fmt(key));
        if (!m_fonts.contains(key) || m_fonts.at(key).fontSize() != fontsize) {
            m_fonts.insert(key, m_params->getFont(m_toml_key + U".circle.{}.font"_fmt(key)));
        }
    }
    {
        const auto key = U"radical";
        const int fontsize = m_params->get<int>(m_toml_key + U".{}.font.size"_fmt(key));
        if (!m_fonts.contains(key) || m_fonts.at(key).fontSize() != fontsize) {
            m_fonts.insert(key, m_params->getFont(m_toml_key + U".{}.font"_fmt(key)));
        }
    }
}

// protected function ------------------------------
void HolderUI::drawImpl() const {
    s3d::RectF frame(
        s3d::Arg::center(m_pos.center()),
        m_pos.size(m_params->getSize(m_toml_key + U".base.size")));
    frame.draw(m_colors.at(U"Base"));
    
    drawCircle(U"above", 0);
    drawCircle(U"left", 1);
    drawCircle(U"right", 2);
    drawRadical();
}

// private function ------------------------------
void HolderUI::drawCircle(const s3d::String& key, const int charaIndex) const {
    s3d::Circle circle(
        m_pos.offset(m_params->getVec2(m_toml_key + U".circle.{}.center"_fmt(key))),
        m_pos.size(m_params->get<int>(m_toml_key + U".circle.{}.r"_fmt(key))));
    circle.draw(m_colors.at(U"Highlight"));
    
    const auto& chara = m_player->characters().at(charaIndex);
    m_fonts.at(key)(chara->kanji().kanji)
        .draw(s3d::Arg::center = circle.center, s3d::Palette::Black);
    s3d::Circle damage(circle.center, circle.r * (1 - chara->hpRate()));
    damage.draw(m_colors.at(U"DamageFill"));
}
void HolderUI::drawRadical() const {
    s3d::RectF radical(
        s3d::Arg::center(m_pos.offset(m_params->getVec2(m_toml_key + U".radical.base.center"))),
        m_pos.size(m_params->getSize(m_toml_key + U".radical.base.size")));
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
m_params(dx::cmp::HotReloadManager::createParamsWithLoad(U"Battle")),
m_player(player) {
    const auto pid_str = dx::denum::toString<dx::di::PlayerId>(m_player->pid());
    m_colors.insert(
        U"Base", m_params->getColorF(m_toml_key + U".color.{}.base"_fmt(pid_str)));
    m_colors.insert(
        U"Gray", m_params->getColorF(m_toml_key + U".color.{}.radical"_fmt(pid_str)));
    m_colors.insert(
        U"Highlight", m_params->getColorF(m_toml_key + U".color.{}.circle"_fmt(pid_str)));
    m_colors.insert(
        U"DamageFill", m_params->getColorF(m_toml_key + U".color.{}.damage"_fmt(pid_str)));
}

}
}
