#pragma once

#include <efi/efi.hpp>
#include <efi/memory.hpp>

#define EFI_DEVICE_PATH_PROTOCOL_GUID                                          \
  {                                                                            \
    0x09576e91, 0x6d3f, 0x11d2, {                                              \
      0x8e, 0x39, 0x00, 0xa0, 0xc9, 0x69, 0x72, 0x3b                           \
    }                                                                          \
  }

#define EFI_DEVICE_PATH_UTILITIES_PROTOCOL_GUID                                \
  {                                                                            \
    0x379be4e, 0xd706, 0x437d, {                                               \
      0xb0, 0x37, 0xed, 0xb8, 0x2f, 0xb7, 0x72, 0xa4                           \
    }                                                                          \
  }

#define EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL_GUID                                \
  {                                                                            \
    0x5c99a21, 0xc70f, 0x4ad2, {                                               \
      0x8a, 0x5f, 0x35, 0xdf, 0x33, 0x43, 0xf5, 0x1e                           \
    }                                                                          \
  }

#define EFI_DEVICE_PATH_TO_TEXT_PROTOCOL_GUID                                  \
  {                                                                            \
    0x8b843e20, 0x8132, 0x4852, {                                              \
      0x90, 0xcc, 0x55, 0x1a, 0x4e, 0x4a, 0x7f, 0x1c                           \
    }                                                                          \
  }

namespace efi {

typedef struct DevicePathUtil {
  typedef uint64_t(EFIAPI *GetDevicePathSize)(
      const DevicePath::DevicePath *devicePath
  );
  typedef DevicePath::DevicePath *(EFIAPI *DuplicateDevicePath)(
      const DevicePath::DevicePath *devicePath
  );
  typedef DevicePath::DevicePath *(EFIAPI *AppendDevicePath)(
      const DevicePath::DevicePath *parent,
      const DevicePath::DevicePath *child
  );
  typedef DevicePath::DevicePath *(EFIAPI *NextDevicePathInstance)(
      DevicePath::DevicePath **devicePathInstance,
      uint64_t *devicePathInstanceSize
  );
  typedef bool(EFIAPI *IsMultiInstance)(const DevicePath::DevicePath *devicePath
  );
  typedef DevicePath::DevicePath *(EFIAPI *CreateNode)(
      uint8_t nodeType,
      uint8_t nodeSubType,
      uint16_t nodeLength
  );

  GetDevicePathSize getDevicePathSize;
  DuplicateDevicePath duplicateDevicePath;
  AppendDevicePath appendDevicePath;
  AppendDevicePath appendDeviceNode;
  AppendDevicePath appendDevicePathInstance;
  NextDevicePathInstance nextInstance;
  IsMultiInstance isMultiInstance;
  CreateNode createNode;
} DevicePathUtil;

typedef struct DevicePathFromText {
  typedef DevicePath::DevicePath *(EFIAPI *FromText)(const char16_t *path);

  FromText toDeviceNode;
  FromText toDevicePath;
} DevicePathFromText;

typedef struct DevicePathToText {
  typedef char16_t *(EFIAPI *ToText)(
      const DevicePath::DevicePath *devicePath,
      bool displayOnly,
      bool allowShortcuts
  );

  ToText fromDeviceNode;
  ToText fromDevicePath;
} DevicePathToText;

namespace DevicePath {

DevicePath *fromString(const char16_t *path, bool isNode);

PoolObject<const char16_t> toString(
    DevicePath *devicePath,
    bool displayOnly,
    bool allowShortcuts,
    bool isNode
);

DevicePath *
append(const DevicePath *parent, const DevicePath *child, bool isChildNode);

DevicePath *getRootFsDevicePath();

} // namespace DevicePath

} // namespace efi