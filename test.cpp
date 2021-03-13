#include "bmp.hpp"

int main() {
	voidhoge::bmp::bmp_image hoge("mandelbrot.bmp");
	hoge.read();

	auto poyo = hoge;
	poyo.change_name("copy.bmp");
	poyo.write();
	return 0;
}
