test: test.cpp bmp.hpp
	g++ test.cpp -o test

clean:
	rm test
	rm copy*.bmp
