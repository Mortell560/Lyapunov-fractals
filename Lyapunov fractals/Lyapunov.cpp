#include "Lyapunov.hpp"
#include <iostream>
#include <string>
#include <chrono>

namespace Lyapunov {
	Lyapunov::Lyapunov(int window_size[2], std::string sequence, int iterations, std::string output_file_name, double x_min, double x_max, double y_min, double y_max){
		this->sequence = sequence;
		this->iterations = iterations;
		this->output_file_name = output_file_name;
		this->window_size[0] = window_size[0];
		this->window_size[1] = window_size[1];
		this->x_min = x_min;
		this->x_max = x_max;
		this->y_min = y_min;
		this->y_max = y_max;
	}

	void Lyapunov::show_param(Lyapunov& lyapunov) {
		std::cout << "Current parameters: " << std::endl << "-------------------" << std::endl;
		std::cout << "sequence: " << lyapunov.sequence << std::endl;
		std::cout << "iterations: " << lyapunov.iterations << std::endl;
		std::cout << "output_file_name: " << lyapunov.output_file_name << std::endl;
		std::cout << "window_size: " << lyapunov.window_size[0] << " " << lyapunov.window_size[1] << std::endl;
		std::cout << "x_min: " << lyapunov.x_min << std::endl;
		std::cout << "x_max: " << lyapunov.x_max << std::endl;
		std::cout << "y_min: " << lyapunov.y_min << std::endl;
		std::cout << "y_max: " << lyapunov.y_max << std::endl;
		std::cout << "x_0: " << lyapunov.x_0 << std::endl;
	}

	double Lyapunov::get_r(Lyapunov& lyapunov, int i, double x, double y, double z) {
		if (lyapunov.sequence[i % lyapunov.sequence.length()] == 'A') {
			return x;
		}
		else if (lyapunov.sequence[i % lyapunov.sequence.length()] == 'B') {
			return y;
		}
		else if (lyapunov.sequence[i % lyapunov.sequence.length()] == 'C') {
			return z;
		}
		else {
			return 0;
		}
	}

	constexpr inline double Lyapunov::logistic_map(double r, double x) {
		return r * x * (1 - x);
	}

	constexpr inline double Lyapunov::exponent_logistic_map(Lyapunov& lyapunov, double x, double y, double z) {
		double x_calc = lyapunov.x_0;
		double avg = 0;
		for (int i = 0; i < lyapunov.iterations; i++) {
			double r = get_r(lyapunov, i, x, y, z);
			x_calc = logistic_map(r, x_calc);
			avg += log(abs(r * (1 - 2 * x_calc)));
		}
		return avg / lyapunov.iterations;
	}

	uint16_t Lyapunov::generate_image(Lyapunov& lyapunov) {
		// for timing
		auto start = std::chrono::high_resolution_clock::now();
		cv::Mat mat = cv::Mat::zeros(lyapunov.window_size[0], lyapunov.window_size[1], CV_8UC3);
		double x_len = lyapunov.x_max - lyapunov.x_min;
		double y_len = lyapunov.y_max - lyapunov.y_min;

		for (int i = 0; i < lyapunov.window_size[0]; i++) {
			for (int j = 0; j < lyapunov.window_size[1]; j++) {
				int blue = 0, red = 0;


				double a = (y_len / lyapunov.window_size[1]) * (lyapunov.window_size[1] - j - 1) - abs(lyapunov.y_min);
				double b = (x_len / lyapunov.window_size[0]) * i - abs(lyapunov.x_min);

				double exponent = exponent_logistic_map(lyapunov, a, b, 0);
				double scale = std::max(x_len, y_len);

				if (exponent == -1*std::numeric_limits<double>::infinity()) {
					red = 0;
					blue = 0;
				}
				else if (exponent > 0) {
					blue = (int)(255 - (256 * exponent / scale));
				}
				else if (exponent < 0) {
					red = (int)(255 + (256 * exponent / scale));
				}
				else {
					red = 255;
				}

				mat.at<cv::Vec3b>(j, i) = cv::Vec3b(blue, red , red);
			}
		}
		auto end = std::chrono::high_resolution_clock::now();
		uint16_t time_taken = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
		std::cout << "Time taken: " << time_taken << "ms" << std::endl;
		//cv::imshow("Image", mat);
		//cv::waitKey(0);
		return time_taken;
	}
};