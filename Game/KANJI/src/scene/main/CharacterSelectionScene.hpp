#pragma once

#include "KanjiScene.hpp"
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
    dui::Button m_next;
    dui::Button m_back;
private: // private function
public: // ctor/dtor
    CharacterSelectionScene(const InitData& init);

};


}
}
