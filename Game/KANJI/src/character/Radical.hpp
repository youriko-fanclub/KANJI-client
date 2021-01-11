#pragma once
#include "IDs.hpp"
#include "Ability.hpp"

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
    const std::unique_ptr<IAbility>& ability() const { return m_ability; }
private: // field
    const md::MasterRadicalParam* m_md;
    std::unique_ptr<IAbility> m_ability;
private: // private function
public: // ctor/dtor
    Radical(RadicalID id);
};


}
}
