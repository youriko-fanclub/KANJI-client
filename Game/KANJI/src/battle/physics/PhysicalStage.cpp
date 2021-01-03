#include "PhysicalStage.hpp"
#include <Siv3D/FormatLiteral.hpp>

using namespace s3d::Literals::FormatLiterals;

namespace kanji {
namespace battle {


/* ---------- PhysicalStageDesc ---------- */

// static ----------------------------------------
PhysicalStageDesc PhysicalStageDesc::createFromToml(const s3d::String& name) {
    PhysicalStageDesc desc;
    const dx::cmp::TomlAsset toml(U"Stage");
    const dx::cmp::TomlKey key(U"stage." + name);
    // desc.id = toml[key + U"id"].get<int>();
    desc.id = toml[dx::cmp::TomlKey(U"stage.notebook.id")].get<int>();
    desc.name = toml[key + U"name"].get<s3d::String>();
    for (int player_num = 1; player_num <= 4; ++player_num) {
        desc.initial_positions.insert(std::make_pair(player_num, std::make_shared<std::vector<s3d::Vec2>>()));
        for (int i = 0; i < player_num; ++i) {
            desc.initial_positions.at(player_num)->push_back(dx::cmp::toml::getVec2(toml[
                key + U"initialposition.{}players.{}"_fmt(player_num, i)]
            ));
        }
    }
    return desc;
}
// public function -------------------------------
// private function ------------------------------
// ctor/dtor -------------------------------------


/* ---------- PhysicalStage ---------- */

// static ----------------------------------------
// public function -------------------------------
void PhysicalStage::drawLegacy() const {
    m_floor.draw(s3d::Palette::Skyblue);
    m_ceiling.draw(s3d::Palette::Skyblue);
    m_wall_left.draw(s3d::Palette::Skyblue);
    m_wall_right.draw(s3d::Palette::Skyblue);
}

const std::vector<s3d::Vec2>& PhysicalStage::initialCharaPositions(int player_num) const {
    return *m_desc.initial_positions.at(player_num);
}
    
// private function ------------------------------
void PhysicalStage::initialize() {
}

// ctor/dtor -------------------------------------
PhysicalStage::PhysicalStage(s3d::P2World* world, const dx::cmp::TomlAsset& toml) :
m_desc(PhysicalStageDesc::createFromToml(U"notebook")),
m_floor     (world->createStaticLine(s3d::Vec2(  0,  0), s3d::Line(-25, 0, 25, 0), s3d::P2Material(1.0, 0.0, toml[dx::cmp::TomlKey(U"physics.floor.friction")].get<double>()))),
m_ceiling   (world->createStaticLine(s3d::Vec2(  0,-25), s3d::Line(-25, 0, 25, 0), s3d::P2Material(1.0, 0.0, toml[dx::cmp::TomlKey(U"physics.floor.friction")].get<double>()))),
m_wall_left (world->createStaticLine(s3d::Vec2(-25,  0), s3d::Line(0, -25, 0, 10), s3d::P2Material(1.0, 0.0, toml[dx::cmp::TomlKey(U"physics.floor.friction")].get<double>()))),
m_wall_right(world->createStaticLine(s3d::Vec2( 25,  0), s3d::Line(0, -25, 0, 10), s3d::P2Material(1.0, 0.0, toml[dx::cmp::TomlKey(U"physics.floor.friction")].get<double>()))) {
    initialize();
}


}
}
