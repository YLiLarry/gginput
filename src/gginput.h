#include <memory>
#include <atomic>
#if WIN32
#include <Windows.h>
#endif

namespace gginput
{
	using namespace std;

	struct GGInputKey {
		unsigned int keyCode;
	};

	class GGInput {
	private:
		atomic<bool> m_keyboard_enabled;
		atomic<bool> m_mouse_enabled;
#if WIN32
		HHOOK m_keyboard_hook_proc = nullptr;
#endif
		static GGInput* m_instance;
	protected:
		virtual void handleKeyDown(GGInputKey key);
		virtual void handleKeyUp(GGInputKey key);
	public:
		GGInput() = default;
		~GGInput();
		void start();
		void stop();
		void enableKeyboard();
		void enableMouse();
		static GGInput* instance();
		virtual void handleKeyChanged(GGInputKey key, bool down);
	};
}

#if WIN32
LRESULT CALLBACK winKeyboardHookProc(int code, WPARAM wParam, LPARAM lParam);
#endif
