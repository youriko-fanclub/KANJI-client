#pragma once

#include "SceneStates.hpp"
#include "UIComponent.hpp"

namespace kanji {
namespace seq {


// タイトルシーン
class TitleScene : public KanjiScene {
public: // static_const/enum
public: // static
public: // public function
  void update() override;
  void draw() const override;
private: // field
  std::pair<s3d::DrawableText, s3d::DrawableText> m_title;
  dui::Button m_start;
  dui::Button m_exit;
private: // private function
public: // ctor/dtor
  TitleScene(const InitData& init);

};


}
}
