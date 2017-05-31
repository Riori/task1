#ifndef encryption_h
#define encryption_h

#include <string>

extern std::string encrypt(std::string message, std::string key, std::string iv, std::string mode);

#endif
