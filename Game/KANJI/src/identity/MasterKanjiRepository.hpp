#pragma once
#include "MasterDataRepository.hpp"
#include "MasterKanji.hpp"
#include "IDs.hpp"

namespace kanji {
namespace md {

class MasterKanjiRepository : public dx::md::MasterDataRepository<chara::KanjiID, MasterKanji> {
public: // static_const/enum
public: // static
public: // public function
protected: // protected function
    void initialize() override;
private: // field
private: // private function
public: // ctor/dtor
};


}
}
