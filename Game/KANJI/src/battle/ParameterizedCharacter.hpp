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
private: // field
private: // private function
    Kanji m_kanji;
    CharaParameters m_params;
public: // ctor/dtor
    ParameterizedCharacter() :
    m_kanji({
        .id = 0,
        .kanji = U"山"
    }),
    m_params({
        .hp = 100,
        .attack = 100,
        .defence = 100,
        .speed = 100,
        .jump = 100,
        .weight = 100,
    }) {}
};


}
}


