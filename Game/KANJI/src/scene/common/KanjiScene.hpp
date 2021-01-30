#pragma once
#include "SceneState.hpp"
#include <functional>

namespace dx {
namespace aud {
class IAudioSource;
}
}
namespace kanji {
namespace seq {

class KanjiScene : public SceneWithData {
public: // static_const/enum
    struct TransitionInfo {
    public: // public function
        void onFadeOutBegin(State next, const Duration& transition_time, bool is_cross_fade);
        void onDestruct();
    public: // field
        State next_state;
        std::unique_ptr<std::function<void(State, const Duration&, bool)>> on_fadeout_began = nullptr;
        std::unique_ptr<std::function<void(State)>> on_destruct = nullptr;
    public: // ctor/dtor
        TransitionInfo() = default;
    };

public: // static
public: // public function
protected: // protected function
    dx::aud::IAudioSource* audioSource() { return m_audio_source; }
    void setOnDestructCallback(const std::function<void(State)>& callback);
    bool changeScene(const State_t& state, const Duration& transition_time = MillisecondsF(1000), bool is_cross_fade = false);
private: // field
    const s3d::String m_name;
    dx::aud::IAudioSource* m_audio_source;
    TransitionInfo m_transition_info;
private: // private function
public: // ctor/dtor
    KanjiScene(const InitData& init, const s3d::String& name);
    virtual ~KanjiScene();
};


}
}
