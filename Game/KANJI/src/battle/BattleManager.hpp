#pragma once
#include "BattleDesc.hpp"

namespace kanji {
namespace battle {

class BattlePlayerManager;
class PhysicalWorldManager;
class PhysicalMoveManager;

class BattleTimer {
public: // static_const/enum
public: // static
public: // public function
    int current() const { return m_counter; }
    bool hasTimeover() const { return m_counter < 0; }
    void update() {
        if (!m_is_pause) {
            --m_counter;
        }
    }
    void pause() { m_is_pause = true; }
    void resume() { m_is_pause = false; }
private: // field
    int m_counter;
    bool m_is_pause = false;
private: // private function
public: // ctor/dtor
    BattleTimer(int timelimit) :
    m_counter(timelimit) {}
};


class IBattleManager {
public: // getter
    virtual bool hasGameSet() const = 0;
    virtual std::shared_ptr<BattleResultDesc> createResultDesc() const = 0;
    virtual const std::shared_ptr<BattlePlayerManager>& playerMgr() const = 0;
    virtual const std::shared_ptr<PhysicalWorldManager>& worldMgr() const = 0;
    virtual const std::shared_ptr<PhysicalMoveManager>& moveMgr() const = 0;
public: // setter
    virtual void initialize(const std::shared_ptr<BattleDesc>& desc) = 0;
    virtual void update() = 0;
    virtual void pause() = 0;
    virtual void resume() = 0;
    virtual void holdUp() = 0;
protected:
    IBattleManager() = default;
    virtual ~IBattleManager() = default;
};


class BattleManager : public IBattleManager {
public: // static_const/enum
public: // static
public: // getter
    bool hasGameSet() const override;
    std::shared_ptr<BattleResultDesc> createResultDesc() const override;
    const std::shared_ptr<BattlePlayerManager>& playerMgr() const override {
        return m_player_mgr;
    }
    const std::shared_ptr<PhysicalWorldManager>& worldMgr() const override {
        return m_world_mgr;
    }
    const std::shared_ptr<PhysicalMoveManager>& moveMgr() const override {
        return m_move_mgr;
    }
public: // setter
    void initialize(const std::shared_ptr<BattleDesc>& desc) override;
    void update() override;
    void pause() override;
    void resume() override;
    void holdUp() override;
private: // field
    std::shared_ptr<BattleTimer> m_timer;
    std::shared_ptr<BattlePlayerManager> m_player_mgr;
    std::shared_ptr<PhysicalWorldManager> m_world_mgr;
    std::shared_ptr<PhysicalMoveManager> m_move_mgr;
private: // private function
public: // ctor/dtor
    BattleManager();
};


}
}
