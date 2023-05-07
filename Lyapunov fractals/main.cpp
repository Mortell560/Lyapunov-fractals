#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "Lyapunov.hpp"

int main(int argc, char* argv[])
{
	int window_size[2] = { 1000, 1000 };
	Lyapunov::Lyapunov lyapunov(window_size, "AABBB", 200, "o.png", -4.0, 4.0, -4.0, 4.0);
	lyapunov.show_param(lyapunov);
	lyapunov.generate_image(lyapunov);

	return 0;
}