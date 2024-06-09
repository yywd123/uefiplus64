#include <efi/rt.hpp>

#include <elf.h>

uint16_t __attribute__((section(".reloc"))) __relocTable[5] = {0, 0, 0xa, 0, 0};

extern "C" {
char _imageBase;
Elf64_Rela _rela;
}

namespace efi {

Handle imageHandle;
SystemTable *systemTable;

extern "C" EFIAPI Status main();

extern "C" EFIAPI Status
_start(Handle _imageHandle, SystemTable *_systemTable) {
  imageHandle = _imageHandle;
  systemTable = _systemTable;

  uintptr_t imageBase = (uintptr_t)&_imageBase;
  Elf64_Rela *rela = &_rela;

  if (rela == nullptr) {
    print(u"error: corrupt exectutable format\r\n");
    return EFI_LOAD_ERROR;
  }

  for (uint32_t i = 0; ELF64_R_TYPE(rela[i].r_info) != R_X86_64_NONE; ++i) {
    if (ELF64_R_TYPE(rela[i].r_info) == R_X86_64_RELATIVE)
      *(uintptr_t *)(imageBase + rela[i].r_offset) += imageBase;
  }

  return main();
}

Handle getImageHandle() { return imageHandle; }

SystemTable *getSystemTable() { return systemTable; }

void print(const char16_t *msg) {
  auto stdout = systemTable->stdout;

  stdout->outputString(stdout, msg);
}

void exit(Status status) {
  systemTable->bootServices->exit(imageHandle, status, 0, nullptr);
}

} // namespace efi