#include "PhysicalStage.hpp"
#include <Siv3D/FormatLiteral.hpp>
#include "MasterStageRepository.hpp"

using namespace s3d::Literals::FormatLiterals;

namespace kanji {
namespace battle {


/* ---------- PhysicalStageDesc ---------- */

// static ----------------------------------------
PhysicalStageDesc PhysicalStageDesc::createFromToml(StageID id) {
    const auto* md = md::MasterStageRepository::instance()->at(id);
    return PhysicalStageDesc(md);
}
// public function -------------------------------
// private function ------------------------------
// ctor/dtor -------------------------------------
PhysicalStageDesc::PhysicalStageDesc(const md::MasterStage* md) :
id(md->id()),
name(md->name()) {
    initial_positions.insert(std::make_pair(1, std::make_shared<std::vector<s3d::Vec2>>()));
    initial_positions.insert(std::make_pair(2, std::make_shared<std::vector<s3d::Vec2>>()));
    initial_positions.insert(std::make_pair(3, std::make_shared<std::vector<s3d::Vec2>>()));
    initial_positions.insert(std::make_pair(4, std::make_shared<std::vector<s3d::Vec2>>()));
    
    initial_positions.at(1)->push_back(md->initialposition1Players0());
    initial_positions.at(2)->push_back(md->initialposition2Players0());
    initial_positions.at(2)->push_back(md->initialposition2Players1());
    initial_positions.at(3)->push_back(md->initialposition3Players0());
    initial_positions.at(3)->push_back(md->initialposition3Players1());
    initial_positions.at(3)->push_back(md->initialposition3Players2());
    initial_positions.at(4)->push_back(md->initialposition4Players0());
    initial_positions.at(4)->push_back(md->initialposition4Players1());
    initial_positions.at(4)->push_back(md->initialposition4Players2());
    initial_positions.at(4)->push_back(md->initialposition4Players3());
}


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
PhysicalStage::PhysicalStage(s3d::P2World* world, const dx::toml::TomlAsset& toml) :
m_desc(PhysicalStageDesc::createFromToml(StageID(300000))),
m_floor     (world->createStaticLine(s3d::Vec2(  0,  0), s3d::Line(-25, 0, 25, 0), s3d::P2Material(1.0, 0.0, toml[dx::toml::TomlKey(U"physics.floor.friction")].get<double>()))),
m_ceiling   (world->createStaticLine(s3d::Vec2(  0,-25), s3d::Line(-25, 0, 25, 0), s3d::P2Material(1.0, 0.0, toml[dx::toml::TomlKey(U"physics.ceiling.friction")].get<double>()))),
m_wall_left (world->createStaticLine(s3d::Vec2(-25,  0), s3d::Line(0, -25, 0, 10), s3d::P2Material(1.0, 0.0, toml[dx::toml::TomlKey(U"physics.wall.friction")].get<double>()))),
m_wall_right(world->createStaticLine(s3d::Vec2( 25,  0), s3d::Line(0, -25, 0, 10), s3d::P2Material(1.0, 0.0, toml[dx::toml::TomlKey(U"physics.wall.friction")].get<double>()))) {
    initialize();
}


}
}
