#include "functions_svg.h"
#include "histogram.h"
#include <iostream>
#include <vector>
#include <string>


using namespace std;


struct Input {
    vector<double> numbers;
    size_t bin_count;
};

vector<double>
input_numbers(istream& in, size_t count)
{
    cerr << "Enter_numbers:";

    vector<double> result(count);

    for (size_t i = 0; i < count; i++)
    {
        in >> result[i];
    }

    return result;
}



Input
read_input(istream& in) {
    Input data;

    cerr << "Enter number count: ";
    size_t number_count;
    in >> number_count;

    cerr << "Enter numbers: ";
    data.numbers = input_numbers(in, number_count);

    cerr << "Enter bin_count";
    cin >> data.bin_count;

    return data;
}


vector<size_t>
make_histogram(const vector<double>& numbers, size_t bin_count)
{
     double min, max;

    find_minmax(numbers, min, max);


    vector<size_t> bins_make (bin_count, 0);

    double bin_size = (max - min) / bin_count;

    for (size_t i = 0; i < numbers.size(); i++)
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



int main()
{
    Input main;

    const auto input = read_input(cin);

    const auto bins = make_histogram(main.numbers, main.bin_count);

    show_histogram_svg(bins);

    return 0;

}
