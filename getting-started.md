## Prepare requirements
- Install 7z
- Visual studio 2019 with c++ support
- Install cmake
- Install https://jrsoftware.org/ add it to path ( only required to package the plugin)

More requirementes needed you can find it in the obs documentation https://obsproject.com/wiki/install-instructions#windows-build-directions

## Prepare dependencies

To prepare dependencies run `make prepare-dependencies`


## Build project

To Build the proejct run `make build` if you want the installer too use `make build-package`
you need to pass a variable msbuild passing the location of the msbuild.exe, you can find an example in the makefile to know where can be located
If you are not using the installer you need to copy the release folder to your obs folder so the plugin is installed