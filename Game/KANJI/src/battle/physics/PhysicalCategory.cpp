#include "PhysicalCategory.hpp"

namespace kanji {
namespace battle {

using bitflag = PhysicalCategory::bitflag;

/* ---------- PhysicalCategory ---------- */

// static ----------------------------------------
void PhysicalCategory::initialize() {
    for (const auto category_a : m_categories) {
        auto mask = category_a;
        for (const auto category_b : m_categories) {
            if (const auto mask_value = category_a | category_b;
                m_collision_map.contains(mask_value) && m_collision_map.at(mask_value)) {
                mask |= category_b;
            }
        }
        m_masks[category_a] = mask;
    }
}

bitflag PhysicalCategory::mask(const bitflag category) {
    return m_masks.at(category);
}

s3d::P2Filter PhysicalCategory::filter(bitflag category) {
    return s3d::P2Filter(category, m_masks.at(category));
}

const std::unordered_map<bitflag, bool> PhysicalCategory::m_collision_map = {
    { Character | Radical, true },
    { Character | Move   , true },
    { Character | Stage  , true },
    
    { Radical   | Stage  , true },
};
std::unordered_map<bitflag, bitflag> PhysicalCategory::m_masks;
const std::vector<bitflag> PhysicalCategory::m_categories = {
    Character, Radical, Move, Stage,
};
// public function -------------------------------
// private function ------------------------------
// ctor/dtor -------------------------------------

}
}
