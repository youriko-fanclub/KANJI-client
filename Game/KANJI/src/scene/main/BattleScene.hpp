#pragma once

#include "SceneStates.hpp"
#include "UIComponent.hpp"

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
    std::pair<s3d::DrawableText, s3d::DrawableText> m_title;
    dui::Button m_start;
    
    // 2Dカメラ
    Camera2D camera;
    // 物理演算用のワールド
    P2World world;
    // 物体
    P2Body m_chara;
    Array<P2Body> bodies;
    // 床
    const P2Body line;
private: // private function
public: // ctor/dtor
    BattleScene(const InitData& init);
    
};


}
}
