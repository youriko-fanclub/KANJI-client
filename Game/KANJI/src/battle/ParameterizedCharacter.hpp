#pragma once
#include <Siv3D/String.hpp>

namespace kanji {
namespace chara {

using KanjiId = int;

struct Kanji {
public:
    KanjiId id;
    s3d::String kanji;
};

struct CharaParameters {
public:
    int hp;
    int attack;
    int defence;
    int speed;
    int jump;
    int weight;
};

class IParameterizedCharacter {
public:
    virtual const Kanji& kanji() const = 0;
    virtual const CharaParameters& params() const = 0;
    virtual const CharaParameters& initialParams() const = 0;
    virtual float hpRate() const = 0;
    
    virtual void damage(int amount) = 0;
protected:
    IParameterizedCharacter() = default;
    virtual ~IParameterizedCharacter() = default;
};

class ParameterizedCharacter : public IParameterizedCharacter {
public: // static_const/enum
public: // static
public: // public function
    const Kanji& kanji() const override { return m_kanji; }
    const CharaParameters& params() const override { return m_params; }
    const CharaParameters& initialParams() const override { return m_initialParams; }
    float hpRate() const override {
        return static_cast<float>(m_params.hp) / static_cast<float>(m_initialParams.hp);
    }

    void damage(int amount) {
        if (amount <= 0) { return; }
        m_params.hp = std::max(m_params.hp - amount, 0);
    }
private: // field
private: // private function
    Kanji m_kanji;
    const CharaParameters m_initialParams;
    CharaParameters m_params;
public: // ctor/dtor
    ParameterizedCharacter(int id, const s3d::String& kanji) :
    m_kanji({
        .id = id,
        .kanji = kanji
    }),
    m_initialParams({
        .hp = 100,
        .attack = 100,
        .defence = 100,
        .speed = 100,
        .jump = 100,
        .weight = 100,
    }),
    m_params(m_initialParams) {}
    ParameterizedCharacter() :
    m_kanji({
        .id = 0,
        .kanji = U"山"
    }),
    m_initialParams({
        .hp = 100,
        .attack = 100,
        .defence = 100,
        .speed = 100,
        .jump = 100,
        .weight = 100,
    }),
    m_params(m_initialParams) {}
};


}
}


