#include "PhysicalStage.hpp"
#include <Siv3D/FormatLiteral.hpp>
#include "MasterStageRepository.hpp"
#include "PhysicalCategory.hpp"
#include "PhysicalWorld.hpp"

using namespace s3d::Literals::FormatLiterals;

namespace kanji {
namespace battle {


/* ---------- PhysicalStageObject ---------- */

// static ----------------------------------------
// public function -------------------------------
const std::shared_ptr<s3d::P2Body>& PhysicalStageObject::body() const {
    return obj()->body();
}
// private function ------------------------------
// ctor/dtor -------------------------------------



/* ---------- PhysicalStage ---------- */

// static ----------------------------------------
// public function -------------------------------
const s3d::String& PhysicalStage::name() const { return m_md->name(); }

void PhysicalStage::drawLegacy() const {
    for (const auto& obj : m_objects) {
        obj.second->body()->draw(s3d::Palette::Skyblue);
    }
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
PhysicalStage::PhysicalStage(const std::shared_ptr<dx::phys::PhysicalWorld>& world, StageID id, const dx::toml::TomlAsset& physical) :
m_md(md::MasterStageRepository::instance()->at(id)) {
dx::toml::TomlKey toml_key(U"physics");
m_objects.emplace(U"Floor", std::make_shared<PhysicalStageObject>(
    world->createStaticLine(PhysicalCategory::Stage,
    s3d::Vec2(  0,  0), s3d::Line(-25, 0, 25, 0),
    s3d::P2Material(1.0, 0.0, physical[toml_key + U"floor" + U"friction"].get<double>()))));
m_objects.emplace(U"Ceiling", std::make_shared<PhysicalStageObject>(
    world->createStaticLine(PhysicalCategory::Stage,
    s3d::Vec2(  0,-25), s3d::Line(-25, 0, 25, 0),
    s3d::P2Material(1.0, 0.0, physical[toml_key + U"ceiling" + U"friction"].get<double>()))));
m_objects.emplace(U"WallLeft", std::make_shared<PhysicalStageObject>(
    world->createStaticLine(PhysicalCategory::Stage,
    s3d::Vec2(-25,  0), s3d::Line(0, -25, 0, 10),
    s3d::P2Material(1.0, 0.0, physical[toml_key + U"wall" + U"friction"].get<double>()))));
m_objects.emplace(U"WallRight", std::make_shared<PhysicalStageObject>(
    world->createStaticLine(PhysicalCategory::Stage,
    s3d::Vec2( 25,  0), s3d::Line(0, -25, 0, 10),
    s3d::P2Material(1.0, 0.0, physical[toml_key + U"wall" + U"friction"].get<double>()))));
    initialize();
}


}
}
