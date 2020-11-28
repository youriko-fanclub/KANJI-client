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
    
    std::vector<dx::app::AssetManager::FontDesc> font_descs;
    font_descs.reserve(5);
    font_descs.emplace_back(U"System", 20, s3d::Typeface::Bold);
    // font_descs.emplace_back(U"Title", 120, U"example/font/AnnyantRoman/AnnyantRoman.ttf");
    font_descs.emplace_back(U"Title", 120, U"KouzanMouhituFontOTF.otf");
    font_descs.emplace_back(U"Menu" ,  40, U"azuki.ttf");
    font_descs.emplace_back(U"Score",  36, s3d::Typeface::Bold);
    font_descs.emplace_back(U"Holder::Above", 20, U"KouzanMouhituFontOTF.otf");
    
    std::vector<dx::app::AssetManager::TextureDesc> texture_descs;
    texture_descs.reserve(5);
    texture_descs.emplace_back(U"Title::Logo", U"Title/Logo");
    texture_descs.emplace_back(U"Title::Bg", U"Title/Bg");
    
    std::vector<dx::app::AssetManager::AudioDesc> audio_descs;
    audio_descs.reserve(30);
    using AudioType = dx::app::AssetManager::AudioDesc::Type;
    audio_descs.emplace_back(AudioType::BGM, U"Title");
    audio_descs.emplace_back(AudioType::BGM, U"CharaSelect");
    audio_descs.emplace_back(AudioType::BGM, U"Battle01");
    audio_descs.emplace_back(AudioType::BGM, U"Battle02");
    audio_descs.emplace_back(AudioType::BGM, U"Battle03");
    audio_descs.emplace_back(AudioType::BGM, U"Result");
    audio_descs.emplace_back(AudioType::SE, U"System/Decide");
    audio_descs.emplace_back(AudioType::SE, U"System/Cancel");
    audio_descs.emplace_back(AudioType::SE, U"System/Choose");
    audio_descs.emplace_back(AudioType::SE, U"Battle/Game/GameStart");
    audio_descs.emplace_back(AudioType::SE, U"Battle/Game/GameSet");
    audio_descs.emplace_back(AudioType::SE, U"Battle/Chara/Appear");
    audio_descs.emplace_back(AudioType::SE, U"Battle/Chara/BurnOut");
    audio_descs.emplace_back(AudioType::SE, U"Battle/Chara/CharaRotation");
    audio_descs.emplace_back(AudioType::SE, U"Battle/Chara/Damage");
    audio_descs.emplace_back(AudioType::SE, U"Battle/Chara/GetRadicalSimple");
    audio_descs.emplace_back(AudioType::SE, U"Battle/Chara/GetRadicalGorgeous");
    audio_descs.emplace_back(AudioType::SE, U"Battle/Move/Normal");
    audio_descs.emplace_back(AudioType::SE, U"Battle/Move/NormalWithRadical");
    audio_descs.emplace_back(AudioType::SE, U"Battle/Move/Special");
    audio_descs.emplace_back(AudioType::SE, U"Battle/Move/Special/Aburu");
    audio_descs.emplace_back(AudioType::SE, U"Battle/Move/Special/Arashi");
    audio_descs.emplace_back(AudioType::SE, U"Battle/Move/Special/Hoshi");
    audio_descs.emplace_back(AudioType::SE, U"Battle/Move/Special/Ikaduchi");
    audio_descs.emplace_back(AudioType::SE, U"Battle/Move/Special/KatamariRolling");
    audio_descs.emplace_back(AudioType::SE, U"Battle/Move/Special/KatamariScrape");
    audio_descs.emplace_back(AudioType::SE, U"Battle/Move/Special/Kiri");
    audio_descs.emplace_back(AudioType::SE, U"Battle/Move/Special/KomainuBark");
    audio_descs.emplace_back(AudioType::SE, U"Battle/Move/Special/KomainuGrowl");
    audio_descs.emplace_back(AudioType::SE, U"Battle/Move/Special/Kuruu");
    audio_descs.emplace_back(AudioType::SE, U"Battle/Move/Special/Noroi");
    audio_descs.emplace_back(AudioType::SE, U"Battle/Move/Special/Tagane");
    audio_descs.emplace_back(AudioType::SE, U"Battle/Move/Special/Toki");

    return dx::app::ExecutiveManager::Desc{
        .application = app_desc,
        .font = font_descs,
        .texture = texture_descs,
        .audio = audio_descs,
    };
}

}
}
