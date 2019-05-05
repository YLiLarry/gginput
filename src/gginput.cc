#include "gginput.h"

using namespace std;
using namespace gginput;

void GGInput::handleKeyChanged(GGInputKey key, bool down)
{
	if (down) {
		handleKeyDown(key);
	} else {
		handleKeyUp(key);
	}
}

void GGInput::handleKeyDown(GGInputKey key)
{
}


void GGInput::handleKeyUp(GGInputKey key)
{
}

void GGInput::enableKeyboard()
{
	m_keyboard_enabled = true;
}

void GGInput::enableMouse()
{
	m_mouse_enabled = true;
}

GGInput::~GGInput()
{
	stop();
}

GGInput* GGInput::m_instance = nullptr;

GGInput* GGInput::instance()
{
	return m_instance;
}
