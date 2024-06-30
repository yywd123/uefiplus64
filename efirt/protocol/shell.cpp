#include <efi/protocol/shell.hpp>
#include <efi/string.hpp>

namespace efi::ShellUtils {

void walkdir(
    ShellProtocol *shell,
    SimpleFilesystem *filesystem,
    const char16_t *path,
    Function<void, const char16_t *, bool> handler,
    uint32_t depth
) {
  if (depth == 0)
    return;

  --depth;

  auto normalizedPath = FileSystem::normalizePath(path);
  path = normalizedPath.get();

  auto rootDirectory = File::open(filesystem, path, EFI_FILE_MODE_READ);
  if (rootDirectory.has_value()) {
    ShellProtocol::FileInfo *files;
    shell->findFilesInDirectory(rootDirectory.value(), &files);

    for (auto file : *files) {
      if (!wstrcmp(file.fileName, u".") || !wstrcmp(file.fileName, u"..")) {
        continue;
      }

      auto child = File::open(filesystem, file.fullName, EFI_FILE_MODE_READ);
      auto childInfo = child->getInfo();

      handler(file.fullName, !!(childInfo->attribute & EFI_FILE_DIRECTORY));

      if (childInfo->attribute & EFI_FILE_DIRECTORY) {
        walkdir(shell, filesystem, file.fullName, handler, depth);
      }
    }
  }
}

void listdir(
    ShellProtocol *shell,
    SimpleFilesystem *filesystem,
    const char16_t *path,
    Function<void, const char16_t *, bool> handler
) {
  walkdir(shell, filesystem, path, handler, 1);
}

} // namespace efi::ShellUtils
