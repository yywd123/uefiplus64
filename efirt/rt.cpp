#include <efi/rt.hpp>

#include <elf.h>

#define __attribute__(v, ...)
#include "nanoprintf.inl"
#undef __attribute__

uint16_t __attribute__((section(".reloc"))) __relocTable[5] = {0, 0, 0xa, 0, 0};

extern "C" {
char _imageBase;
Elf64_Rela _rela;
}

namespace efi {

static Handle imageHandle;
static SystemTable *systemTable;

extern "C" EFIAPI Status main();

extern "C" EFIAPI Status
_start(Handle _imageHandle, SystemTable *_systemTable) {
  imageHandle = _imageHandle;
  systemTable = _systemTable;

  uintptr_t imageBase = (uintptr_t)&_imageBase;
  Elf64_Rela *rela = &_rela;

#ifndef NDEBUG
  if (rela == nullptr) {
    print(u"error: corrupt exectutable format\r\n");
    return EFI_LOAD_ERROR;
  }
#endif

  for (uint32_t i = 0; ELF64_R_TYPE(rela[i].r_info) != R_X86_64_NONE; ++i) {
    if (ELF64_R_TYPE(rela[i].r_info) != R_X86_64_RELATIVE)
      continue;

    *(uintptr_t *)(imageBase + rela[i].r_offset) += imageBase;
  }

  systemTable->bootServices->setWatchdogTimer(0, 0, 0, nullptr);

  return main();
}

Handle getImageHandle() { return imageHandle; }

SystemTable *getSystemTable() { return systemTable; }

void print(const char16_t *msg) {
  auto stdout = systemTable->stdout;

  stdout->outputString(stdout, msg);
}

void printf(const char16_t *fmt, ...) {
  va_list ap;
  va_start(ap, fmt);

  auto putc = [](int c, void *stdout) {
    auto instance = (SimpleTextOutputProtocol *)stdout;

    char16_t buf[2] = {(char16_t)c, 0};
    instance->outputString(instance, buf);
  };

  npf_vpprintf(putc, systemTable->stdout, fmt, ap);

  va_end(ap);
}

void exit(Status status) {
  systemTable->bootServices->exit(imageHandle, status, 0, nullptr);
}

Event::TPLGuard::TPLGuard(TPL newTPL) {
  this->tpl = systemTable->bootServices->raiseTaskPriorityLevel(newTPL);
}

Event::TPLGuard::~TPLGuard() {
  systemTable->bootServices->restoreTaskPriorityLevel(this->tpl);
}

} // namespace efi