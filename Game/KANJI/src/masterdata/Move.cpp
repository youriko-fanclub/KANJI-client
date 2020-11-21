#include "Move.hpp"
#include "PhysicalMove.hpp"

namespace kanji {
namespace md {

/* ---------- MasterRepository ---------- */

// static ----------------------------------------
// public function -------------------------------
// private function ------------------------------
// ctor/dtor -------------------------------------
MasterRepository::MasterRepository() {
    // TOdO: デバッグ用
    std::vector<battle::MomentaryMove> moments;
    float t = 0.f;
    moments.emplace_back(t, 50.f, s3d::Circular(-35, 500), s3d::RectF(s3d::Arg::center(0, 0), s3d::Size(60, 60)));
    t += 0.1f;
    moments.emplace_back(t, 50.f, s3d::Circular(-35, 500), s3d::RectF(s3d::Arg::center(20, 0), s3d::Size(60, 60)));
    t += 0.2f;
    moments.emplace_back(t, 50.f, s3d::Circular(-35, 500), s3d::RectF(s3d::Arg::center(40, 0), s3d::Size(60, 60)));
    t += 0.2f;
    moments.emplace_back(t, 50.f, s3d::Circular(-35, 500), s3d::RectF(s3d::Arg::center(60, 0), s3d::Size(60, 60)));
    t += 0.1f;
    moments.emplace_back(t, 50.f, s3d::Circular(-35, 500), s3d::RectF(s3d::Arg::center(60, 0), s3d::Size(60, 60)));
    t += 0.7f;
    moments.emplace_back(t, 50.f, s3d::Circular(-35, 500), s3d::RectF(s3d::Arg::center(40, 0), s3d::Size(60, 60)));
    t += 0.8f;
    moments.emplace_back(t, 50.f, s3d::Circular(-35, 500), s3d::RectF(s3d::Arg::center(30, 0), s3d::Size(60, 60)));
    t += 0.3f;
    moments.emplace_back(t, 50.f, s3d::Circular(-35, 500), s3d::RectF(s3d::Arg::center(10, 0), s3d::Size(60, 60)));
    t += 0.2f;
    moments.emplace_back(t, 50.f, s3d::Circular(-35, 500), s3d::RectF(s3d::Arg::center( 0, 0), s3d::Size(60, 60)));
    const MoveId id = 0;
    m_masterdata.insert(std::make_pair(id,
        std::make_shared<Move>(id, U"拳", std::make_shared<battle::Trajectory>(moments))));
}

}
}
