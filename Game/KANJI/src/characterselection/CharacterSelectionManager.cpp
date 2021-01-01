#include "CharacterSelectionManager.hpp"

namespace kanji {
namespace cs {

CharacterSelectionManager::CharacterSelectionManager() :
    m_cursorManager{}
{}

void CharacterSelectionManager::update()
{
    m_cursorManager.update();
}

void CharacterSelectionManager::draw() const
{
    m_cursorManager.draw();
}

}
}
