#pragma once
#include "HotReloadableParameters.hpp"

namespace kanji {
namespace param {

class CharaPhysics final : public dx::cmp::HotReloadableParameters {
public: // protected function
    void loadImpl(const s3d::TOMLReader& toml) override;
public: // field
    double force_horizontal;
    double force_jump;
    double chara_friction;
    double air_resistance;
    double floor_friction;
    double wall_friction;
private: // private function
public: // ctor/dtor
    CharaPhysics();
};

}
}
