#include "functions_svg.h"
#include "histogram.h"
#include <iostream>
#include <vector>
#include <string>

#include <sstream>
#include <string>


#include <curl/curl.h>
using namespace std;




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
read_input(istream& in, bool prompt) {

    Input data;


	if (prompt) {
		cerr << "Enter number_count: ";
	}

    size_t number_count;
    in >> number_count;

    if (prompt) {
		cerr << "Enter numbers: ";
	}

    data.numbers = input_numbers(in, number_count);

   if (prompt) {
		cerr << "Enter bin_count: ";
	}

    cin >> data.bin_count;

    return data;
}


vector<size_t>
make_histogram(Input make)
{
     double min, max;

    find_minmax(make.numbers, min, max);


    vector<size_t> bins_make (make.bin_count, 0);

    double bin_size = (max - min) / make.bin_count;

    for (size_t i = 0; i < make.numbers.size(); i++)
    {
        bool found = false;
        for (size_t j = 0; j < (make.bin_count - 1) && !found; j++)
        {
            double lo = min + j * bin_size;
            double hi = min + (j + 1) * bin_size;

            if ((lo <= make.numbers[i]) && (make.numbers[i] < hi))
            {
                bins_make[j]++;
                found = true;
            }
        }

        if(!found)
        {
            bins_make[make.bin_count - 1]++;
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


size_t
write_data(void* items, size_t item_size, size_t item_count, void* ctx) {

    size_t data_size = item_size * item_count;

    stringstream* buffer = reinterpret_cast<stringstream*>(ctx);

    buffer->write(reinterpret_cast<const char*>(items), data_size);

    return data_size;
}


Input
download(const string& address) {
    stringstream buffer;




      CURL *curl = curl_easy_init();

      if(curl)
      {
       CURLcode res;
       curl_easy_setopt(curl, CURLOPT_URL, "https://example.com");
       res = curl_easy_perform(curl);
       curl_easy_cleanup(curl);

         if (res != CURLE_OK) {
            cerr << curl_easy_strerror(res);
            exit(1);
        }
      }



    curl_global_init(CURL_GLOBAL_ALL);


    return read_input(buffer, false);
}




int
main(int argc, char* argv[]) {
    Input input;
    if (argc > 1) {
        input = download(argv[1]);
    } else {
        input = read_input(cin, true);
    }

    const auto bins = make_histogram(input);
    show_histogram_svg(bins);
}

