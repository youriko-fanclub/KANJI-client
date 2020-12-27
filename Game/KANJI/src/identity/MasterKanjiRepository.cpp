#include "MasterKanjiRepository.hpp"

// TOdO: このファイル自体を自動生成する?

namespace {

std::pair<kanji::chara::KanjiID, std::unique_ptr<kanji::md::MasterKanji>> createPair(int id_int, const s3d::String& character) {
    kanji::chara::KanjiID id(id_int);
    return std::make_pair(id, std::make_unique<kanji::md::MasterKanji>(id, character));
}

}

namespace kanji {
namespace md {

void MasterKanjiRepository::initialize() {
    // TOdO: toml読み込みにする
    m_data.insert(createPair( 0, U"山"));
    m_data.insert(createPair( 1, U"斬"));
    m_data.insert(createPair( 2, U"王"));
    m_data.insert(createPair( 3, U"包"));
    m_data.insert(createPair( 4, U"分"));
    m_data.insert(createPair( 5, U"鬼"));
    m_data.insert(createPair( 6, U"工"));
    m_data.insert(createPair( 7, U"詛"));
    m_data.insert(createPair( 8, U"寺"));
    m_data.insert(createPair( 9, U"白"));
    m_data.insert(createPair(10, U"生"));
    m_data.insert(createPair(11, U"田"));
}


}
}
