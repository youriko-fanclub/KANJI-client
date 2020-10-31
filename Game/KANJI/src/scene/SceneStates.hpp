#pragma once

#include <Siv3D/SceneManager.hpp>
#include "DomainGameData.hpp"

namespace kanji {
namespace seq {

// シーンの名前
enum class State {
    Splash,
    Title,
    CharacterSelection,
    Battle,
    Game,
 
    InputDemo,
};


using KanjiScene = s3d::SceneManager<State, DomainGameData>::Scene;

}
}

