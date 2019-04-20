#include <gginput.h>
#include <thread>
#include <condition_variable>
#include <mutex>
#include <iostream>

using namespace std;
using namespace gginput;

class ExampleGGInput : public GGInput
{
	void handleKeyDown(GGInputKey key) override {
		cout << key.keyCode << endl;
	}
};

int main()
{
	mutex cv_mutex;
	condition_variable cv;
	unique_lock<mutex> cv_lock(cv_mutex);
	ExampleGGInput gg;
	gg.enableKeyboard();
	gg.start();
	cv.wait(cv_lock);
}
