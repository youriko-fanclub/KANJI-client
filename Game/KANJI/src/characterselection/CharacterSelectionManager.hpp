#pragma once

#include "PlayerCursorManager.hpp"

namespace kanji {
namespace cs {

class CharacterSelectionManager {
public:
    CharacterSelectionManager();
    ~CharacterSelectionManager() = default;
    
    void update();
    void draw() const;
    
private:
    dui::PlayerCursorManager m_cursorManager;
};

}
}
