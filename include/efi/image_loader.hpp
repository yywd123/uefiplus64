#pragma once

#include <efi/efi.hpp>

#define EFI_LOADED_IMAGE_PROTOCOL_GUID                                         \
  {                                                                            \
    0x5b1b31a1, 0x9562, 0x11d2, {                                              \
      0x8e, 0x3f, 0x00, 0xa0, 0xc9, 0x69, 0x72, 0x3b                           \
    }                                                                          \
  }

namespace efi {

typedef struct LoadedImage {
  typedef Status(EFIAPI *Unload)(Handle imageHandle);

  uint32_t revision;
  Handle parentHandle;
  SystemTable *systemTable;

  Handle deviceHandle;
  DevicePath::DevicePath *filePath;
  void *reserved;

  uint32_t loadOptionsSize;
  void *loadOptions;

  void *imageBase;
  size_t imageSize;
  Memory::Type imageCodeType;
  Memory::Type imageDataType;
  Unload unload;
} LoadedImage;

namespace ImageLoader {
typedef struct {
  size_t length;
  const char16_t *info;
  Status status;
} ExitInfo;

Handle load(DevicePath::DevicePath *imagePath);
ExitInfo start(Handle imageHandle);
Status unload(Handle imageHandle);

LoadedImage *getLoadedImageProtocol(Handle imageHandle);

} // namespace ImageLoader

} // namespace efi