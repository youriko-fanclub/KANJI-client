#pragma once
#include "IDs.hpp"

namespace kanji {
namespace md {
class MasterStage;
}
namespace battle {

class Stage {
public: // static_const/enum
public: // static
public: // public function
    void initialize();
private: // field
    const md::MasterStage* m_md;
private: // private function
public: // ctor/dtor
    Stage(StageID id);
};


}
}
