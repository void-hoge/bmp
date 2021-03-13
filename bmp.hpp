#ifndef BMP_HPP
#define BMP_HPP

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <cassert>

namespace voidhoge::bmp {

class header {
private:
public:
	unsigned short bftype;
	unsigned int bfsize;
	unsigned short bfreserved1;
	unsigned short bfreserved2;
	unsigned int bfoffbits;

	unsigned int bisize;
	unsigned int biwidth;
	unsigned int biheight;
	unsigned short biplanes;
	unsigned short bibitcount;
	unsigned int bicompression;
	unsigned int bisizeimage;
	unsigned int bixpelspermeter;
	unsigned int biypelspermeter;
	unsigned int biclrused;
	unsigned int biclrimportant;
	header(
		unsigned short ftype,
		unsigned int fsize,
		unsigned short freserved1,
		unsigned short freserved2,
		unsigned short foffbits,
		unsigned int isize,
		unsigned int iwidth,
		unsigned int iheight,
		unsigned short iplanes,
		unsigned short ibitcount,
		unsigned int icompression,
		unsigned int isizeimage,
		unsigned int ixpelspermeter,
		unsigned int iypelspermeter,
		unsigned int iclrused,
		unsigned int iclrimportant
	) {
		bftype = ftype;
		bfsize = fsize;
		bfreserved1 = freserved1;
		bfreserved2 = freserved2;
		bfoffbits = foffbits;
		bisize = isize;
		biwidth = iwidth;
		biheight = iheight;
		biplanes = iplanes;
		bibitcount = ibitcount;
		bicompression = icompression;
		bisizeimage = isizeimage;
		bixpelspermeter = ixpelspermeter;
		biypelspermeter = iypelspermeter;
		biclrused = iclrused;
		biclrimportant = iclrimportant;
	}
	header() {
		bftype = 0;
		bfsize = 0;
		bfreserved1 = 0;
		bfreserved2 = 0;
		bfoffbits = 0;
		bisize = 0;
		biwidth = 0;
		biheight = 0;
		biplanes = 0;
		bibitcount = 0;
		bicompression = 0;
		bisizeimage = 0;
		bixpelspermeter = 0;
		biypelspermeter = 0;
		biclrused = 0;
		biclrimportant = 0;
	}
	void dump() {
		std::cout << "bftype: " << bftype << '\n';
		std::cout << "bfsize: " << bfsize << '\n';
		std::cout << "bfreserved1: " << bfreserved1 << '\n';
		std::cout << "bfreserved2: " << bfreserved2 << '\n';
		std::cout << "bfoffbits: " << bfoffbits << '\n';
		std::cout << "bisize: " << bisize << '\n';
		std::cout << "biwidth: " << biwidth << '\n';
		std::cout << "biheight:" << biheight << '\n';
		std::cout << "biplanes: " << biplanes << '\n';
		std::cout << "bibitcount: " << bibitcount << '\n';
		std::cout << "bicompression: " << bicompression << '\n';
		std::cout << "bisizeimage: " << bisizeimage << '\n';
		std::cout << "bixpelspermeter: " << bixpelspermeter << '\n';
		std::cout << "biypelspermeter: " << biypelspermeter << '\n';
		std::cout << "biclrused: " << biclrused << '\n';
		std::cout << "biclrimportant: " << biclrimportant << '\n';
	}
};

class pixel {
private:
public:
	unsigned char r;
	unsigned char g;
	unsigned char b;
	pixel(unsigned char red, unsigned char gleen, unsigned blue): r(red), g(gleen), b(blue) {};
	pixel():r(0), g(0), b(0){};
};

using grid = std::vector<std::vector<pixel>>;

class bmp_image {
protected:
	std::string filename;
	header hd;
	grid data;
	void set_conntents() {
		hd.bftype = 19778;
		hd.bfreserved1 = 0;
		hd.bfreserved2 = 0;
		hd.bfoffbits = 54;

		hd.bisize = 40;
		hd.biplanes = 1;
		hd.bibitcount = 24;
		hd.bicompression = 0;
		hd.bixpelspermeter = 0;
		hd.biypelspermeter = 0;
		hd.biclrused = 0;
		hd.biclrimportant = 0;
	}

