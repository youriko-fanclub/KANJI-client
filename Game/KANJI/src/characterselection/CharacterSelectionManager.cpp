#include "CharacterSelectionManager.hpp"

namespace kanji {
namespace cs {

CharacterSelectionManager::CharacterSelectionManager() :
    m_panel_grid{},
    m_cursor_manager{}
{}

void CharacterSelectionManager::update()
{
    m_panel_grid.update();
    m_cursor_manager.update();
}

void CharacterSelectionManager::draw() const
{
    m_panel_grid.draw();
    m_cursor_manager.draw();
}

}
}
