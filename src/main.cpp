#include <efi/rt.hpp>

using namespace efi;

extern "C" EFIAPI Status main() {
  auto bs = getSystemTable()->bootServices;

  bs->setWatchdogTimer(0, 0, 0, nullptr);

  print(u"hello world\r\n");

  return 0;
}