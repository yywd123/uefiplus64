#include <efi/memory.hpp>
#include <efi/rt.hpp>

using namespace efi;

namespace efi::Memory {

void *allocPool(Memory::Type type, size_t size) {
  auto bs = getSystemTable()->bootServices;
  void *pool;

  bs->allocatePool(type, size, &pool);

#if DEBUG_MEM_LEAKCHECK == 1
  printf(u"leakcheck: alloc %p\r\n", pool);
#endif

  return pool;
}

void *sizedReallocPool(Memory::Type type, void *p, size_t oldsz, size_t newsz) {
  void *result = allocPool(type, newsz);
  memcpy(result, p, oldsz);
  freePool(p);
  return result;
}

void freePool(void *pool) { getSystemTable()->bootServices->freePool(pool); }

} // namespace efi::Memory

void memcpy(void *dest, void *src, size_t size) {
  getSystemTable()->bootServices->memcpy(dest, src, size);
}

void memmove(void *dest, void *src, size_t size) {
  // uefi的内存复制函数实现已经考虑到内存复制的方向 故可以直接调用
  memcpy(dest, src, size);
}

void memset(void *buf, int c, size_t size) {
  getSystemTable()->bootServices->memset(buf, size, c);
}