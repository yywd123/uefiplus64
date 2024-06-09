#pragma once

#include <efi/efi.hpp>

namespace efi {

namespace Memory {

void *allocPool(Memory::Type type, size_t size);
void freePool(void *pool);

} // namespace Memory

template <typename T = void> class PoolObject {
  T *ptr;

public:
  PoolObject(){};
  PoolObject(T *p) : ptr(p){};
  ~PoolObject() { Memory::freePool((void *)ptr); };

  T *get() { return this->ptr; };
  T *&getRef() { return this->ptr; };

  T *operator->() { return this->ptr; };
};

} // namespace efi