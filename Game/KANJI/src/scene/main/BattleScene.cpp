#include "BattleScene.hpp"
#include <Siv3D/TOMLReader.hpp>
#include "Input.hpp"
#include "Misc.hpp"
#include "HotReloadManager.hpp"

namespace kanji {
namespace seq {

/* ---------- BattleScene ---------- */

// static ----------------------------------------
// public function -------------------------------
void BattleScene::update() {
    param->update();
    // 物理演算の精度
    static constexpr int32 velocityIterations = 12;
    static constexpr int32 positionIterations = 4;
    
    // (y > 10) まで落下した P2Body は削除
    m_bodies.remove_if([](const P2Body& body) { return body.getPos().y > 10; });

    // 物理演算のワールドを更新
    m_world.update(true ? (1.0 / 60.0) : Scene::DeltaTime(), velocityIterations, positionIterations);
        

    m_camera.update();
    {
        // 2D カメラの設定から Transformer2D を作成・適用
        const auto t = m_camera.createTransformer();
        
        if (MouseL.down()) {
            // クリックした場所にボールを作成
            m_bodies << m_world.createCircle(Cursor::PosF(), 0.5);
        }
        const auto& input = dx::di::Input::get(dx::di::GamePadId::_1P);
        s3d::Vec2 velocity(
            param->force_horizontal * input.arrowL().x,
            input.dpad().up().down() || input.buttons().b().down() ? -param->force_jump : 0.0);
        // m_chara.applyForce(force);
        const auto& v = m_chara.getVelocity();
        if (dx::misc::approximatelyZero(velocity)) {
            velocity.x = v.x * param->air_resistance;
            velocity.y = v.y;
        }
        else {
            if (dx::misc::approximatelyZero(velocity.x)) {
                velocity.x = v.x;
            }
            if (dx::misc::approximatelyZero(velocity.y)) {
                velocity.y = v.y;
            }
            velocity.x *= param->air_resistance;
        }
        m_chara.setVelocity(velocity);
    }
}
void BattleScene::draw() const {
    {
        // 2D カメラの設定から Transformer2D を作成・適用
        const auto t = m_camera.createTransformer();
        
        // 床を描画
        m_floor.draw(Palette::Skyblue);
        m_ceiling.draw(Palette::Skyblue);
        m_wall_left.draw(Palette::Skyblue);
        m_wall_right.draw(Palette::Skyblue);
        
        // 物体を描画
        for (const auto& body : m_bodies) {
            body.draw(HSV(body.id() * 10, 0.7, 0.9));
        }
        m_chara.draw();
    }
    m_camera.draw();
}

// private function ------------------------------
// ctor/dtor -------------------------------------
BattleScene::BattleScene(const InitData& init) :
    IScene(init),
    param(dx::cmp::HotReloadManager::createParams<param::CharaPhysics>()),
    m_start(
        Rect(Arg::center = Scene::Center().movedBy(65, 170), 300, 60), DrawableText(FontAsset(U"Menu"), U"はじめる"),
        Transition(0.4s, 0.2s)),
    m_camera(Vec2(0, -8), 20.0, s3d::Camera2DParameters::MouseOnly()),
    m_world(9.8),
    m_chara     (m_world.createRect      (Vec2(  0, -5), SizeF(2, 3),         P2Material(1.0, 0.0, param->chara_friction))),
    m_floor     (m_world.createStaticLine(Vec2(  0,  0), Line(-25, 0, 25, 0), P2Material(1.0, 0.0, param->floor_friction))),
    m_ceiling   (m_world.createStaticLine(Vec2(  0,-25), Line(-25, 0, 25, 0), P2Material(1.0, 0.0, param->ceiling_friction))),
    m_wall_left (m_world.createStaticLine(Vec2(-25,  0), Line(0, -25, 0, 10), P2Material(1.0, 0.0, param->wall_friction))),
    m_wall_right(m_world.createStaticLine(Vec2( 25,  0), Line(0, -25, 0, 10), P2Material(1.0, 0.0, param->wall_friction)))
{
    m_chara.setFixedRotation(true);
    // 物理演算のワールド更新に 60FPS の定数時間を使う場合は true, 実時間を使う場合 false
    constexpr bool useConstantDeltaTime = true;
    if (useConstantDeltaTime) { // フレームレート上限を 60 FPS に
        Graphics::SetTargetFrameRateHz(60);
    }

}

}
}
