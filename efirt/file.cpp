#include <efi/device_path.hpp>
#include <efi/file.hpp>
#include <efi/protocol.hpp>
#include <efi/rt.hpp>

namespace efi::File {

File *open(const char16_t *path, uint64_t openMode, uint64_t attributes) {
  Handle fsHandle;
  SimpleFilesystem *rootfs;
  File *volume;
  File *file;

  auto rootfsDevicePath = DevicePath::getRootFsDevicePath();

  Protocol::locateDevicePath(
      EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_GUID,
      &rootfsDevicePath,
      &fsHandle
  );

  Protocol::openProtocol(
      EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_GUID,
      (void **)&rootfs,
      fsHandle,
      efi::getImageHandle(),
      nullptr,
      Protocol::GetProtocol
  );

  rootfs->openVolume(rootfs, &volume);

  volume->_open(volume, &file, path, openMode, attributes);

  return file;
}

PoolObject<FileInfo> File::getInfo() {
  Guid infoGuid = EFI_FILE_INFO_GUID;
  auto bs = getSystemTable()->bootServices;

  uint64_t bufferSize;
  FileInfo *info;

  this->_getInfo(this, &infoGuid, &bufferSize, nullptr);

  bs->allocatePool(Memory::Type::LoaderData, bufferSize, (void **)&info);

  this->_getInfo(this, &infoGuid, &bufferSize, info);

  return info;
}

} // namespace efi::File