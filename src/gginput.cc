#include "gginput.h"
#include <thread>
#include <windows.h>
#include <iostream>
#include <cassert>

using namespace gginput;
using namespace std;

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

void GGInput::start()
{
	assert(! GGInput::m_instance && "only one instance is allowed");
	GGInput::m_instance = this;
	if (m_keyboard_enabled) {
		HHOOK hook = SetWindowsHookExA(WH_KEYBOARD_LL, winKeyboardHookProc, GetModuleHandle(NULL), 0);
		assert(hook);
		m_keyboard_hook_proc = hook;
	}
	MSG Msg;
	while (GetMessage(&Msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}
}

void GGInput::enableKeyboard()
{
	m_keyboard_enabled = true;
}

void GGInput::enableMouse()
{
	m_mouse_enabled = true;
}

void GGInput::stop()
{
	if (m_keyboard_hook_proc) {
		UnhookWindowsHookEx(m_keyboard_hook_proc);
	}
}

GGInput::~GGInput()
{
	stop();
}

LRESULT CALLBACK winKeyboardHookProc(int code, WPARAM wParam, LPARAM lParam)
{
	bool rtv = CallNextHookEx(0, code, wParam, lParam);
	if (code < 0) {
		return rtv;
	}
	KBDLLHOOKSTRUCT* key = reinterpret_cast<KBDLLHOOKSTRUCT*>(lParam);
	GGInput::instance()->handleKeyChanged(GGInputKey{ key->vkCode }, wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN);;
	return rtv;
}

GGInput* GGInput::m_instance = nullptr;

GGInput* GGInput::instance()
{
	return m_instance;
}
