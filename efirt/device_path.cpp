#include <efi/device_path.hpp>
#include <efi/image.hpp>
#include <efi/protocol.hpp>
#include <efi/rt.hpp>

namespace efi::DevicePathUtils {

PoolObject<DevicePath> fromString(const char16_t *path, bool isNode) {
  DevicePathFromText *protocol;

  Protocol::locateProtocol(
      EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL_GUID,
      (void **)&protocol
  );

  return isNode ? protocol->toDeviceNode(path) : protocol->toDevicePath(path);
}

PoolObject<const char16_t> toString(
    DevicePath *devicePath,
    bool displayOnly,
    bool allowShortcuts,
    bool isNode
) {
  DevicePathToText *protocol;

  Protocol::locateProtocol(
      EFI_DEVICE_PATH_TO_TEXT_PROTOCOL_GUID,
      (void **)&protocol
  );

  return isNode
             ? protocol->fromDeviceNode(devicePath, displayOnly, allowShortcuts)
             : protocol
                   ->fromDevicePath(devicePath, displayOnly, allowShortcuts);
}

PoolObject<DevicePath>
append(const DevicePath *parent, const DevicePath *child, bool isChildNode) {
  DevicePathUtil *protocol;

  Protocol::locateProtocol(
      EFI_DEVICE_PATH_UTILITIES_PROTOCOL_GUID,
      (void **)&protocol
  );

  return isChildNode ? protocol->appendDeviceNode(parent, child)
                     : protocol->appendDevicePath(parent, child);
}

} // namespace efi::DevicePathUtils