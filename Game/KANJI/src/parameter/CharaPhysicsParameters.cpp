#include "CharaPhysicsParameters.hpp"

namespace kanji {
namespace param {

/* ---------- CharaPhysicsParams ---------- */

// static ----------------------------------------
// public function -------------------------------
// protected function -------------------------------
void CharaPhysics::loadImpl(const s3d::TOMLReader& toml) {
    // 要素のパスで値を取得
    force_horizontal = toml[U"physics.chara.force.horizontal"].get<double>();
    force_jump       = toml[U"physics.chara.force.jump"].get<double>();
    chara_friction   = toml[U"physics.chara.friction"].get<double>();
    air_resistance   = toml[U"physics.chara.air_resistance"].get<double>();
    floor_friction   = toml[U"physics.floor.friction"].get<double>();
    wall_friction    = toml[U"physics.wall.friction"].get<double>();
}
// private function ------------------------------
// ctor/dtor -------------------------------------
CharaPhysics::CharaPhysics() :
HotReloadableParameters(U"Physics") {
    load();
}


}
}
