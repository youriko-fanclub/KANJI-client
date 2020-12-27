#pragma once
#include "MasterDataRepository.hpp"
#include "MasterKanji.hpp"
#include "IDs.hpp"
#include "Singleton.hpp"

namespace kanji {
namespace md {

class MasterKanjiRepository :
    public dx::md::MasterDataRepository<chara::KanjiID, MasterKanji>,
    public dx::cmp::Singleton<MasterKanjiRepository> {
public: // static_const/enum
public: // static
public: // public function
protected: // protected function
    void initialize();
private: // field
private: // private function
public: // ctor/dtor
    MasterKanjiRepository() {
        initialize();
    }
};


}
}
