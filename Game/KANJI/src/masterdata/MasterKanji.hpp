#pragma once
#include "IDs.hpp"

namespace kanji {
namespace md {

class MasterKanji {
public: // static_const/enum
public: // static
public: // public function
    chara::KanjiID id() const { return m_id; }
    const s3d::String& character() const { return m_character; }
private: // field
    chara::KanjiID m_id;
    s3d::String m_character;
private: // private function
public: // ctor/dtor
    MasterKanji(chara::KanjiID id, s3d::String character) :
    m_id(id),
    m_character(character) {}
};


}
}
