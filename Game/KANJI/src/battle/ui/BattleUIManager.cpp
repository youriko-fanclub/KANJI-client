#include "BattleUIManager.hpp"
#include "BattleManager.hpp"
#include "BattlePlayerManager.hpp"
#include "BattlePlayer.hpp"
#include "PhysicalStage.hpp"
#include "PhysicalWorldManager.hpp"
#include "PhysicalMove.hpp"
#include "ParameterizedCharacter.hpp"
#include "HolderUI.hpp"
#include "Log.hpp"
#include "AssetManager.hpp"
#include "TomlAsset.hpp"

namespace kanji {
namespace ui {


/* ---------- MoveUIManager ---------- */

// static ----------------------------------------
// public function -------------------------------
void MoveUIManager::update() {}
// protected function ------------------------------
void MoveUIManager::drawImpl() const {
    for (const auto& move : m_move_mgr->moves()) {
        const auto box = move->currentHitBox();
        box.draw(dx::di::Id::ToColor(move->owner()));
    }
}
// private function ------------------------------
// ctor/dtor -------------------------------------
MoveUIManager::MoveUIManager(const battle::PhysicalMoveManager* move_mgr) :
m_move_mgr(move_mgr) {}



/* ---------- PhysicalWorldUIManager ---------- */

// static ----------------------------------------
// public function -------------------------------
void PhysicalWorldUIManager::update() {}
// protected function ------------------------------
void PhysicalWorldUIManager::drawImpl() const {
    {
        const auto& stage = m_world_mgr->stage();
        s3d::Rect(-26, -28, 52, 40)(TextureAsset(U"Stage::" + stage->name() + U"::Bg")).draw();
        stage->drawLegacy();
    }
    for (const auto& chara : m_world_mgr->characters()) {
        const auto& color = dx::di::Id::ToColor(chara.first);
        chara.second->rect()
            .drawFrame(0.2f, 0.2f, s3d::Palette::Black)
            .drawFrame(0.1f, 0.1f, color)
            .draw(s3d::ColorF(1.f, 1.f, 1.f, 0.5f));
        s3d::Shape2D::Arrow(
            chara.second->position() + s3d::Vec2((chara.second->isRight() ? 1 : -1) * 2.00, 0),
            chara.second->position() + s3d::Vec2((chara.second->isRight() ? 1 : -1) * 3.75, 0),
            1.2,
            s3d::Vec2::One()).draw(color);
    }
}
// private function ------------------------------
// ctor/dtor -------------------------------------
PhysicalWorldUIManager::PhysicalWorldUIManager(const battle::PhysicalWorldManager* world_mgr) :
m_world_mgr(world_mgr) {}



/* ---------- BattleUIManager ---------- */

// static ----------------------------------------
// public function -------------------------------
void BattleUIManager::update() {
    m_camera.update();
    for (auto& holder : m_holders) {
        holder.second->update();
    }
}

void BattleUIManager::drawImpl() const {
    {
        const auto t = m_camera.createTransformer();
        m_world->draw();
        m_moves->draw();
    }
    m_camera.draw();
    
    dx::toml::TomlKey key(U"battle.ui.object.physical.chara.font");
    dx::toml::TomlAsset toml(U"Battle");
    static s3d::Font font = dx::toml::font(toml[key]);
    if (font.fontSize() != toml[key + U"size"].get<int>()) {
        font = dx::toml::font(toml[key]);
    }
    for (const auto& chara : m_battle_manager->worldMgr()->characters()) {
        const auto& kanji = chara.second->status()->activeCharacter()->kanji().kanji;
        const auto& pos = m_camera.getMat3x2().transform(chara.second->position());
        const auto& color = dx::di::Id::ToColorDark(chara.first);
        font(kanji).draw(s3d::Arg::center(pos), color);
    }
    for (const auto& holder : m_holders) {
        holder.second->draw();
    }
}

// private function ------------------------------
// ctor/dtor -------------------------------------
BattleUIManager::BattleUIManager(const battle::IBattleManager* battle_mgr) :
m_camera(Vec2(0, -8), 20.0, s3d::Camera2DParameters::MouseOnly()),
m_battle_manager(battle_mgr),
m_world(std::make_shared<PhysicalWorldUIManager>(battle_mgr->worldMgr().get())),
m_moves(std::make_shared<MoveUIManager>(battle_mgr->moveMgr().get())) {
    const auto& players = m_battle_manager->playerMgr()->players();
    const int player_num = static_cast<int>(players.size());
    for (int i = 0; const auto& player : players) {
        m_holders.insert(std::make_pair(player.first,
            std::make_shared<HolderUI>(i, player_num, player.second)));
        ++i;
    }
}


}
}
