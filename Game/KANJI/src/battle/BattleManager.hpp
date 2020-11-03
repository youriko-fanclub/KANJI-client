#pragma once
#include "BattleDesc.hpp"

namespace kanji {
namespace battle {

class IBattleManager {
public: // getter
    virtual bool hasGameSet() = 0;
    virtual std::shared_ptr<BattleResultDesc> createResultDesc() = 0;
public: // setter
    virtual void initialize(const std::shared_ptr<BattleDesc>& desc) = 0;
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
public: // public function
private: // field
private: // private function
public: // ctor/dtor
};


}
}
