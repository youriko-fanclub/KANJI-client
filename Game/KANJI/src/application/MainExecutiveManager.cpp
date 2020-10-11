#include "MainExecutiveManager.hpp"

namespace kanji {
namespace app {

dx::app::ExecutiveManager::Desc createExecutiveDesc() {
  const dx::app::ApplicationManager::Desc appDesc = {
    .isCloseByEscapeKey = true,
    .windowTitle = U"クレイジーサイコレズ",
    .windowSize = s3d::Size(1280, 720)
  };
  
  std::vector<dx::app::AssetManager::FontDesc> fontDescs;
  fontDescs.reserve(5);
  fontDescs.emplace_back(U"Title", 120, U"example/font/AnnyantRoman/AnnyantRoman.ttf");
  fontDescs.emplace_back(U"Menu" ,  30, s3d::Typeface::Regular);
  fontDescs.emplace_back(U"Score",  36, s3d::Typeface::Bold);
  
  return dx::app::ExecutiveManager::Desc{
    .application = appDesc,
    .font = fontDescs
  };
}

}
}
