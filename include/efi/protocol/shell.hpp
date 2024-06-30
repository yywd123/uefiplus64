#pragma once

#include <efi/common.hpp>
#include <efi/filesystem.hpp>

#define EFI_SHELL_PROTOCOL_GUID                                                \
  {                                                                            \
    0x6302d008, 0x7f9b, 0x4f30, {                                              \
      0x87, 0xac, 0x60, 0xc9, 0xfe, 0xf5, 0xda, 0x4e                           \
    }                                                                          \
  }

namespace efi {

typedef struct ShellProtocol {
  typedef struct FileInfo : public ListNode<struct FileInfo> {
    Status fileOpenStatus;
    const char16_t *fullName;
    const char16_t *fileName;
    FileProtocol *handle;
    FileProtocol::FileInfo *info;
  } FileInfo;

  typedef Status(EFIAPI *Execute)(
      IN Handle *parentImageHandle,
      IN char16_t *command OPTIONAL,
      IN char16_t **environment OPTIONAL,
      OUT Status *exitCode OPTIONAL
  );

  typedef const char16_t *(EFIAPI *GetEnvironment)(IN const char16_t *name);

  typedef Status(EFIAPI *SetEnvironment)(
      IN const char16_t *name,
      IN const char16_t *value,
      IN bool isVolatile
  );

  typedef const char16_t *(EFIAPI *GetAlias)(
      IN const char16_t *alias,
      OUT bool *isVolatile OPTIONAL
  );

  typedef Status(EFIAPI *SetAlias)(
      IN const char16_t *command,
      IN const char16_t *alias,
      IN bool replace,
      IN bool isVolatile
  );

  typedef Status(EFIAPI *GetHelpText)(
      IN const char16_t *command,
      IN const char16_t *sections,
      OUT PoolObject<char16_t> &helpText
  );

  typedef const DevicePath *(EFIAPI *GetDevicePathFromMapping)(
      IN const char16_t *mapping
  );

  typedef PoolObject<const char16_t>(EFIAPI *GetMappingFromDevicePath)(
      IN OUT DevicePath **devicePath
  );

  typedef PoolObject<DevicePath>(EFIAPI *GetDevicePathFromFilePath)(
      IN const char16_t *path
  );

  typedef PoolObject<char16_t>(EFIAPI *GetFilePathFromDevicePath)(
      IN const DevicePath *devicePath
  );

  typedef Status(EFIAPI *SetMapping)(
      IN const DevicePath *devicePath,
      IN const char16_t *mapping
  );

  typedef const char16_t *(EFIAPI *GetCurrentDirectory)(
      IN const char16_t *fileSystemMapping OPTIONAL
  );

  typedef Status(EFIAPI *SetCurrentDirectory)(
      IN const char16_t *fileSystemMapping OPTIONAL,
      IN const char16_t *dir
  );

  typedef Status(EFIAPI *OpenFileList)(
      IN char16_t *path,
      IN uint64_t openMode,
      OUT FileInfo **fileList
  );

  typedef Status(EFIAPI *FreeFileList)(IN FileInfo **fileList);

  typedef Status(EFIAPI *FileListRemoveDuplicate)(IN FileInfo **fileList);

  typedef bool(EFIAPI *IsBatchActive)();

  typedef bool(EFIAPI *IsRootShell)();

  typedef void(EFIAPI *EnablePageBreak)();

  typedef void(EFIAPI *DisablePageBreak)();

  typedef bool(EFIAPI *GetPageBreak)();

  typedef Status (*GetDeviceName)(
      IN Handle deviceHandle,
      IN uint32_t flags,
      IN char *language,
      OUT char16_t **bestDeviceName
  );

  typedef PoolObject<FileProtocol::FileInfo>(EFIAPI *GetFileInfo)(
      IN FileProtocol *handle
  );

  typedef Status(EFIAPI *SetFileInfo)(
      IN FileProtocol *Handle,
      IN const FileProtocol::FileInfo *info
  );

  typedef Status(EFIAPI *OpenFileByName)(
      IN const char16_t *fileName,
      OUT FileProtocol *handle,
      IN uint64_t openMode
  );

  typedef Status(EFIAPI *CloseFile)(IN FileProtocol *handle);

  typedef Status(EFIAPI *CreateFile)(
      IN const char16_t *fileName,
      IN uint64_t attributes,
      OUT FileProtocol **handle
  );

  typedef Status(EFIAPI *ReadFile)(
      IN FileProtocol *handle,
      IN OUT size_t *size,
      OUT void *buffer
  );

  typedef Status(EFIAPI *WriteFile)(
      IN FileProtocol *handle,
      IN OUT size_t *size,
      OUT void *buffer
  );

  typedef Status(EFIAPI *DeleteFile)(IN FileProtocol handle);

  typedef Status(EFIAPI *DeleteFileByName)(IN const char16_t *fileName);

  typedef Status(EFIAPI *GetFilePosition)(
      IN FileProtocol *handle,
      OUT off64_t *position
  );

  typedef Status(EFIAPI *SetFilePosition)(
      IN FileProtocol *Handle,
      IN off64_t position
  );

  typedef Status(EFIAPI *FlushFile)(IN FileProtocol *handle);

  typedef Status(EFIAPI *FindFiles)(
      IN const char16_t *filePattern,
      OUT FileInfo **fileList
  );

  typedef Status(EFIAPI *FindFilesInDirectory)(
      IN FileProtocol *FileDirHandle,
      OUT FileInfo **FileList
  );

  typedef Status(EFIAPI
                     *GetFileSize)(IN FileProtocol *handle, OUT uint64_t *size);

  typedef Status(EFIAPI *OpenRoot)(
      IN DevicePath *devicePath,
      OUT FileProtocol **handle
  );

  typedef Status(EFIAPI *OpenRootByHandle)(
      IN Handle deviceHandle,
      OUT FileProtocol **handle
  );

  typedef Status(EFIAPI *RegisterGuidName)(
      IN const Guid *guid,
      IN const char16_t *name
  );
  typedef Status(EFIAPI *GetGuidName)(
      IN const Guid *guid,
      OUT const char16_t **name
  );
  typedef Status(EFIAPI
                     *GetGuidFromName)(IN const char16_t *name, OUT Guid *guid);
  typedef const char16_t *(EFIAPI *GetEnvironmentEx)(
      IN const char16_t *name,
      OUT uint32_t *attributes OPTIONAL
  );

  Execute execute;
  GetEnvironment getEnvironment;
  SetEnvironment setEnvironment;
  GetAlias getAlias;
  SetAlias setAlias;
  GetHelpText getHelpText;
  GetDevicePathFromMapping getDevicePathFromMap;
  GetMappingFromDevicePath getMapFromDevicePath;
  GetDevicePathFromFilePath getDevicePathFromFilePath;
  GetFilePathFromDevicePath getFilePathFromDevicePath;
  SetMapping setMapping;

  GetCurrentDirectory getCurrentDirectory;
  SetCurrentDirectory setCurrentDirectory;
  OpenFileList openFileList;
  FreeFileList freeFileList;
  FileListRemoveDuplicate fileListRemoveDuplicate;

  IsBatchActive isBatchActive;
  IsRootShell isRootShell;
  EnablePageBreak enablePageBreak;
  DisablePageBreak disablePageBreak;
  GetPageBreak getPageBreak;
  GetDeviceName getDeviceName;

  GetFileInfo getFileInfo;
  SetFileInfo setFileInfo;
  OpenFileByName openFileByName;
  CloseFile closeFile;
  CreateFile createFile;
  ReadFile readFile;
  WriteFile writeFile;
  DeleteFile deleteFile;
  DeleteFileByName deleteFileByName;
  GetFilePosition getFilePosition;
  SetFilePosition setFilePosition;
  FlushFile flushFile;
  FindFiles findFiles;
  FindFilesInDirectory findFilesInDirectory;
  GetFileSize getFileSize;

  OpenRoot openRoot;
  OpenRootByHandle openRootByHandle;

  Event::Instance executionBreak;

  uint32_t majorVersion;
  uint32_t minorVersion;

  // uefi shell 2.1+
  RegisterGuidName registerGuidName;
  GetGuidName getGuidName;
  GetGuidFromName getGuidFromName;
  GetEnvironmentEx getEnvironmentEx;
} ShellProtocol;

namespace ShellUtils {

void walkdir(
    ShellProtocol *shell,
    SimpleFilesystem *filesystem,
    const char16_t *path,
    Function<void, const char16_t * /*path*/, bool /*isDirectory*/> handler,
    uint32_t depth = ~0u
);

void listdir(
    ShellProtocol *shell,
    SimpleFilesystem *filesystem,
    const char16_t *path,
    Function<void, const char16_t * /*path*/, bool /*isDirectory*/> handler
);

} // namespace ShellUtils

} // namespace efi