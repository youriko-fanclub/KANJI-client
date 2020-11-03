#pragma once

#include <Siv3D/SceneManager.hpp>
#include "SceneState.hpp"
#include "ExecutiveManager.hpp"

namespace kanji {
namespace seq {

class SequenceManager final :public dx::app::ISequenceManager, public ::dx::cmp::Singleton<SequenceManager> {
public: // static_const/enum
public: // static
public: // public function
  void initialize();
  bool update();
  void draw() const;
private: // field
  s3d::SceneManager<State, DomainGameData> m_manager;
private: // private function
public: // ctor/dtor
};

}
}
