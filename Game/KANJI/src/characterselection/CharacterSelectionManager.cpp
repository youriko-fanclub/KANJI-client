#include "CharacterSelectionManager.hpp"

#include <Siv3D/Keyboard.hpp>

namespace kanji {
namespace cs {

CharacterSelectionManager::CharacterSelectionManager() :
    m_panel_grid{ { 50, 50 },  { 100, 100 } , 5 , 1 },
    m_cursor_manager{}
{
    // ファイルから読み込みたいよね
    m_panel_grid.Add(U"安");
    m_panel_grid.Add(U"達");
    m_panel_grid.Add(U"曜");
    m_panel_grid.Add(U"梨");
    m_panel_grid.Add(U"子");
}

void CharacterSelectionManager::update()
{
    m_panel_grid.update();
    m_cursor_manager.update();
    
    if (s3d::KeyA.up()) {
        m_panel_grid.Add(U"王");
    }
}

void CharacterSelectionManager::draw() const
{
    m_panel_grid.draw();
    m_cursor_manager.draw();
}

}
}
