#include <efi/filesystem.hpp>
#include <efi/protocol.hpp>
#include <efi/protocol/shell.hpp>
#include <efi/rt.hpp>

using namespace efi;

class StringNode : public ListNode<StringNode> {
public:
  const char16_t *data;
};

Status lsdir() {
  print(u"example: list all files in root directory\r\n");

  ShellProtocol *shell;
  Protocol::locateProtocol(EFI_SHELL_PROTOCOL_GUID, (void **)&shell);

  if (!shell) {
    print(u"could not locate shell protocol! please run the application in "
          u"uefi shell\r\n");
    return EFI_UNSUPPORTED;
  }

  static StringNode list;
  list.init();

  auto rootfs = FileSystem::getRootfs();
  ShellUtils::walkdir( //  或者直接用ShellUtils::listdir
      shell,
      rootfs,
      u"./",
      [](const char16_t *path, bool isDirectory) {
        if (!isDirectory) { //  文件直接显示
          printf(u"file: %s\r\n", path);
          return;
        }

        //  链表测试 将目录插入链表中
        auto node = (StringNode *)
            Memory::allocPool(Memory::Type::LoaderData, sizeof(StringNode));
        node->data = path;
        list.push_back(node);
      },
      1
  );

  for (auto node : list) {
    printf(u"dir: %s\r\n", node.data);
  }

  return EFI_SUCCESS;
}

Function<Status> examples[]{
    lsdir,
};

extern "C" EFIAPI Status main() {
  printf(u"this is uefi++64! here are some examples\r\n");

  for (auto example : examples) {
    printf(u"example return code: %x\r\n", example());
    getSystemTable()->bootServices->stall(1000000);
  }

  printf(u"finish!\r\n");

  return EFI_SUCCESS;
}