#include "BattleDesc.hpp"
#include "ParameterizedCharacter.hpp"
#include <Siv3D/Print.hpp>

using namespace s3d::Literals::FormatLiterals;

namespace kanji {
namespace battle {

/* ---------- BattlePlayerDesc ---------- */

// static ----------------------------------------
// public function -------------------------------
s3d::String BattlePlayerDesc::toString() const {
    s3d::String ret = U"{ ";
    for (int i = 0; i < m_characters.size(); ++i) {
        ret += U"{}:{}, "_fmt(i, m_characters.at(i)->kanji().kanji);
    }
    ret += U"}";
    return ret;
}
// private function ------------------------------
// ctor/dtor -------------------------------------



/* ---------- BattleDesc ---------- */

// static ----------------------------------------
// public function -------------------------------
void BattleDesc::setPlayerDesc(dx::di::PlayerId id, const std::shared_ptr<BattlePlayerDesc>& value) {
    if (m_players.contains(id)) {
        m_players.at(id) = value;
    }
    else {
        m_players.insert(std::make_pair(id, value));
    }
}

bool BattleDesc::readyToBattle() const {
    return !m_players.empty(); // TOdO:
}

void BattleDesc::dump() const {
    for (auto pid : dx::denum::elems<dx::di::PlayerId>()) {
        // std::cout
        s3d::Print
            << dx::denum::toString(pid) << U" : "
            << (m_players.contains(pid)
                ? m_players.at(pid)->toString()
                : U"NO ENTRY");
            // << std::endl;
    }
    // std::cout
    s3d::Print
        << U"TimeLimit : " << m_timeLimit_sec ;// << std::endl
    s3d::Print
        << U"StageId : " << m_stage_id.toInt() ;// << std::endl;
}
// private function ------------------------------
// ctor/dtor -------------------------------------


}
}
