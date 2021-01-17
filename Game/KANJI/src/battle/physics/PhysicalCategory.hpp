#pragma once
#include <Siv3D/Types.hpp>
#include "PhysicalCategoryManager.hpp"

namespace kanji {
namespace battle {

class PhysicalCategory {
public:
    using bitflag = dx::phys::PhysicalCategoryManager::bitflag;
public:
    static constexpr bitflag Character = 0b0001;
    static constexpr bitflag Radical   = 0b0010;
    static constexpr bitflag Move      = 0b0100;
    static constexpr bitflag Stage     = 0b1000;
    
    static dx::phys::PhysicalCategoryManager::Categories categories();
    static dx::phys::PhysicalCategoryManager::CollisionMap collisionMap();
    
public:
    PhysicalCategory() = delete;
    ~PhysicalCategory() = delete;
};

}
}
