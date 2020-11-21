#pragma once
#include <unordered_map>
#include <Siv3D/String.hpp>
#include "Singleton.hpp"

namespace kanji {
namespace battle {
class Trajectory;
}
namespace md {

// TOdO:
using MoveId = int;

class Move {
public: // static_const/enum
public: // static
public: // public function
public: // field
    const MoveId id;
    const s3d::String kanji;
    const std::shared_ptr<battle::Trajectory> trajectory;
private: // private function
public: // ctor/dtor
    Move(MoveId id, const s3d::String& kanji, const std::shared_ptr<battle::Trajectory>& trajectory) :
        id(id), kanji(kanji), trajectory(trajectory) {}
};

// TOdO: Template化
class MasterRepository : public dx::cmp::Singleton<MasterRepository> {
public: // static_const/enum
    using Id = MoveId;
    using Value = Move;
public: // static
public: // public function
    const std::shared_ptr<Value>& get(Id id) {
        return m_masterdata.at(id);
    }
private: // field
    std::unordered_map<Id, std::shared_ptr<Value>> m_masterdata;
private: // private function
public: // ctor/dtor
    MasterRepository();
};



}
}
