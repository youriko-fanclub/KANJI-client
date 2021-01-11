#pragma once

namespace kanji {
namespace chara {

class Status {
public: // static_const/enum
public: // static
public: // public function
    int hp() const { return m_hp; }
    int initialHp() const { return m_initial_hp; }
    float hpRate() const {
        return static_cast<float>(m_hp) / static_cast<float>(m_initial_hp);
    }
    bool isBurnedOut() const { return m_is_burned_out; }
    
    void setHp(int value) { m_hp = value; }
    void damage(int amount) { m_hp -= amount; }
    void burnOut() { m_is_burned_out = true; }
private: // field
    bool m_is_burned_out = false;
    int m_hp = 100;
    const int m_initial_hp = 100;
private: // private function
public: // ctor/dtor
};


}
}
