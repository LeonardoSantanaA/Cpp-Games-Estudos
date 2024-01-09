#pragma once

#include "Scene.h"
#include "../Utils/ScoreFileLoader.h"

class Screen;

class ShowScoreScene : public Scene {
public:
	virtual void Init() override;
	virtual void Update(uint32_t dt) override;
	virtual void Draw(Screen& theScreen) override;
	virtual const std::string& GetSceneName() const override;

private:
	ScoreFileLoader scoreFile;
};