#pragma once

#include "SceneState.hpp"
#include "UIComponent.hpp"
#include "CharaPhysicsParameters.hpp"

namespace kanji {
namespace battle {
    class IBattleManager;
}
namespace ui {
    class BattleUIManager;
}
namespace seq {


// タイトルシーン
class BattleScene : public KanjiScene {
public: // static_const/enum
public: // static
public: // public function
    void initialize();
    void update() override;
    void updateLegacy(); // 近いうちに消す
    void draw() const override;
    void drawLegacy() const; // 近いうちに消す
private: // field
    std::shared_ptr<battle::IBattleManager> m_mgr;
    std::shared_ptr<ui::BattleUIManager> m_ui;
    // ↓ここから下は試し書きの無法地帯
    std::shared_ptr<param::CharaPhysics> param;
    std::pair<s3d::DrawableText, s3d::DrawableText> m_title;
    dui::Button m_start;
    
    // 2Dカメラ
    Camera2D m_camera;
    // 物理演算用のワールド
    P2World m_world;
    // 物体
    P2Body m_chara;
    Array<P2Body> m_bodies;
    // 床
    const P2Body m_floor;
    const P2Body m_ceiling;
    const P2Body m_wall_left;
    const P2Body m_wall_right;
private: // private function
public: // ctor/dtor
    BattleScene(const InitData& init);
    
};


}
}
