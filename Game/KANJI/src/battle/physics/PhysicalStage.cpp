#include "PhysicalStage.hpp"
#include <Siv3D/FormatLiteral.hpp>
#include "MasterStageRepository.hpp"

using namespace s3d::Literals::FormatLiterals;

namespace kanji {
namespace battle {


/* ---------- PhysicalStage ---------- */

// static ----------------------------------------
// public function -------------------------------
void PhysicalStage::drawLegacy() const {
    m_floor.draw(s3d::Palette::Skyblue);
    m_ceiling.draw(s3d::Palette::Skyblue);
    m_wall_left.draw(s3d::Palette::Skyblue);
    m_wall_right.draw(s3d::Palette::Skyblue);
}

std::vector<s3d::Vec2> initialPos(const md::MasterStage* md, int player_num) {
    switch (player_num) {
        case 1: return {
            md->initialposition1Players0()
        };
        case 2: return {
            md->initialposition2Players0(),
            md->initialposition2Players1()
        };
        case 3: return {
            md->initialposition3Players0(),
            md->initialposition3Players1(),
            md->initialposition3Players2()
        };
        case 4: return {
            md->initialposition4Players0(),
            md->initialposition4Players1(),
            md->initialposition4Players2(),
            md->initialposition4Players3()
        };
        default: return {};
    }
}

std::vector<s3d::Vec2> PhysicalStage::initialCharaPositions(int player_num) const {
    return initialPos(m_md, player_num);
}
    
// private function ------------------------------
void PhysicalStage::initialize() {
}

// ctor/dtor -------------------------------------
PhysicalStage::PhysicalStage(s3d::P2World* world, StageID id, const dx::toml::TomlAsset& physical) :
m_md(md::MasterStageRepository::instance()->at(id)),
m_floor     (world->createStaticLine(s3d::Vec2(  0,  0), s3d::Line(-25, 0, 25, 0), s3d::P2Material(1.0, 0.0, physical[dx::toml::TomlKey(U"physics.floor.friction")].get<double>()))),
m_ceiling   (world->createStaticLine(s3d::Vec2(  0,-25), s3d::Line(-25, 0, 25, 0), s3d::P2Material(1.0, 0.0, physical[dx::toml::TomlKey(U"physics.ceiling.friction")].get<double>()))),
m_wall_left (world->createStaticLine(s3d::Vec2(-25,  0), s3d::Line(0, -25, 0, 10), s3d::P2Material(1.0, 0.0, physical[dx::toml::TomlKey(U"physics.wall.friction")].get<double>()))),
m_wall_right(world->createStaticLine(s3d::Vec2( 25,  0), s3d::Line(0, -25, 0, 10), s3d::P2Material(1.0, 0.0, physical[dx::toml::TomlKey(U"physics.wall.friction")].get<double>()))) {
    initialize();
}


}
}
