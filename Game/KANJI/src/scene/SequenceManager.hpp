#pragma once

#include <Siv3D/SceneManager.hpp>
#include "SceneStates.hpp"
#include "Singleton.hpp"

namespace kanji {
namespace seq {

class SequenceManager final : public ::dx::cmp::Singleton<SequenceManager> {
public: // static_const/enum
public: // static
public: // public function
  void initialize();
  bool update();
private: // field
  s3d::SceneManager<State, DomainGameData> m_manager;
private: // private function
public: // ctor/dtor
};

}
}
