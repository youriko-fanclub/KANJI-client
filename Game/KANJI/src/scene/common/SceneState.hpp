#pragma once

#include <Siv3D/SceneManager.hpp>
#include "DomainGameData.hpp"
#include "Enum.hpp"

namespace kanji {
namespace seq {

// シーンの名前
enum class State {
    Splash,
    Title,
    CharacterSelection,
    StageSelection,
    Battle,
    Result,

    InputDemo,
};


using SceneWithData = s3d::SceneManager<State, DomainGameData>::Scene;

}
}

namespace dx {
namespace denum {

#ifdef FUTURE_WORK // ひとまず使わないので無効にしておく
template <>
s3d::Array<kanji::seq::State> elems();
template <>
s3d::String toString(kanji::seq::State value);
#endif
template <>
std::optional<kanji::seq::State> fromString(const s3d::String& str);

}
}

