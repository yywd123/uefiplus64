#include <efi/filesystem.hpp>
#include <efi/protocol.hpp>
#include <efi/protocol/graphics.hpp>
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

Status graphicsTest() {
  print(u"example: testing graphics optput protocol\r\n");

  GraphicsOutput *gop;
  Protocol::locateProtocol(EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID, (void **)&gop);

  if (!gop) {
    print(u"could not locate graphics output protocol!\r\n");
    return EFI_UNSUPPORTED;
  }

  auto mode = gop->mode->info;

  {
    GraphicsOutput::BltPixel pixel{0xff, 0xff, 0xff, 0};
    gop->blt(
        gop,
        &pixel,
        GraphicsOutput::BltOperation::FillVideo,
        0,
        0,
        0,
        0,
        mode->horizontalResolution,
        mode->verticalResolution,
        0
    );

    print(u"1.fill the whole screen with pure white\r\n");
  }

  getSystemTable()->bootServices->stall(2000000);

  {
    GraphicsOutput::BltPixel pixel{.red = 0xff};
    gop->blt(
        gop,
        &pixel,
        GraphicsOutput::BltOperation::FillVideo,
        0,
        0,
        0,
        0,
        100,
        100,
        0
    );

    pixel = GraphicsOutput::BltPixel{.green = 0xff};
    gop->blt(
        gop,
        &pixel,
        GraphicsOutput::BltOperation::FillVideo,
        0,
        0,
        100,
        0,
        100,
        100,
        0
    );

    pixel = GraphicsOutput::BltPixel{.blue = 0xff};
    gop->blt(
        gop,
        &pixel,
        GraphicsOutput::BltOperation::FillVideo,
        0,
        0,
        200,
        0,
        100,
        100,
        0
    );

    print(u"2.red green blue blocks\r\n");
  }

  getSystemTable()->bootServices->stall(2000000);

  {
    gop->blt(
        gop,
        nullptr,
        GraphicsOutput::BltOperation::VideoToVideo,
        0,
        0,
        0,
        100,
        300,
        100,
        0
    );

    print(u"3.copy an area to another area in framebuffer\r\n");
  }

  getSystemTable()->bootServices->stall(2000000);

  return EFI_SUCCESS;
}

Function<Status> examples[]{
    lsdir,
    graphicsTest,
};

extern "C" EFIAPI Status main() {
  print(u"this is uefi++64! here are some examples\r\n");

  for (auto example : examples) {
    printf(u"example return code: %llx\r\n", example());
    getSystemTable()->bootServices->stall(1000000);
  }

  print(u"finish!\r\n");

  return EFI_SUCCESS;
}