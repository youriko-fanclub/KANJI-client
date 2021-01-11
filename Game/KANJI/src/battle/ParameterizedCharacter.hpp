#pragma once
#include <Siv3D/String.hpp>
#include <Siv3D/Circular.hpp>
#include "IDs.hpp"
#include "MasterKanjiParam.hpp"
#include "Ability.hpp"

namespace kanji {
namespace chara {


class IParameterizedCharacter {
public:
    virtual const s3d::String& chara() const = 0;
    virtual bool isBurnedOut() const = 0;
    virtual const std::unique_ptr<IAbility>& ability() const = 0;
    virtual const std::unique_ptr<IAbility>& initialAbility() const = 0;
    virtual float hpRate() const = 0;
    
    virtual void damage(int amount) = 0;
protected:
    IParameterizedCharacter() = default;
    virtual ~IParameterizedCharacter() = default;
};

class ParameterizedCharacter : public IParameterizedCharacter {
public: // static_const/enum
public: // static
    static std::shared_ptr<IParameterizedCharacter> createShared(KanjiID id) {
        return std::make_shared<ParameterizedCharacter>(id);
    }
public: // public function
    const s3d::String& chara() const override { return m_md->character(); }
    bool isBurnedOut() const override { return m_is_burned_out; }
    const std::unique_ptr<IAbility>& ability() const override { return m_ability; }
    const std::unique_ptr<IAbility>& initialAbility() const override { return m_initial_ability; }
    float hpRate() const override {
        return static_cast<float>(m_hp) / static_cast<float>(m_initial_hp);
    }

    void damage(int amount) override;
    
    // const md::MasterKanjiParam* mdKanji() const;
    // const ud::UserKanjiParam* udKanji() const;
private: // field
private: // private function
    bool m_is_burned_out = false;
    const md::MasterKanjiParam* m_md;
    ud::UserKanjiParam m_ud;
    int m_hp = 100;
    const int m_initial_hp = 100;
    std::unique_ptr<IAbility> m_ability;
    const std::unique_ptr<IAbility> m_initial_ability;

public: // ctor/dtor
    ParameterizedCharacter(const KanjiID id);
};


}
}


