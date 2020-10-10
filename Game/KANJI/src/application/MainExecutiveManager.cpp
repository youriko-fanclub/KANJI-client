#include "MainExecutiveManager.hpp"

namespace kanji {
namespace app {

dx::app::ExecutiveManager::Desc createExecutiveDesc() {
  const dx::app::ApplicationManager::Desc appDesc = {
    .isCloseByEscapeKey = true,
    .windowTitle = U"クレイジーサイコレズ",
    .windowSize = s3d::Size(1280, 720)
  };
  return dx::app::ExecutiveManager::Desc{
    .application = appDesc
  };
}

}
}
