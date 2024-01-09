#pragma once

#include "Scene.h"
#include "../Graphics/Color.h"
#include <SDL.h>
#include "../Input/InputController.h"

class Screen;

class SelectNameScene : public Scene {
public:
	~SelectNameScene();

	virtual void Init() override;
	virtual void Update(uint32_t dt) override;
	virtual void Draw(Screen& theScreen) override;
	virtual const std::string& GetSceneName() const override;

private:
	std::string name = "leo";
	Color nameColor = Color::White();


};