#include <iostream>
#include <vector>
#include <string>

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




void
find_minmax(const vector<double>& numbers, double& min, double& max)
{
    min = numbers[0];
    max + numbers[0];

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

    return ;
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
        if (max_bin > MAX_ASTERIX) // ���� ��������������� ����������
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

void svg_rect(double x, double y, double width, double height,
        string stroke = "black", string fill = "black")
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



    svg_text(TEXT_LEFT, TEXT_BASELINE, to_string(bins[0]));
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

    show_histogram_svg(bins);

    return 0;

}
