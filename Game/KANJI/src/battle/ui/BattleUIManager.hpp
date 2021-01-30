#pragma once
#include <Siv3D/Camera2D.hpp>
#include "PlayerId.hpp"
#include "UIComponent.hpp"

namespace kanji {
namespace battle {
class IBattleManager;
class PhysicalWorldManager;
class PhysicalMoveManager;
class PhysicalRadicalManager;
class PhysicalCharacter;
}
namespace ui {
class IHolderUI;

class MoveUIManager : public dx::ui::UIComponent {
public: // static_const/enum
public: // static
public: // public function
    void update();
protected: // protected function
    void drawImpl() const override;
private: // field
    const battle::PhysicalMoveManager* const m_move_mgr = nullptr;
private: // private function
public: // ctor/dtor
    MoveUIManager(const battle::PhysicalMoveManager* move_mgr);
};


class PhysicalWorldUIManager : public dx::ui::UIComponent {
public: // static_const/enum
public: // static
public: // public function
    void update();
protected: // protected function
    void drawImpl() const override;
private: // field
    const battle::PhysicalWorldManager* const m_world_mgr = nullptr;
private: // private function
public: // ctor/dtor
    PhysicalWorldUIManager(const battle::PhysicalWorldManager* world_mgr);
};


class BattleUIManager : public dx::ui::UIComponent {
public: // static_const/enum
public: // static
public: // public function
    void update();
protected: // protected function
    void drawImpl() const override;
private: // field
    s3d::Camera2D m_camera;
    const battle::IBattleManager* const m_battle_manager = nullptr;
    s3d::HashTable<dx::di::PlayerId, std::shared_ptr<IHolderUI>> m_holders;
    std::shared_ptr<PhysicalWorldUIManager> m_world;
    std::shared_ptr<MoveUIManager> m_moves;
private: // private function
public: // ctor/dtor
    BattleUIManager(const battle::IBattleManager* battle_mgr);
};


}
}

