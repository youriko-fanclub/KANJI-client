#pragma once

#include <Siv3D/SceneManager.hpp>
#include "KanjiScene.hpp"
#include "ExecutiveManager.hpp"

namespace kanji {
namespace seq {

class SequenceManager final :public dx::app::ISequenceManager, public ::dx::cmp::Singleton<SequenceManager> {
public: // static_const/enum
public: // static
public: // public function
  void initialize() override;
  bool update() override;
  void draw() const override;
private: // field
  s3d::SceneManager<State, DomainGameData> m_manager;
private: // private function
public: // ctor/dtor
};

}
}
