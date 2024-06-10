add_rules("mode.debug", "mode.release")

target("efi_application")
    set_kind("binary")

    add_cxxflags("-c -g -ffreestanding -nostdlib -mcmodel=large -m64 -fdata-sections -ffunction-sections -fno-exceptions -fno-rtti -Wall -Werror")
    set_optimize("smallest")

    add_files("efirt/**.cpp")
    add_includedirs("include")
    add_files("src/**.cpp")

    before_build("!linux|x86_64", function () 
        raise("invaild platform, please use linux or cross compiler instead")
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
        
        os.exec(objcopy.." -j .text -j .data -j .rela.dyn -j .reloc --target efi-app-x86_64 "..objectdir.."/"..name..".so "..rundir.."/"..name.."_unstrip.efi")
        os.exec(objcopy.." --strip-all "..rundir.."/"..name.."_unstrip.efi "..rundir.."/"..name.."_stripped.efi")

        -- make a copy
        os.trycp(rundir.."/"..name.."_stripped.efi", "./build/"..name..".efi")
    end)