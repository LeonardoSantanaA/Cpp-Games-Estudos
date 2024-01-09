#pragma once

#include <string>
#include "InputAction.h"

class GameController;

class InputController {
public:

	InputController();
	void Init(InputAction quitAction);
	void Update(uint32_t dt);

	void SetGameController(GameController* controller);

	static inline std::string GetName() { return mName; }
	static inline void ClearName() { mName.clear(); }

private:
	InputAction mQuit;
	GameController* mnoptrCurrentController;
	static std::string mName;
};