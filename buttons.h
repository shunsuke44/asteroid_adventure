#pragma once

class KeyButton {
public:
	static KeyButton* instance() { return mInstance; }
	KeyButton(const KeyButton&) = delete;
	void operator=(const KeyButton&) = delete;
	static void create();
	static void destroy();
	void drawButton(int x, int y, int idx) const;
private:
	KeyButton();
	~KeyButton();
	static KeyButton* mInstance;
	int mButtons[5];
};
