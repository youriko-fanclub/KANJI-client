#include "PhysicalCategory.hpp"

namespace kanji {
namespace battle {

using bitflag = PhysicalCategory::bitflag;

dx::phys::PhysicalCategoryManager::Categories PhysicalCategory::categories() {
    return { Character, Radical, Move, Stage, };
}
dx::phys::PhysicalCategoryManager::CollisionMap PhysicalCategory::collisionMap() {
    return {
        { Character | Move   , true },
        { Character | Stage  , true },

        { Radical   | Stage  , true },
    };
}

// public function -------------------------------
// private function ------------------------------
// ctor/dtor -------------------------------------

}
}
