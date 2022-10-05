#include "functions_svg.h"
#include "histogram.h"
#include <iostream>
#include <vector>
#include <string>
#include<cstdio>
#include <sstream>
#include <string>
#include <windows.h>

DWORD WINAPI GetVersion(void);

using namespace std;






vector<double>
input_numbers(size_t count)
{
    cerr << "Enter_numbers:";

    vector<double> result(count);

    for (size_t i = 0; i < count; i++)
    {
        cin >> result[i];
    }

    return result;
}



vector<size_t>
make_histogram(const vector<double>& numbers, size_t bin_count, size_t number_count, double min, double max)
{
    vector<size_t> bins_make (bin_count, 0);

    double bin_size = (max - min) / bin_count;

    for (size_t i = 0; i < number_count; i++)
    {
        bool found = false;
        for (size_t j = 0; j < (bin_count - 1) && !found; j++)
        {
            double lo = min + j * bin_size;
            double hi = min + (j + 1) * bin_size;

            if ((lo <= numbers[i]) && (numbers[i] < hi))
            {
                bins_make[j]++;
                found = true;
            }
        }

        if(!found)
        {
            bins_make[bin_count - 1]++;
        }

    }

   return bins_make;
}



 show_histogram_text(const vector<size_t> bins)

{
    const size_t SCREEN_WIDTH = 80;
    const size_t MAX_ASTERIX = SCREEN_WIDTH - 3 - 1;

    size_t max_bin = bins[0];
    for (size_t bin : bins)
    {
        if (bin > max_bin)
        {
            max_bin = bin;
        }
    }



    for (size_t bin : bins)
    {

        size_t height = bin;
        if (max_bin > MAX_ASTERIX) // Если масштабирование необходимо
        {
            height = MAX_ASTERIX * (static_cast<double>(bin) / max_bin);
        }

        if (bin < 100)
        {
            cout << ' ';
        }
        if (bin < 10)
        {
            cout << ' ';
        }
        cout << bin << '|';
        for (size_t i =0; i < height; i++)
        {
            cout << '*';
        }
        cout << endl;
    }

}

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





int main()
{

    size_t number_count;
    cerr << "Enter number_count";
    cin >> number_count;

    const auto numbers = input_numbers(number_count);

    size_t bin_count;
    cerr << "Enter bin_count";
    cin >> bin_count;

    double min, max;

    find_minmax(numbers, min, max);

    const auto bins = make_histogram(numbers, bin_count, number_count, min, max);

    svg_text;

    make_info_text();
    show_histogram_svg(bins);

    return 0;

}
