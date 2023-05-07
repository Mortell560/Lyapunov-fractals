#pragma once
#include <string>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

namespace Lyapunov {
	class Lyapunov {
	public:
		Lyapunov(int window_size[2], std::string sequence = "AB", int iterations = 200, std::string output_file_name = "o.png", double x_min = -4.0, double x_max = 4, double y_min = -4, double y_max = 4);
		void show_param(Lyapunov& lyapunov);
		double get_r(Lyapunov& lyapunov, int i, double x, double y, double z = 0);
		constexpr inline double logistic_map(double r, double x);
		constexpr inline double exponent_logistic_map(Lyapunov& lyapunov, double x, double y, double z = 0);
		uint16_t generate_image(Lyapunov& lyapunov);

	private:
		std::string sequence;
		int iterations;
		std::string output_file_name;
		int window_size[2];
		double x_min;
		double x_max;
		double y_min;
		double y_max;
		double x_0 = 0.5;
	};
};