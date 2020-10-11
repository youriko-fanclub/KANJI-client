#pragma once

#include "SceneStates.hpp"

namespace kanji {
namespace seq {


// タイトルシーン
class TitleScene : public KanjiScene {
public: // static_const/enum
  class Button {
  public: // static_const/enum
  public: // static
  public: // public getter
    const s3d::Rect& rect() const { return m_rect; }
  public: // public setter
    void setCallback(const std::function<void()>& callback) {
      m_pressedCallback = callback;
    }
    bool update() {
      m_transition.update(m_rect.mouseOver());
      if (rect().mouseOver()) {
        Cursor::RequestStyle(CursorStyle::Hand);
      }
      if (rect().leftClicked()) {
        m_pressedCallback();
      }
      return true;
    }
    void draw() const {
      m_rect.draw(ColorF(1.0, m_transition.value())).drawFrame(2);
      m_label.drawAt(m_rect.center(), ColorF(0.25));
    }
  private: // field
    s3d::Rect m_rect;
    s3d::DrawableText m_label;
    Transition m_transition;
    std::function<void()> m_pressedCallback = [](){};
  private: // private function
  public: // ctor/dtor
    Button(
      const s3d::Rect& rect,
      const s3d::DrawableText& label,
      const Transition& transition,
      const std::function<void()>& pressedCallback) :
      m_rect(rect), m_label(label), m_transition(transition), m_pressedCallback(pressedCallback) {}
    Button(const s3d::Rect& rect, const s3d::DrawableText& label, const Transition& transition) :
      m_rect(rect), m_label(label), m_transition(transition) {}
  };
public: // static
public: // public function
private: // field
  std::pair<DrawableText, DrawableText> m_title;
  Button m_start;
  Button m_exit;
private: // private function
public: // ctor/dtor

private:
  
  Rect m_startButton = Rect(Arg::center = Scene::Center().movedBy(0, 0), 300, 60);
  Transition m_startTransition = Transition(0.4s, 0.2s);
  
  Rect m_exitButton = Rect(Arg::center = Scene::Center().movedBy(0, 100), 300, 60);
  Transition m_exitTransition = Transition(0.4s, 0.2s);

public:
  
  TitleScene(const InitData& init);
  
  void update() override;
  
  void draw() const override;
};


}
}
