#include <efi/rt.hpp>

using namespace efi;

extern "C" EFIAPI Status main() {
  print(u"hello world\r\n");
  return 0;
}