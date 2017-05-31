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

std::vector<u32> string_to_block(std::string s)
{
    std::stringstream ss(s);
    
    std::vector<u8> digits;
    char cur_symbol;
    
    while (ss >> cur_symbol)
    {
        digits.push_back(symbol_to_hex(cur_symbol));
    }
    
    if(digits.size() % 8 != 0)
        digits.push_back(0x8);
    
    while (digits.size() % 8 != 0)
    {
        digits.push_back(0x00);
    }
    
    std::vector<u32> words;
    
    for (int i=0; i<digits.size(); i+=8)
    {
        u32 res = 0;
        for (int j=0; j<8; ++j)
        {
            res |= u32(digits[i+j]) << (32 - 4*(j+1));
        }
        words.push_back(res);
    }
    
    return words;
}

u32 c(u32 a, u32 b) //шифрование
{
    return a ^ b;
}

std::string cbc(std::string message, std::string key, std::string ivector)
{
    std::vector<u32> mes;
    std::vector<u32> k;
    std::vector<u32> iv;

    mes = string_to_block(message);
    k = string_to_block(key);
    iv = string_to_block(ivector);

    std::vector<u32> res;

    u32 cur = mes[0] + iv[0];
    res.push_back(c(k[0], cur));

    for (int i = 1; i <  mes.size(); i++)
    {
        cur = mes[i] + res[i-1];
        res.push_back(c(k[i], cur));
    }

    std::stringstream ress;

    ress.fill('0');
    ress.width(2);

    for (u32 i: res)
    {
        ress << std::hex << i;
    }

    return ress.str();
}

std::string cfb(std::string message, std::string key, std::string ivector)
{
    std::vector<u32> mes;
    std::vector<u32> k;
    std::vector<u32> iv;

    mes = string_to_block(message);
    k = string_to_block(key);
    iv = string_to_block(ivector);

    std::vector<u32> res;

    u32 cur = c(iv[0], k[0]);
    res.push_back(cur+mes[0]);

    for (int i = 1; i <  mes.size(); i++)
    {
        cur = c(res[i-1], k[i]);
        res.push_back(cur+mes[i]);
    }

    std::stringstream ress;

    ress.fill('0');
    ress.width(2);

    for (u32 i: res)
    {
        ress << std::hex << i;
    }

    return ress.str();
}

std::string ofb(std::string message, std::string key, std::string ivector)
{
    std::vector<u32> mes;
    std::vector<u32> k;
    std::vector<u32> iv;

    mes = string_to_block(message);
    k = string_to_block(key);
    iv = string_to_block(ivector);

    std::vector<u32> res;

    u32 cur = c(iv[0], k[0]);
    res.push_back(cur+mes[0]);

    for (int i = 1; i <  mes.size(); i++)
    {
        cur = c(cur, k[i]);
        res.push_back(cur+mes[i]);
    }

    std::stringstream ress;

    ress.fill('0');
    ress.width(2);

    for (u32 i: res)
    {
        ress << std::hex << i;
    }

    return ress.str();
}

std::string encrypt(std::string message, std::string key, std::string iv, std::string mode)
{
    if (message.size() != key.size())
        throw std::logic_error("Wrong legth!");

    if (string.compare(mode, 'CBC', 3) == 0)
        return cbc(message, key, iv);
    else if (string.compare(mode, 'CFB', 3) == 0)
        return cfb(message, key, iv);
    else if (string.compare(mode, 'OFB', 3) == 0)
        return ofb(message, key, iv);
    else
        throw std::logic_error("Wrong mode!");
};
