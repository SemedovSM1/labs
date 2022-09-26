#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main()
{
    // Ввод данных
    size_t number_count;
    cerr << "Enter number_count";
    cin >> number_count;

    vector<double> numbers (number_count);
    cerr << "Enter numbers:";
    for (size_t i = 0; i < number_count; i++)
    {
        cin >> numbers[i];
    }

    size_t bin_count;
    cerr << "Enter bin_count";
    cin >> bin_count;

    // Расчет гистограммы
    vector<size_t> bins (bin_count, 0);
    double min = numbers[0];
    double max = numbers[0];

    for (double number : numbers)
    {
        if (min > number)
        {
            min = number;
        }

        else if (max < number)
        {
            max = number;
        }
    }



    double bin_size = (max - min) / bin_count;
    for (size_t i = 0; i < number_count; i++)
    {
        bool found = false;
        for (size_t j = 0; j < (bin_count - 1) && !found; j++)
        {
            auto lo = min + j * bin_size;
            auto hi = min + (j + 1) * bin_size;

            if ((lo <= numbers[i]) && (numbers[i] < hi))
            {
                bins[j]++;
                found = true;
            }


        }

        if(!found)
        {
            bins[bin_count - 1]++;
        }

    }

    // Вывод данных
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

    string  draw;
    cerr << "Enter draw:";
    cin >> draw;

    string axis;
    cerr << "Enter axis:";
    cin >> axis;

    string evenly;
    cerr << "Enter evenly:";
    cin >> evenly;


    for (size_t bin : bins)
    {

        size_t height = bin;
        if (max_bin > MAX_ASTERIX) // Если масштабирование необходимо
        {
            height = MAX_ASTERIX * (static_cast<double>(bin) / max_bin);
        }

        if (bin < 100)
        {
            cout << evenly;
        }
        if (bin < 10)
        {
            cout << evenly;
        }
        cout << bin << axis;
        for (size_t i =0; i < height; i++)
        {
            cout << draw;
        }
        cout << endl;
    }

    return 0;

    double S = 0;
    double C = 0;
    for (double number : numbers)
    {
        S = S + number;
    }

    C = S / number_count;


}
