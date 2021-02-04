#ifndef SHA256_CHECKSUM_H
#define SHA256_CHECKSUM_H

#include <cstdlib>
#include <cerrno>
#include <cstring>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <stdexcept>

// OpenSSL Library
#include <openssl/sha.h>

std::string SHA256_CHECKSUM(const char* const path);

#endif   // SHA256_CHECKSUM_H