#include "MainExecutiveManager.hpp"

namespace kanji {
namespace app {

dx::app::ExecutiveManager::Desc createExecutiveDesc() {
  const dx::app::ApplicationManager::Desc appDesc = {
    .isCloseByEscapeKey = true,
    .windowTitle = U"漢字発見! 文字バトル",
    // .windowSize = s3d::Size(1280, 720)
    .windowSize = s3d::Size(1024, 768)
  };
  
  std::vector<dx::app::AssetManager::FontDesc> fontDescs;
  fontDescs.reserve(5);
  // fontDescs.emplace_back(U"Title", 120, U"example/font/AnnyantRoman/AnnyantRoman.ttf");
  fontDescs.emplace_back(U"Title", 120, U"KouzanMouhituFontOTF.otf");
  fontDescs.emplace_back(U"Menu" ,  40, U"azuki.ttf");
  fontDescs.emplace_back(U"Score",  36, s3d::Typeface::Bold);
  
  std::vector<dx::app::AssetManager::TextureDesc> textureDescs;
  textureDescs.reserve(5);
  textureDescs.emplace_back(U"Title::Logo", U"Title/Logo");
  textureDescs.emplace_back(U"Title::Bg", U"Title/Bg");

  return dx::app::ExecutiveManager::Desc{
    .application = appDesc,
    .font = fontDescs,
    .texture = textureDescs
  };
}

}
}
