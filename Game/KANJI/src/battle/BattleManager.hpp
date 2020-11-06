#pragma once
#include "BattleDesc.hpp"

namespace kanji {
namespace battle {

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
public: // setter
    void initialize(const std::shared_ptr<BattleDesc>& desc) override;
    void update() override;
    void pause() override;
    void resume() override;
    void holdUp() override;
private: // field
    std::shared_ptr<BattleTimer> m_timer;
private: // private function
public: // ctor/dtor
    BattleManager();
};


}
}
