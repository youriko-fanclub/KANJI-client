#pragma once
#include <unordered_map>

namespace kanji {
namespace battle {

class PhysicalCategory {
public:
    static constexpr unsigned Character = 0b0001;
    static constexpr unsigned Radical   = 0b0010;
    static constexpr unsigned Move      = 0b0100;
    static constexpr unsigned Stage     = 0b1000;
    
    std::unordered_map<unsigned, bool> m_collision_map;
    
public:
    PhysicalCategory() = delete;
    ~PhysicalCategory() = delete;
};

}
}
