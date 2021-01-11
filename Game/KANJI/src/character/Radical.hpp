#pragma once
#include "IDs.hpp"
#include "Ability.hpp"

namespace kanji {
namespace md {
class MasterRadicalParam;
}
namespace chara {

class IRadical {
public:
    virtual s3d::String chara() const = 0;
    virtual const IAbility* ability() const = 0;
protected:
    IRadical() = default;
public:
    virtual ~IRadical() = default;
};


class Radical : public IRadical {
public: // static_const/enum
public: // static
public: // public function
    s3d::String chara() const override;
    const IAbility* ability() const override { return &m_ability; }
private: // field
    const md::MasterRadicalParam* m_md;
    const ud::UserRadicalParam m_ud;
    RadicalAbility m_ability;
private: // private function
public: // ctor/dtor
    Radical(RadicalID id);
};

class RadicalHolder : public IRadical {
public: // static_const/enum
    static const ConstantAbility s_zero;
public: // static
public: // public function
    s3d::String chara() const override;
    const IAbility* ability() const override;

    bool hasRadical() const { return m_radical != nullptr; }
    const std::unique_ptr<chara::Radical>& radical() const { return m_radical; }
    void add(RadicalID id) {
        m_radical = std::make_unique<chara::Radical>(id);
    }
    void remove() { m_radical.reset(); }
private: // field
    std::unique_ptr<Radical> m_radical;
private: // private function
public: // ctor/dtor
    RadicalHolder();
    RadicalHolder(RadicalID id);
};

}
}
