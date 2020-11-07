#include "BattlePlayer.hpp"
#include "BattleDesc.hpp"
#include "ParameterizedCharacter.hpp"

namespace kanji {
namespace battle {


/* ---------- BattlePlayerManager ---------- */

// static ----------------------------------------
// public function -------------------------------
// private function ------------------------------
// ctor/dtor -------------------------------------
BattlePlayer::BattlePlayer(dx::di::PlayerId pid, const std::shared_ptr<BattlePlayerDesc>& desc) :
m_pid(pid),
m_characters(desc->characters()) {}


}
}
