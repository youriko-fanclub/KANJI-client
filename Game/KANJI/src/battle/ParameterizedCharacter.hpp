#pragma once
#include <Siv3D/String.hpp>
#include <Siv3D/Circular.hpp>
#include "IDs.hpp"
#include "MasterKanjiParam.hpp"
#include "Ability.hpp"
#include "Status.hpp"

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
    const std::unique_ptr<IAbility>& ability() const override { return m_ability; }
    const std::unique_ptr<IAbility>& initialAbility() const override { return m_initial_ability; }
    float hpRate() const override { return m_status.hpRate(); }
    bool isBurnedOut() const override { return m_status.isBurnedOut(); }

    void damage(int amount) override;
    
    // const md::MasterKanjiParam* mdKanji() const;
    // const ud::UserKanjiParam* udKanji() const;
private: // field
private: // private function
    // 戦闘中に変化しない値、攻撃力/防御力などの基礎値
    const md::MasterKanjiParam* m_md; // 種族値
    ud::UserKanjiParam m_ud; // 努力値
    
    // 動的能力値、基礎値×状態変化
    std::unique_ptr<IAbility> m_ability;
    const std::unique_ptr<IAbility> m_initial_ability;
    
    // 戦闘中に変化する値、HP/状態変化
    Status m_status;

public: // ctor/dtor
    ParameterizedCharacter(const KanjiID id);
};


}
}


