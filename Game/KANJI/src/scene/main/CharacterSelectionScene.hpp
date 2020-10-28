#pragma once

#include "SceneStates.hpp"
#include "UIComponent.hpp"

namespace kanji {
namespace seq {


// キャラクター選択シーン
class CharacterSelectionScene : public KanjiScene {
public: // static_const/enum
public: // static
public: // public function
    void update() override;
    void draw() const override;
private: // field
    std::pair<s3d::DrawableText, s3d::DrawableText> m_title;
    dui::Button m_next;
private: // private function
public: // ctor/dtor
    CharacterSelectionScene(const InitData& init);

};


}
}
