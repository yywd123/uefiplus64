#pragma once

#include <efi/efi.hpp>
#include <efi/memory.hpp>

#include <optional>

#define EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_GUID                                   \
  {                                                                            \
    0x0964e5b22, 0x6459, 0x11d2, {                                             \
      0x8e, 0x39, 0x00, 0xa0, 0xc9, 0x69, 0x72, 0x3b                           \
    }                                                                          \
  }

#define EFI_FILE_INFO_GUID                                                     \
  {                                                                            \
    0x09576e92, 0x6d3f, 0x11d2, {                                              \
      0x8e, 0x39, 0x00, 0xa0, 0xc9, 0x69, 0x72, 0x3b                           \
    }                                                                          \
  }

#define EFI_FILE_MODE_READ 0x0000000000000001
#define EFI_FILE_MODE_WRITE 0x0000000000000002
#define EFI_FILE_MODE_CREATE 0x8000000000000000

#define EFI_FILE_READ_ONLY 0x0000000000000001
#define EFI_FILE_HIDDEN 0x0000000000000002
#define EFI_FILE_SYSTEM 0x0000000000000004
#define EFI_FILE_RESERVED 0x0000000000000008
#define EFI_FILE_DIRECTORY 0x0000000000000010
#define EFI_FILE_ARCHIVE 0x0000000000000020
#define EFI_FILE_VALID_ATTR 0x0000000000000037

namespace efi {

typedef struct FileProtocol {
  typedef struct {
    Event::Instance event;
    Status status;
    uint64_t bufferSize;
    void *buffer;
  } IoToken;

  typedef struct {
    uint64_t size;
    uint64_t fileSize;
    uint64_t physicalSize;
    Time::Time createTime;
    Time::Time lastAccessTime;
    Time::Time modificationTime;
    uint64_t attribute;
    char16_t fileName[];
  } FileInfo;

  typedef Status(EFIAPI *Open)(
      struct FileProtocol *instance,
      struct FileProtocol **newHandle,
      const char16_t *fileName,
      uint64_t openMode,
      uint64_t attributes
  );

  typedef Status(EFIAPI *Close)(struct FileProtocol *instance);

  typedef Status(EFIAPI *Remove)(struct FileProtocol *instance);

  typedef Status(EFIAPI *Read)(
      struct FileProtocol *instance,
      uint64_t *bufferSize,
      void *buffer
  );

  typedef Status(EFIAPI *Write)(
      struct FileProtocol *instance,
      uint64_t *bufferSize,
      void *buffer
  );

  typedef Status(EFIAPI *SetPosition)(
      struct FileProtocol *instance,
      uint64_t position
  );

  typedef Status(EFIAPI *GetPosition)(
      struct FileProtocol *instance,
      uint64_t *position
  );

  typedef Status(EFIAPI *GetInfo)(
      struct FileProtocol *instance,
      Guid *informationType,
      uint64_t *bufferSize,
      void *buffer
  );

  typedef Status(EFIAPI *SetInfo)(
      struct FileProtocol *instance,
      Guid *informationType,
      uint64_t bufferSize,
      void *buffer
  );

  typedef Status(EFIAPI *Flush)(struct FileProtocol *instance);

  typedef Status(EFIAPI *OpenEx)(
      struct FileProtocol *instance,
      struct FileProtocol **newHandle,
      const char16_t *fileName,
      uint64_t openMode,
      uint64_t attributes,
      IoToken *token
  );

  typedef Status(EFIAPI
                     *FileOpEx)(struct FileProtocol *instance, IoToken *token);

  uint64_t revision;
  Open open;
  Close close;
  Remove remove;
  Read read;
  Write write;
  GetPosition getPosition;
  SetPosition setPosition;
  GetInfo getInfo;
  SetInfo setInfo;
  Flush flush;
  OpenEx openEx;    // Added for revision 2
  FileOpEx readEx;  // Added for revision 2
  FileOpEx writeEx; // Added for revision 2
  FileOpEx flushEx; // Added for revision 2
} FileProtocol;

typedef struct SimpleFilesystem {
  typedef Status(EFIAPI *OpenVolume)(
      SimpleFilesystem *instance,
      FileProtocol **root
  );

  uint64_t revision;
  OpenVolume openVolume;
} SimpleFilesystem;

class File {
  FileProtocol *file;

  File(FileProtocol *fp);

public:
  Status read(void *buf, size_t &size, off64_t offset = 0);
  PoolObject<uint8_t> readAll(size_t &size);

  Status write(const void *data, size_t &size);

  PoolObject<FileProtocol::FileInfo> getInfo();

  Status flush();
  Status close();

  operator FileProtocol *() { return this->file; }

  static std::optional<File> open(
      SimpleFilesystem *rootfs,
      const char16_t *path,
      uint64_t openMode,
      uint64_t attributes = 0
  );
};

namespace FileSystem {

SimpleFilesystem *getRootfs();

PoolObject<SimpleFilesystem *> getFilesystemList(uint64_t &count);

PoolObject<const char16_t> normalizePath(const char16_t *path);

} // namespace FileSystem

} // namespace efi