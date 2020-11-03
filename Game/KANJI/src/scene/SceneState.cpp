#include "SceneState.hpp"

using State = kanji::seq::State;

namespace dx {
namespace denum {

#ifdef FUTURE_WORK // ひとまず使わないので無効にしておく (更新が面倒なので)
template <>
std::vector<State> elems() {
    return std::vector<State>({
        State::Splash,
        State::Title,
        State::CharacterSelection,
        State::Battle,
        State::Game,
    
        State::InputDemo,
    });
}
template <>
s3d::String toString(State value) {
    switch (value) {
    case State::Splash            : return U"Splash";
    case State::Title             : return U"Title";
    case State::CharacterSelection: return U"CharacterSelection";
    case State::Battle            : return U"Battle";
    case State::Game              : return U"Game";
    case State::InputDemo         : return U"InputDemo";
    }
}
#endif

template <>
std::optional<State> fromString(const s3d::String& str) {
    std::unordered_map<s3d::String, State> map = {
        { U"Splash"            , State::Splash             },
        { U"Title"             , State::Title              },
        { U"CharacterSelection", State::CharacterSelection },
        { U"Battle"            , State::Battle             },
        { U"Game"              , State::Game               },
        { U"InputDemo"         , State::InputDemo          },
    };
    if (map.contains(str)) {
        return std::optional<State>(map.at(str));
    }
    else {
        return std::optional<State>();
    }
}

}
}

