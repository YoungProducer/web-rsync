#include "sha256-checksum.h"

std::string SHA256_CHECKSUM(const char *const path)
{
  std::ifstream fp(path, std::ios::in | std::ios::binary);

  if (not fp.good())
  {
    std::ostringstream os;
    os << "Cannot open \"" << path << "\": " << std::strerror(errno) << ".";
    throw std::runtime_error(os.str());
  }

  constexpr const std::size_t buffer_size{1 << 12};
  char buffer[buffer_size];

  unsigned char hash[SHA256_DIGEST_LENGTH] = {0};

  SHA256_CTX ctx;
  SHA256_Init(&ctx);

  while (fp.good())
  {
    fp.read(buffer, buffer_size);
    SHA256_Update(&ctx, buffer, fp.gcount());
  }

  SHA256_Final(hash, &ctx);
  fp.close();

  std::ostringstream os;
  os << std::hex << std::setfill('0');

  for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i)
  {
    os << std::setw(2) << static_cast<unsigned int>(hash[i]);
  }

  return os.str();
}