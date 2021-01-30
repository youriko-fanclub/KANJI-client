#pragma once
#include <Siv3D/HashTable.hpp>
#include <Siv3D/String.hpp>
#include "Singleton.hpp"
#include "IDs.hpp"

namespace kanji {
namespace battle {
class Trajectory;
}
namespace md {

class Move {
public: // static_const/enum
public: // static
public: // public function
public: // field
    const MoveID id;
    const s3d::String kanji;
    const std::shared_ptr<battle::Trajectory> trajectory;
private: // private function
public: // ctor/dtor
    Move(MoveID id, const s3d::String& kanji, const std::shared_ptr<battle::Trajectory>& trajectory) :
        id(id), kanji(kanji), trajectory(trajectory) {}
};

// TOdO: Template化
class MasterRepository : public dx::cmp::Singleton<MasterRepository> {
public: // static_const/enum
    using Id = MoveID;
    using Value = Move;
public: // static
public: // public function
    const std::shared_ptr<Value>& get(Id id) {
        return m_masterdata.at(id);
    }
private: // field
    s3d::HashTable<Id, std::shared_ptr<Value>> m_masterdata;
private: // private function
public: // ctor/dtor
    MasterRepository();
};



}
}
