#include <iostream>
#include <fstream>
#include <vector>
#include <stdexcept>
#include <algorithm>

#include "types.h"
#include "encryption.hpp"

int main(int argc, char *argv[])
{
    try
    {
        if (argc != 2)
        {
            throw std::logic_error("1 argument is required");
        }

        std::string path(argv[1]);

        std::string arg_prefix("--path=");

        auto iterators = std::mismatch(path.begin(), path.end(), arg_prefix.begin());

        if (iterators.second != arg_prefix.end())
        {
            throw std::logic_error("Not valid argument");
        }

        std::fstream f(std::string(iterators.first, path.end()));

        if (!f.good())
        {
            throw std::logic_error("File opening failed");
        }

        auto ii = std::istreambuf_iterator<char>(f.rdbuf());

        //
        std::string input;

        copy_n(ii, 6, std::back_inserter(input));
        ii++;

        std::transform(input.begin(), input.end(), input.begin(), ::toupper);

        if (input != std::string("INPUT="))
        {
            throw std::logic_error("Wrong file structure");
        }

        std::string message;

        std::getline(f, message);

        //
        auto jj = std::istreambuf_iterator<char>(f.rdbuf());

        std::string key;

        copy_n(jj, 4, std::back_inserter(key));
        jj++;

        std::transform(key.begin(), key.end(), key.begin(), ::toupper);

        if (key != std::string("KEY="))
        {
            throw std::logic_error("Wrong file structure");
        }

        std::string k;

        std::getline(f, k);

        //
        auto ll = std::istreambuf_iterator<char>(f.rdbuf());

        std::string iv;

        copy_n(ll, 3, std::back_inserter(iv));
        ll++;

        std::transform(iv.begin(), iv.end(), iv.begin(), ::toupper);

        if (iv != std::string("IV="))
        {
            throw std::logic_error("Wrong file structure");
        }

        std::string ivector;

        std::getline(f, ivector);

        //
        auto ss = std::istreambuf_iterator<char>(f.rdbuf());

        std::string mode;

        copy_n(ss, 3, std::back_inserter(iv));
        ss++;

        std::transform(mode.begin(), mode.end(), mode.begin(), ::toupper);

        if (iv != std::string("MODE="))
        {
            throw std::logic_error("Wrong file structure");
        }

        std::string m;

        std::getline(f, m);

        f.close();

        f.open(std::string(iterators.first, path.end()), std::ios_base::app);

        f << std::endl << "OUTPUT=" << encrypt(message, k, ivector, m) << std::endl;

        f.close();

    } catch (std::logic_error e) {
        std::cerr << "ERROR!!! ";
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
