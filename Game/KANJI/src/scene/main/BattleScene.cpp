#include "BattleScene.hpp"

namespace kanji {
namespace seq {


/* ---------- BattleScene ---------- */

// static ----------------------------------------
// public function -------------------------------
void BattleScene::update() {
    // 物理演算の精度
    static constexpr int32 velocityIterations = 12;
    static constexpr int32 positionIterations = 4;
    
    // (y > 10) まで落下した P2Body は削除
    bodies.remove_if([](const P2Body& body) { return body.getPos().y > 10; });

    // 物理演算のワールドを更新
    world.update(true ? (1.0 / 60.0) : Scene::DeltaTime(), velocityIterations, positionIterations);
        

    camera.update();
    {
        // 2D カメラの設定から Transformer2D を作成・適用
        const auto t = camera.createTransformer();
        
        if (MouseL.down()) {
            // クリックした場所にボールを作成
            bodies << world.createCircle(Cursor::PosF(), 0.5);
        }
        constexpr float force_factor = 100;
        float force_x = force_factor
            * (KeyH.pressed() ? -1
            : KeyL.pressed() ? 1
            : 0);
        m_chara.applyForce(Vec2(force_x, 0));
    }
}
void BattleScene::draw() const {
    {
        // 2D カメラの設定から Transformer2D を作成・適用
        const auto t = camera.createTransformer();
        
        // 床を描画
        line.draw(Palette::Skyblue);
        
        // 物体を描画
        for (const auto& body : bodies) {
            body.draw(HSV(body.id() * 10, 0.7, 0.9));
        }
        m_chara.draw();
    }
    camera.draw();
}

// private function ------------------------------
// ctor/dtor -------------------------------------
BattleScene::BattleScene(const InitData& init) :
    IScene(init),
    m_start(
        Rect(Arg::center = Scene::Center().movedBy(65, 170), 300, 60), DrawableText(FontAsset(U"Menu"), U"はじめる"),
        Transition(0.4s, 0.2s)),
    camera(Vec2(0, -8), 20.0),
    world(9.8),
    m_chara(world.createRect(Vec2(0, -5), SizeF(2, 3))),
    line(world.createStaticLine(Vec2(0, 0), Line(-16, 0, 16, 0)))
{
    // 物理演算のワールド更新に 60FPS の定数時間を使う場合は true, 実時間を使う場合 false
    constexpr bool useConstantDeltaTime = true;
    if (useConstantDeltaTime) { // フレームレート上限を 60 FPS に
        Graphics::SetTargetFrameRateHz(60);
    }

}

}
}
