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
    const s3d::Size size(3, 3);
    float t = 0.f;
    t += 0.0f / 40.f; moments.emplace_back(t, 50.f, s3d::Circular(-35, 500), s3d::RectF(s3d::Arg::center(0.5, 0), size));
    t += 2.0f / 40.f; moments.emplace_back(t, 50.f, s3d::Circular(-35, 500), s3d::RectF(s3d::Arg::center(1.5, 0), size));
    t += 2.0f / 40.f; moments.emplace_back(t, 50.f, s3d::Circular(-35, 500), s3d::RectF(s3d::Arg::center(2.5, 0), size));
    t += 0.5f / 40.f; moments.emplace_back(t, 50.f, s3d::Circular(-35, 500), s3d::RectF(s3d::Arg::center(3.5, 0), size));
    t += 0.5f / 40.f; moments.emplace_back(t, 50.f, s3d::Circular(-35, 500), s3d::RectF(s3d::Arg::center(4.0, 0), size));
    t += 7.0f / 40.f; moments.emplace_back(t, 50.f, s3d::Circular(-35, 500), s3d::RectF(s3d::Arg::center(3.5, 0), size));
    t += 8.0f / 40.f; moments.emplace_back(t, 50.f, s3d::Circular(-35, 500), s3d::RectF(s3d::Arg::center(2.5, 0), size));
    t += 3.0f / 40.f; moments.emplace_back(t, 50.f, s3d::Circular(-35, 500), s3d::RectF(s3d::Arg::center(2.0, 0), size));
    t += 2.0f / 40.f; moments.emplace_back(t, 50.f, s3d::Circular(-35, 500), s3d::RectF(s3d::Arg::center(1.0, 0), size));
    t += 1.0f / 40.f; moments.emplace_back(t, 50.f, s3d::Circular(-35, 500), s3d::RectF(s3d::Arg::center(0.5, 0), size));
    const MoveId id = 0;
    m_masterdata.insert(std::make_pair(id,
        std::make_shared<Move>(id, U"拳", std::make_shared<battle::Trajectory>(moments))));
}

}
}
