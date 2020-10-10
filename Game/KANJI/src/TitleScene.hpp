#pragma once

#include "SceneStates.hpp"

namespace kanji {
namespace seq {


// タイトルシーン
class TitleScene : public KanjiScene {
private:

	Rect m_startButton = Rect(Arg::center = Scene::Center().movedBy(0, 0), 300, 60);
	Transition m_startTransition = Transition(0.4s, 0.2s);

	Rect m_exitButton = Rect(Arg::center = Scene::Center().movedBy(0, 100), 300, 60);
	Transition m_exitTransition = Transition(0.4s, 0.2s);

public:

	TitleScene(const InitData& init);

	void update() override;

	void draw() const override;
};


}
}
