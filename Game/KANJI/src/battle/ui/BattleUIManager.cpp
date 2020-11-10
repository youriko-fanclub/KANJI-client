#include "BattleUIManager.hpp"
#include <Siv3D/Vector2D.hpp>
#include <Siv3D/Circle.hpp>
#include <Siv3D/Rectangle.hpp>
#include <Siv3D/Color.hpp>
#include <Siv3D/FormatLiteral.hpp>
#include <Siv3D/FontAsset.hpp>
#include "HotReloadManager.hpp"
#include "BattleManager.hpp"
#include "BattlePlayerManager.hpp"
#include "BattlePlayer.hpp"

using namespace s3d::Literals::FormatLiterals;

namespace kanji {
namespace ui {

struct RelativePosition {
public:
    const s3d::Vec2 center;
    const float scale;
public:
    s3d::Vec2 offset(float x, float y) const {
        return center + s3d::Vec2(x, y) * scale;
    }
    s3d::Vec2 offset(const s3d::Vec2 vec) const {
        return center + vec * scale;
    }
    s3d::Size size(float w, float h) const {
        return s3d::Size(
            static_cast<int>(w * scale),
            static_cast<int>(h * scale));
    }
    s3d::Size size(const s3d::Size size) const {
        return s3d::Size(
            static_cast<int>(size.x * scale),
            static_cast<int>(size.y * scale));
    }
    float size(float x) const {
        return x * scale;
    }
};

/* ---------- BattleUIManager ---------- */

// static ----------------------------------------
// public function -------------------------------
void BattleUIManager::update() {
    const s3d::String holder = U"battle.ui.object.holder";
    {
        const int fontsize = m_params->get<int>(holder + U".circle.above.font.size");
        if (!m_font_holder_above || m_font_holder_above->fontSize() != fontsize) {
            m_font_holder_above = m_params->getFontPtr(holder + U".circle.above.font");
        }
    }
    {
        // とりあえず下段の2つはフォント同じ前提、代表してleftを読み出す
        const int fontsize = m_params->get<int>(holder + U".circle.left.font.size");
        if (!m_font_holder_bottom || m_font_holder_bottom->fontSize() != fontsize) {
            m_font_holder_bottom = m_params->getFontPtr(holder + U".circle.left.font");
        }
    }
}

void BattleUIManager::draw() const {
    const auto& players = m_battle_manager->playerMgr()->players();
    const int player_num = static_cast<int>(players.size());
    for (int i = 0; const auto& player : players) {
        drawHolder(i, player_num, player.second);
        ++i;
    }
}
void BattleUIManager::drawHolder(int index, int player_num, const std::shared_ptr<battle::BattlePlayer>& player) const {
    
    const auto pid_str = dx::denum::toString<dx::di::PlayerId>(player->pid());
    
    const s3d::String holder = U"battle.ui.object.holder";
    s3d::ColorF base(m_params->getColorF(holder + U".color.{}.base"_fmt(pid_str)));
    s3d::ColorF gray(m_params->getColorF(
        holder + U".color.{}.radical"_fmt(pid_str)));
    s3d::ColorF highlight(m_params->getColorF(
        holder + U".color.{}.circle"_fmt(pid_str)));

    RelativePosition pos = {
        .center = m_params->getVec2(holder + U".base.center.{}"_fmt(player_num))
            + s3d::Vec2(index * m_params->get<int>(holder + U".interval.{}"_fmt(player_num)), 0),
        .scale = m_params->get<float>(U"battle.ui.base.scale"),
    };
    s3d::RectF frame(
        s3d::Arg::center(pos.center),
        pos.size(m_params->getSize(holder + U".base.size")));
    frame.draw(base);
    s3d::Circle circle_above(
        pos.offset(m_params->getVec2(holder + U".circle.above.center")),
        pos.size(m_params->get<int>(holder + U".circle.above.r")));
    circle_above.draw(highlight);
    s3d::Circle circle_left(
        pos.offset(m_params->getVec2(holder + U".circle.left.center")),
        pos.size(m_params->get<int>(holder + U".circle.left.r")));
    circle_left.draw(highlight);
    s3d::Circle circle_right(
        pos.offset(m_params->getVec2(holder + U".circle.right.center")),
        pos.size(m_params->get<int>(holder + U".circle.right.r")));
    circle_right.draw(highlight);
    s3d::RectF radical(
        s3d::Arg::center(pos.offset(m_params->getVec2(holder + U".radical.base.center"))),
        pos.size(m_params->getSize(holder + U".radical.base.size")));
    radical.draw(gray);
    
    if (m_font_holder_above) {
        (*m_font_holder_above)(U"山").draw(s3d::Arg::center = circle_above.center, s3d::Palette::Black);
    }
    if (m_font_holder_bottom) {
        (*m_font_holder_bottom)(U"百").draw(s3d::Arg::center = circle_left.center, s3d::Palette::Black);
        (*m_font_holder_bottom)(U"合").draw(s3d::Arg::center = circle_right.center, s3d::Palette::Black);
    }

}
// private function ------------------------------
// ctor/dtor -------------------------------------
BattleUIManager::BattleUIManager(const battle::IBattleManager* battle_manager) :
m_battle_manager(battle_manager),
m_params(dx::cmp::HotReloadManager::createParamsWithLoad(U"Battle")) {}


}
}
