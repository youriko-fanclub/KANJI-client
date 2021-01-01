#pragma once

#include "PlayerCursorManager.hpp"
#include "PanelGrid.hpp"

namespace kanji {
namespace cs {

class CharacterSelectionManager {
public:
    CharacterSelectionManager();
    ~CharacterSelectionManager() = default;
    
    void update();
    void draw() const;
    
private:
    dui::PanelGrid m_panel_grid;
    dui::PlayerCursorManager m_cursor_manager;
};

}
}
