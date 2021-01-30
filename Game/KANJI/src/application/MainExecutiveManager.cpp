#include "MainExecutiveManager.hpp"

namespace kanji {
namespace app {

dx::app::ExecutiveManager::Desc createExecutiveDesc() {
    const dx::app::ApplicationManager::Desc app_desc = {
        .is_close_by_escape_key = true,
        .window_title = U"漢字発見! 文字バトル",
        // .windowSize = s3d::Size(1280, 720)
        .window_size = s3d::Size(1024, 768)
    };
    
    s3d::Array<dx::app::AssetManager::FontDesc> font_descs;
    font_descs.reserve(5);
    font_descs.emplace_back(U"System", 20, s3d::Typeface::Bold);
    // font_descs.emplace_back(U"Title", 120, U"example/font/AnnyantRoman/AnnyantRoman.ttf");
    font_descs.emplace_back(U"Title", 120, U"KouzanMouhituFontOTF.otf");
    font_descs.emplace_back(U"Menu" ,  40, U"azuki.ttf");
    font_descs.emplace_back(U"Score",  36, s3d::Typeface::Bold);
    font_descs.emplace_back(U"Holder::Above", 20, U"KouzanMouhituFontOTF.otf");
    
    s3d::Array<dx::app::AssetManager::TextureDesc> texture_descs;
    texture_descs.reserve(5);
    texture_descs.emplace_back(U"Title::Logo", U"Title/Logo");
    texture_descs.emplace_back(U"Title::Bg", U"Title/Bg");
    for (const s3d::String& stage_name : { U"Notebook", U"BlackBoard", U"Scroll" }) {
        texture_descs.emplace_back(U"Stage::" + stage_name + U"::Bg", U"Stage/" + stage_name + U"/Bg");
        texture_descs.emplace_back(U"Stage::" + stage_name + U"::Block", U"Stage/" + stage_name + U"/Block");
    }
    
    s3d::Array<dx::app::AssetManager::AudioDesc> audio_descs
        = dx::app::AssetManager::AudioDesc::loadFromToml();

    return dx::app::ExecutiveManager::Desc{
        .application = app_desc,
        .font = font_descs,
        .texture = texture_descs,
        .audio = audio_descs,
    };
}

}
}
