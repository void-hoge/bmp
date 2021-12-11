#include "bmp.hpp"

namespace bmp = voidhoge::bmp;

int main() {
	bmp::bmp_image hoge = bmp::bmp_image("mandelbrot.bmp");
	bmp::bmp_image poyo = bmp::bmp_image(hoge.data());
	hoge.save("copy1.bmp");
	poyo.save("copy2.bmp");
	return 0;
}
