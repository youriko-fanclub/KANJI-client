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
#include "HotReloadManager.hpp"

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
    m_world_mgr->stage()->drawLegacy();
    for (const auto& chara : m_world_mgr->characters()) {
        const auto& color = dx::di::Id::ToColor(chara.first);
        chara.second->rect()
            .drawFrame(0.2f, 0.2f, s3d::Palette::Black)
            .drawFrame(0.1f, 0.1f, color)
            .draw(s3d::ColorF(1.f, 1.f, 1.f, 0.5f));
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
    for (const auto& holder : m_holders) {
        holder.second->draw();
    }
    {
        const auto t = m_camera.createTransformer();
        m_world->draw();
        m_moves->draw();
    }
    m_camera.draw();
    
    static auto param = dx::cmp::HotReloadManager::createParamsWithLoad(U"Battle");
    static s3d::Font font = param->getFont(U"battle.ui.object.physical.chara.font");
    if (font.fontSize() != param->get<int>(U"battle.ui.object.physical.chara.font.size")) {
        font = param->getFont(U"battle.ui.object.physical.chara.font");
    }
    for (const auto& chara : m_battle_manager->worldMgr()->characters()) {
        const auto& kanji = chara.second->status()->kanji().kanji;
        const auto& pos = m_camera.getMat3x2().transform(chara.second->position());
        const auto& color = dx::di::Id::ToColorDark(chara.first);
        font(kanji).draw(s3d::Arg::center(pos), color);
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
