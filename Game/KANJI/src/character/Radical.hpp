#pragma once
#include "IDs.hpp"

namespace kanji {
namespace md {
class MasterRadicalParam;
}
namespace chara {

class Radical {
public: // static_const/enum
public: // static
public: // public function
    const s3d::String& chara() const;
private: // field
    const md::MasterRadicalParam* m_md;
private: // private function
public: // ctor/dtor
    Radical(RadicalID id);
};


}
}
