#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "Lyapunov.hpp"
#include <iostream>

int main(int argc, char* argv[])
{
	int window_size[2] = { 1000, 1000 };
	Lyapunov::Lyapunov lyapunov(window_size, "AABBB", 200, "o.png", -4.0, 4.0, -4.0, 4.0);
	lyapunov.show_param(lyapunov);

	const int n = 16;
	uint32_t ms_total = 0;
	for (int i = 0; i < n; i++)
		ms_total += lyapunov.generate_image(lyapunov);

	std::cout << "Average render time : " << ms_total / n << "ms" << std::endl;


	return 0;
}