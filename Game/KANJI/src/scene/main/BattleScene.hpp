#pragma once

#include "SceneStates.hpp"
#include "UIComponent.hpp"
#include "CharaPhysicsParameters.hpp"

namespace kanji {
namespace seq {


// タイトルシーン
class BattleScene : public KanjiScene {
public: // static_const/enum
public: // static
public: // public function
    void update() override;
    void draw() const override;
private: // field
    std::unique_ptr<param::CharaPhysics> param;
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
    const P2Body m_line;
    const P2Body m_wall_left;
    const P2Body m_wall_right;
private: // private function
public: // ctor/dtor
    BattleScene(const InitData& init);
    
};


}
}
