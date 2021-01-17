#pragma once
#include <unordered_map>
#include <vector>
#include <Siv3D/Physics2D.hpp>

namespace kanji {
namespace battle {

class PhysicalCategory {
public:
    using bitflag = s3d::uint16;
public:
    static constexpr bitflag Character = 0b0001;
    static constexpr bitflag Radical   = 0b0010;
    static constexpr bitflag Move      = 0b0100;
    static constexpr bitflag Stage     = 0b1000;
    
    static void initialize();
    static bitflag mask(bitflag category);
    static s3d::P2Filter filter(bitflag category);
    static const std::vector<bitflag>& categories() { return m_categories; }

private:
    static const std::unordered_map<bitflag, bool> m_collision_map;
    static std::unordered_map<bitflag, bitflag> m_masks;
    static const std::vector<bitflag> m_categories;

public:
    PhysicalCategory() = delete;
    ~PhysicalCategory() = delete;
};

}
}
