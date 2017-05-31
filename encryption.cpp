#include "encryption.hpp"

#include <vector>
#include <sstream>

#include "types.h"

u8 symbol_to_hex(char c)
{
    if (c >= 'a' && c <= 'f')
    {
        return (char) 10 + c - 'a';
    }
    if (c >= 'A' && c <= 'F')
    {
        return (char) 10 + c - 'A';
    }
    if (c >= '0' && c <= '9')
    {
        return c - '0';
    }
    throw std::logic_error("Invalid hex character");
}

std::string cbc(std::string message, std::string key, std::string iv)
{

}

std::string cfb(std::string message, std::string key, std::string iv)
{

}

std::string ofb(std::string message, std::string key, std::string iv)

std::string encrypt(std::string message, std::string key, std::string iv, std::string mode)
{
    std::stringstream ss(message);
    std::stringstream kk(key);

    std::vector<u8> mdigits;
    char cur_symbol;

    while (ss >> cur_symbol)
    {
        mdigits.push_back(symbol_to_hex(cur_symbol));
    }

    std::vector<u8> kdigits;
    char curr_symbol;

    while (kk >> curr_symbol)
    {
        mdigits.push_back(symbol_to_hex(curr_symbol));
    }

    if (mdigits.size() != kdigits.size())
    {
        throw std::logic_error("Wrong message length");
    }

    if ()


}