#include <efi/rt.hpp>

using namespace efi;

extern "C" EFIAPI Status main() {
  auto bs = getSystemTable()->bootServices;

  printf(u"hello world\r\n");

  //  sleep for 5s
  bs->stall(5000000);

  return EFI_SUCCESS;
}