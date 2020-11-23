#include "PhysicalStage.hpp"
#include <Siv3D/FormatLiteral.hpp>
#include "HotReloadManager.hpp"
using namespace s3d::Literals::FormatLiterals;


namespace kanji {
namespace battle {


/* ---------- PhysicalStageDesc ---------- */

// static ----------------------------------------
PhysicalStageDesc PhysicalStageDesc::createFromToml(const s3d::String& name) {
    PhysicalStageDesc desc;
    const auto& param = dx::cmp::HotReloadManager::createParamsWithLoad(U"Stage");
    const auto key = U"stage." + name;
    // desc.id = param->get<int>(key + U".id");
    desc.id = param->get<int>(U"stage.notebook.id");
    desc.name = param->get<s3d::String>(key + U".name");
    for (int player_num = 1; player_num <= 4; ++player_num) {
        desc.initial_positions.insert(std::make_pair(player_num, std::make_shared<std::vector<s3d::Vec2>>()));
        for (int i = 0; i < player_num; ++i) {
            desc.initial_positions.at(player_num)->push_back(param->getVec2(
                key + U".initialposition.{}players.{}"_fmt(player_num, i)
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
PhysicalStage::PhysicalStage(s3d::P2World* world, const std::shared_ptr<param::CharaPhysics>& param) :
m_desc(PhysicalStageDesc::createFromToml(U"notebook")),
m_floor     (world->createStaticLine(s3d::Vec2(  0,  0), s3d::Line(-25, 0, 25, 0), s3d::P2Material(1.0, 0.0, param->floor_friction))),
m_ceiling   (world->createStaticLine(s3d::Vec2(  0,-25), s3d::Line(-25, 0, 25, 0), s3d::P2Material(1.0, 0.0, param->ceiling_friction))),
m_wall_left (world->createStaticLine(s3d::Vec2(-25,  0), s3d::Line(0, -25, 0, 10), s3d::P2Material(1.0, 0.0, param->wall_friction))),
m_wall_right(world->createStaticLine(s3d::Vec2( 25,  0), s3d::Line(0, -25, 0, 10), s3d::P2Material(1.0, 0.0, param->wall_friction))) {
    initialize();
}


}
}
