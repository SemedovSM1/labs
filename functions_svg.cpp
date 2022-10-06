
#include "functions_svg.h"

#include <windows.h>

#include "functions_svg.h"
#include "histogram.h"
#include <iostream>
#include <vector>
#include <string>
#include<cstdio>
#include <sstream>
#include <string>

string make_info_text() {
    DWORD WINAPI GetVersion(void);
    stringstream buffer;
    const auto R = GetVersion();
    printf("n = %lu\n", R);
    printf("n = %lx\n", R);
    DWORD mask = 0b00000000'00000000'11111111'11111111;
    DWORD version = R & mask;
    printf("ver = %lu\n", version);
    DWORD platform = R >> 16;
    printf("ver2 = %lu\n", platform);
    DWORD mask2 = 0b00000000'11111111;
    DWORD version_major = version & mask2;
    printf("version_major = %lu\n", version_major);
    DWORD version_minor = version >> 8;
    printf("version_minor = %lu\n", version_minor);
    DWORD build;
    if ((R & 0x80000000) == 0)
    {
        build = platform;
        printf("build = %lu\n", build);

    }
    buffer << "Windows" << " " << "v" << " " << version_major << "." << version_minor << " " << "(build" << " " << build << ")" << endl;
    TCHAR storage[MAX_COMPUTERNAME_LENGTH + 1];
    DWORD  bufCharCount = MAX_COMPUTERNAME_LENGTH + 1;
    GetComputerNameA(LPSTR(storage), &bufCharCount);
    buffer << "Computer name:" << " " << storage;
    return buffer.str();
}

void
svg_begin(double width, double height) {
    cout << "<?xml version='1.0' encoding='UTF-8'?>\n";
    cout << "<svg ";
    cout << "width='" << width << "' ";
    cout << "height='" << height << "' ";
    cout << "viewBox='0 0 " << width << " " << height << "' ";
    cout << "xmlns='http://www.w3.org/2000/svg'>\n";
}

void
svg_end() {
    cout << "</svg>\n";
}

void
svg_text(double left, double baseline, string text) {
    cout << "<text x='" << left << "' y='" << baseline << "' >" << text << "</text>";
}

void svg_rect(double x, double y, double width, double height, string stroke, string fill)
{
   cout << "<rect x='" << x << "' y='" << y << "' width='" << width << "' height='" << height
        << "' stroke='" << stroke << "' fill='" << fill << "' />";
}

void
show_histogram_svg(const vector<size_t>& bins) {

    const auto IMAGE_WIDTH = 400;
    const auto IMAGE_HEIGHT = 300;
    const auto TEXT_LEFT = 20;
    const auto TEXT_BASELINE = 20;
    const auto TEXT_WIDTH = 50;
    const auto BIN_HEIGHT = 30;
    const auto BLOCK_WIDTH = 10;

    svg_begin(IMAGE_WIDTH, IMAGE_HEIGHT);

    size_t max_bin = bins[0];
    for (size_t bin : bins)
    {
        if (bin > max_bin)
        {
            max_bin = bin;
        }
    }
    const bool scaling = max_bin* BLOCK_WIDTH > IMAGE_WIDTH - TEXT_WIDTH;
    for (size_t bin : bins)
    {
        size_t height = bin;

        if (scaling)
        {
            const double scaling_check = (double)(IMAGE_WIDTH - TEXT_WIDTH )/ (max_bin* BLOCK_WIDTH);
            height = bin * scaling_check;
        }
        const double bin_width = BLOCK_WIDTH * height;
    }



    svg_text(TEXT_LEFT, TEXT_BASELINE + 100, to_string(bins[0]) + make_info_text());
    svg_rect(TEXT_WIDTH, 0, bins[0] * BLOCK_WIDTH, BIN_HEIGHT, "blue", "#aaffaa");

    double top = 0;
     for (size_t bin : bins) {
     const double bin_width = BLOCK_WIDTH * bin;
     svg_text(TEXT_LEFT, top + TEXT_BASELINE, to_string(bin));
     svg_rect(TEXT_WIDTH, top, bin_width, BIN_HEIGHT, "blue", "#aaffaa");
     top += BIN_HEIGHT;
   }

    svg_end();
}
