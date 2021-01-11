#pragma once
#include "MasterKanjiParam.hpp"

namespace kanji {
namespace chara {

struct CharaParameters {
public:
    int hp;
    int attack;
    int defence;
    int speed;
    int jump;
    int weight;
};

}
namespace md {
class MasterKanjiParam;
}
namespace ud {
using UserKanjiParam = chara::CharaParameters;
}
namespace chara {

class IAbility {
public:
    virtual int attack() const = 0;
    virtual int defence() const = 0;
    virtual int speed() const = 0;
    virtual int jump() const = 0;
    virtual int weight() const = 0;
    
protected:
    IAbility() = default;
public:
    virtual ~IAbility() = default;
};


class ConstantAbility : public IAbility {
public: // static_const/enum
public: // static
public: // public function
    int attack() const override { return m_attack; }
    int defence() const override { return m_defence; }
    int speed() const override { return m_speed; }
    int jump() const override { return m_jump; }
    int weight() const override { return m_weight; }
private: // field
    int m_attack;
    int m_defence;
    int m_speed;
    int m_jump;
    int m_weight;
private: // private function
public: // ctor/dtor
    ConstantAbility(int attack, int defence, int speed, int jump, int weight) :
    m_attack(attack),
    m_defence(defence),
    m_speed(speed),
    m_jump(jump),
    m_weight(weight) {}
    ConstantAbility(const IAbility& another) :
    m_attack(another.attack()),
    m_defence(another.defence()),
    m_speed(another.speed()),
    m_jump(another.jump()),
    m_weight(another.weight()) {}
    virtual ~ConstantAbility() = default;
};


class ParameterizedCharacter;

class Ability : public IAbility {
public: // static_const/enum
public: // static
public: // public function
    int attack() const override;
    int defence() const override;
    int speed() const override;
    int jump() const override;
    int weight() const override;
    
    // void set(const md::MasterKanjiParam* md, const ud::UserKanjiParam* ud) {
    //     m_md = md;
    //     u_ud = ud;
    // }
private: // field
    const md::MasterKanjiParam* m_md;
    const ud::UserKanjiParam* m_ud;
private: // private function
public: // ctor/dtor
    Ability(const md::MasterKanjiParam* md, const ud::UserKanjiParam* ud) :
    m_md(md), m_ud(ud) {}
    virtual ~Ability() = default;
};


}
}



