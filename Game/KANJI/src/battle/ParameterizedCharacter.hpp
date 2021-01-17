#pragma once
#include <Siv3D/String.hpp>
#include <Siv3D/Circular.hpp>
#include "IDs.hpp"
#include "MasterKanjiParam.hpp"

namespace kanji {
namespace chara {

struct Kanji {
public:
    KanjiID id;
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
    virtual bool isBurnedOut() const = 0;
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
    static std::shared_ptr<ParameterizedCharacter> createShared(const md::MasterKanjiParam* md) {
        return std::make_shared<ParameterizedCharacter>(md->id(), md->character());
    }
public: // public function
    const Kanji& kanji() const override { return m_kanji; }
    bool isBurnedOut() const override { return m_is_burned_out; }
    const CharaParameters& params() const override { return m_params; }
    const CharaParameters& initialParams() const override { return m_initial_params; }
    float hpRate() const override {
        return static_cast<float>(m_params.hp) / static_cast<float>(m_initial_params.hp);
    }

    void damage(int amount) override;
private: // field
private: // private function
    Kanji m_kanji;
    bool m_is_burned_out;
    const CharaParameters m_initial_params;
    CharaParameters m_params;
public: // ctor/dtor
    ParameterizedCharacter(const KanjiID id, const s3d::String& kanji) :
    m_kanji({
        .id = id,
        .kanji = kanji
    }),
    m_initial_params({
        .hp = 100,
        .attack = 100,
        .defence = 100,
        .speed = 100,
        .jump = 100,
        .weight = 100,
    }),
    m_params(m_initial_params) {}
    ParameterizedCharacter() :
    m_kanji({
        .id = KanjiID(0),
        .kanji = U"山"
    }),
    m_initial_params({
        .hp = 100,
        .attack = 100,
        .defence = 100,
        .speed = 100,
        .jump = 100,
        .weight = 100,
    }),
    m_params(m_initial_params) {}
};


}
}


