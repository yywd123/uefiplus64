#include <efi/device_path.hpp>
#include <efi/filesystem.hpp>
#include <efi/image.hpp>
#include <efi/protocol.hpp>
#include <efi/rt.hpp>
#include <efi/string.hpp>

namespace efi {

File::File(FileProtocol *fp) { this->file = fp; }

Status File::read(void *buf, size_t &size, off64_t offset) {
  if (!this->file) {
    size = 0;

    return ERR_INVAILD_STATE;
  }

  auto stat = this->file->setPosition(this->file, offset);

  if (EFI_ERROR(stat)) {
    return stat;
  }

  return this->file->read(this->file, &size, buf);
}

PoolObject<uint8_t> File::readAll(size_t &size) {
  if (!this->file) {
    size = 0;

    return nullptr;
  }

  auto info = this->getInfo();

  if (!info) {
    return nullptr;
  }

  size = info->fileSize;
  auto buf = Memory::allocPool(Memory::Type::LoaderData, size);

  if (EFI_ERROR(this->read(buf, size))) {
    Memory::freePool(buf);

    return nullptr;
  }

  return buf;
}

Status File::write(const void *data, size_t &size) {
  if (!this->file) {
    return ERR_INVAILD_STATE;
  }

  return this->file->write(this->file, &size, (void *)data);
}

PoolObject<FileProtocol::FileInfo> File::getInfo() {
  if (!this->file) {
    return nullptr;
  }

  Guid infoGuid = EFI_FILE_INFO_GUID;
  auto fp = this->file;

  uint64_t bufferSize;
  fp->getInfo(fp, &infoGuid, &bufferSize, nullptr);

  auto info = (FileProtocol::FileInfo *)
      Memory::allocPool(Memory::Type::LoaderData, bufferSize);

  if (EFI_ERROR(fp->getInfo(fp, &infoGuid, &bufferSize, info))) {
    Memory::freePool(info);

    return nullptr;
  }

  return info;
}

Status File::flush() {
  if (!this->file) {
    return ERR_INVAILD_STATE;
  }

  return this->file->flush(this->file);
}

Status File::close() {
  if (!this->file) {
    return ERR_INVAILD_STATE;
  }

  auto stat = this->file->close(this->file);
  this->file = nullptr;

  return stat;
}

std::optional<File> File::open(
    SimpleFilesystem *rootfs,
    const char16_t *path,
    uint64_t openMode,
    uint64_t attributes
) {
  FileProtocol *volume;
  FileProtocol *file;

  if (!rootfs || !path || !openMode) {
    return std::nullopt;
  }

  if (EFI_ERROR(rootfs->openVolume(rootfs, &volume))) {
    return std::nullopt;
  }

  if (EFI_ERROR(volume->open(volume, &file, path, openMode, attributes))) {
    return std::nullopt;
  }

  return std::make_optional<File>(file);
}

SimpleFilesystem *FileSystem::getRootfs() {
  auto imageHandle = getImageHandle();
  auto loadedImage = Image::getLoadedImageProtocol(imageHandle);

  DevicePath *devicePath;
  Handle handle;
  SimpleFilesystem *filesystem;

  Protocol::openProtocol(
      EFI_DEVICE_PATH_PROTOCOL_GUID,
      (void **)&devicePath,
      loadedImage->deviceHandle,
      imageHandle,
      nullptr,
      Protocol::OpenAttribute::GetProtocol
  );

  Protocol::locateDevicePath(
      EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_GUID,
      &devicePath,
      &handle
  );

  Protocol::openProtocol(
      EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_GUID,
      (void **)&filesystem,
      handle,
      efi::getImageHandle(),
      nullptr,
      Protocol::GetProtocol
  );

  return filesystem;
}

PoolObject<SimpleFilesystem *> FileSystem::getFilesystemList(uint64_t &count) {
  SimpleFilesystem **fsList;
  Handle *handleList;

  Protocol::locateHandleBuffer(
      EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_GUID,
      Protocol::SearchType::ByProtocol,
      nullptr,
      &count,
      &handleList
  );

  fsList = (SimpleFilesystem **)
      Memory::allocPool(Memory::Type::LoaderData, count * sizeof(*fsList));

  for (uint64_t i = 0; i < count; ++i) {
    Protocol::handleProtocol(
        EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_GUID,
        (void **)&fsList[i],
        handleList[i]
    );
  }

  return fsList;
}

PoolObject<const char16_t> FileSystem::normalizePath(const char16_t *path) {
  char16_t *p = wstrdup(path).unwrap();
  bool quoted = false;

  for (uint64_t i = 0; p[i]; ++i) {
    if (p[i] == '\"') {
      quoted = !quoted;
    } else if (p[i] == '/' && !quoted) {
      p[i] = '\\';
    }
  }

  return p;
}

} // namespace efi