#include "BattleUIManager.hpp"
#include <Siv3D/Vector2D.hpp>
#include <Siv3D/Circle.hpp>
#include <Siv3D/Rectangle.hpp>
#include <Siv3D/Color.hpp>
#include "BattleManager.hpp"
#include "HotReloadManager.hpp"

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
void BattleUIManager::draw() const {
    for (int i = 0; i < 4; ++i) {
        drawHolder(i, 4, dx::di::PlayerId::_1P);
    }
}
void BattleUIManager::drawHolder(int index, int player_num, dx::di::PlayerId pid) const {
    
    static auto param = dx::cmp::HotReloadManager::createParamsWithLoad(U"Battle");
    { // Holder
        s3d::ColorF base(0.86, 0.47, 0.35);
        s3d::ColorF gray(0.30, 0.30, 0.30);
        s3d::ColorF highlight(0.96, 0.82, 0.57);
        s3d::ColorF red(1.00, 0.30, 0.30);
        
        RelativePosition pos = {
            .center = param->getVec2(U"battle.ui.object.holder.base.center")
                + s3d::Vec2(index * param->get<int>(U"battle.ui.object.holder.interval"), 0),
            .scale = param->get<float>(U"battle.ui.base.scale"),
        };
        const s3d::String holder = U"battle.ui.object.holder";
        s3d::RectF frame(
            s3d::Arg::center(pos.center),
            pos.size(param->getSize(holder + U".base.size")));
        frame.draw(base);
        s3d::Circle circle_above(
            pos.offset(param->getVec2(holder + U".circle.above.center")),
            pos.size(param->get<int>(holder + U".circle.above.r")));
        circle_above.draw(highlight);
        s3d::Circle circle_left(
            pos.offset(param->getVec2(holder + U".circle.left.center")),
            pos.size(param->get<int>(holder + U".circle.left.r")));
        circle_left.draw(highlight);
        s3d::Circle circle_right(
            pos.offset(param->getVec2(holder + U".circle.right.center")),
            pos.size(param->get<int>(holder + U".circle.right.r")));
        circle_right.draw(highlight);
        s3d::RectF radical(
            s3d::Arg::center(pos.offset(param->getVec2(holder + U".radical.base.center"))),
            pos.size(param->getSize(holder + U".radical.base.size")));
        radical.draw(gray);
    }

}
// private function ------------------------------
// ctor/dtor -------------------------------------


}
}
