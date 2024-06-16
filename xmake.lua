add_rules("mode.debug", "mode.release")

local ovmf_path = "" -- replace with your ovmf path(for `xmake run`)

-- choose the executable's subsystem
-- "efi-app": efi application
-- "efi-bsd": efi boot service driver
-- "efi-rtd": efi runtime driver
-- "sal-rtd": sal runtime driver(see https://www.intel.com/content/dam/www/public/us/en/documents/specification-updates/itanium-system-abstraction-layer-specification.pdf)
local subsystem = ""

target("efi_application")
    set_kind("binary")

    add_cxxflags("-c -g -ffreestanding -nostdlib -mcmodel=large -m64 -fdata-sections -ffunction-sections -fno-exceptions -fno-rtti -Wall -Werror")
    set_optimize("smallest")

    add_includedirs("include")

    add_files("efirt/**.cpp")
    add_files("src/**.cpp")

    before_build("!linux|x86_64", function () 
        raise("invaild platform, please use linux or cross compiler instead")
    end)

    before_build(function () 
        if(subsystem == "") then
            raise("please replace subsystem with the target subsystem in xmake.lua")
        end
    end)

    on_link(function (target)
        objectdir = target:objectdir()
        rundir = target:rundir()
        name = target:name()
        compiler = target:tool("cxx")
        objcopy, _ = path.filename(compiler):gsub("gcc", "objcopy")
        objcopy = path.join(path.directory(compiler), objcopy)
    
        objlist = ""
        for key,val in pairs(target:objectfiles()) do 
            objlist = objlist..val.." "
        end
        
        -- link
        os.exec(compiler.." "..objlist.."-flto -nostdlib -nostartfiles -Tlinker.ld -shared -Wl,-Bsymbolic,-gc-sections -o "..objectdir.."/"..name..".so")
        
        -- generate efi image
        os.mkdir(rundir)
        
        os.exec(objcopy.." -j .text -j .data -j .rela.dyn -j .reloc --target efi-app-x86_64 --subsystem "..subsystem.." "..objectdir.."/"..name..".so "..rundir.."/"..name.."_unstrip.efi")
        os.exec(objcopy.." -R .reloc --strip-all "..rundir.."/"..name.."_unstrip.efi "..rundir.."/"..name.."_stripped.efi")
    end)

    on_run(function (target) 
        if(ovmf_path == "") then
            raise("please replace ovmf_path with your ovmf path in xmake.lua")
        end

        -- copy to build/esp
        rundir = target:rundir()
        name = target:name()
        espdir = rundir.."/../../../esp/"

        os.mkdir(espdir.."efi/boot/")
        os.trycp(rundir.."/"..name.."_stripped.efi", espdir.."efi/boot/bootx64.efi")

        os.exec("qemu-system-x86_64 -net none -m 1g -hda fat:rw:build/esp -pflash "..ovmf_path)
    end)