	void set_size(unsigned int height, unsigned int width) {
		hd.biheight = height;
		hd.biwidth = width;
		hd.bisizeimage = height*width*hd.bibitcount/8;
		hd.bfsize = hd.bisizeimage + hd.bfoffbits;

		data.resize(hd.biheight);
		for (int i = 0; i < hd.biheight; i++) {
			data[i].resize(hd.biwidth);
		}
	}
public:
	bmp_image(std::string name):filename(name){};
	void change_name(std::string name) {
		this->filename = name;
	}
	void set_data(grid data) {
		this->data = data;
		set_size(data.size(), data[0].size());
	}
	void read() {
		std::ifstream ifs(filename, std::ios::in | std::ios::binary);
		if (!ifs.is_open()) {
			throw std::runtime_error("cannot open the file.");
		}
		ifs.read((char*)&hd.bftype, sizeof(hd.bftype));
		ifs.read((char*)&hd.bfsize, sizeof(hd.bfsize));
		ifs.read((char*)&hd.bfreserved1, sizeof(hd.bfreserved1));
		ifs.read((char*)&hd.bfreserved2, sizeof(hd.bfreserved2));
		ifs.read((char*)&hd.bfoffbits, sizeof(hd.bfoffbits));

		ifs.read((char*)&hd.bisize, sizeof(hd.bisize));
		ifs.read((char*)&hd.biwidth, sizeof(hd.biwidth));
		ifs.read((char*)&hd.biheight, sizeof(hd.biheight));
		ifs.read((char*)&hd.biplanes, sizeof(hd.biplanes));
		ifs.read((char*)&hd.bibitcount, sizeof(hd.bibitcount));
		ifs.read((char*)&hd.bicompression, sizeof(hd.bicompression));
		ifs.read((char*)&hd.bisizeimage, sizeof(hd.bisizeimage));
		ifs.read((char*)&hd.bixpelspermeter, sizeof(hd.bixpelspermeter));
		ifs.read((char*)&hd.biypelspermeter, sizeof(hd.biypelspermeter));
		ifs.read((char*)&hd.biclrused, sizeof(hd.biclrused));
		ifs.read((char*)&hd.biclrimportant, sizeof(hd.biclrimportant));

		data.resize(hd.biheight);
		for (int i = 0; i < hd.biheight; i++) {
			data[i].resize(hd.biwidth);
		}

		for (int i = 0; i < hd.biheight; i++) {
			for (int j = 0; j < hd.biwidth; j++) {
				ifs.read((char*)&data[i][j].b, sizeof(unsigned char));
				ifs.read((char*)&data[i][j].g, sizeof(unsigned char));
				ifs.read((char*)&data[i][j].r, sizeof(unsigned char));
			}
		}
		ifs.close();
	}
	void write() {
		std::ofstream ofs(filename, std::ios::out | std::ios::binary);
		if (this->data.empty()) {
			throw std::runtime_error("data is empty.");
		}
		if (!ofs.is_open()) {
			throw std::runtime_error("cannot open the file.");
		}

		ofs.write((char*)&hd.bftype, sizeof(hd.bftype));
		ofs.write((char*)&hd.bfsize, sizeof(hd.bfsize));
		ofs.write((char*)&hd.bfreserved1, sizeof(hd.bfreserved1));
		ofs.write((char*)&hd.bfreserved2, sizeof(hd.bfreserved2));
		ofs.write((char*)&hd.bfoffbits, sizeof(hd.bfoffbits));

		ofs.write((char*)&hd.bisize, sizeof(hd.bisize));
		ofs.write((char*)&hd.biwidth, sizeof(hd.biwidth));
		ofs.write((char*)&hd.biheight, sizeof(hd.biheight));
		ofs.write((char*)&hd.biplanes, sizeof(hd.biplanes));
		ofs.write((char*)&hd.bibitcount, sizeof(hd.bibitcount));
		ofs.write((char*)&hd.bicompression, sizeof(hd.bicompression));
		ofs.write((char*)&hd.bisizeimage, sizeof(hd.bisizeimage));
		ofs.write((char*)&hd.bixpelspermeter, sizeof(hd.bixpelspermeter));
		ofs.write((char*)&hd.biypelspermeter, sizeof(hd.biypelspermeter));
		ofs.write((char*)&hd.biclrused, sizeof(hd.biclrused));
		ofs.write((char*)&hd.biclrimportant, sizeof(hd.biclrimportant));

		assert(data.size() == hd.biheight);
		for (int i = 0; i < data.size(); i++) {
			assert(data[i].size() == hd.biwidth);
		}

		for (int i = 0; i < hd.biheight; i++) {
			for (int j = 0; j < hd.biwidth; j++) {
				ofs.write((char*)&data[i][j].b, sizeof(unsigned char));
				ofs.write((char*)&data[i][j].g, sizeof(unsigned char));
				ofs.write((char*)&data[i][j].r, sizeof(unsigned char));
			}
		}
	}
};

} /* namespace voidhoge */

#endif /* end of include guard: BMP_HPP */
