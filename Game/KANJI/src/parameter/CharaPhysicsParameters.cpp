#include "CharaPhysicsParameters.hpp"

namespace kanji {
namespace param {

/* ---------- CharaPhysicsParams ---------- */

// static ----------------------------------------
// public function -------------------------------
// protected function -------------------------------
void CharaPhysics::loadImpl(const s3d::TOMLReader& toml) {
    // 要素のパスで値を取得
    force_horizontal = toml[U"chara.force.horizontal"].get<double>();
    force_jump       = toml[U"chara.force.jump"].get<double>();
    chara_friction   = toml[U"chara.friction"].get<double>();
    air_resistance   = toml[U"chara.air_resistance"].get<double>();
    floor_friction   = toml[U"floor.friction"].get<double>();
    wall_friction    = toml[U"wall.friction"].get<double>();
}
// private function ------------------------------
// ctor/dtor -------------------------------------
CharaPhysics::CharaPhysics() :
HotReloadableParameters(U"Physics") {
    load();
}


}
}
