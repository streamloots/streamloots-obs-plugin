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

## VSCode setup
To be able to work with vscode you'll need to follow this tutorial:
https://code.visualstudio.com/docs/cpp/cmake-linux

For the vscode configuration you can use this settings:
```
    "cmake.configureArgs":[
        "-A x64",
    ],
    "cmake.generator":"Visual Studio 16 2019",	
    "cmake.configureSettings": {
        "CMAKE_SYSTEM_VERSION": "10.0",
        "QTDIR": ".\\deps\\QT\\5.10.1\\msvc2017",
        "LibObs_DIR": ".\\deps\\obs-studio\\build64\\libobs",
        "LIBOBS_INCLUDE_DIR": ".\\deps\\obs-studio\\libobs",
        "LIBOBS_LIB": ".\\deps\\obs-studio\\build64\\libobs\\RelWithDebInfo\\obs.lib",
        "OBS_FRONTEND_LIB": ".\\deps\\obs-studio\\build64\\UI\\obs-frontend-api\\RelWithDebInfo\\obs-frontend-api.lib",
        "CPPWS_DIR": ".\\deps\\websocketpp",
        "ASIO_DIR": ".\\deps\\asio"
    }

```

## How to test
1. Run `make build`
2. Copy the release folder to your obs instalation ( C:\Program Files\obs-studio )
3. Run obs
4. Check the logs Help->Log Files -> View current log
5. To test the server you need to make a request to the port, similar to:
```
{
    "request-type":"display-image",
    "message-id":"wey",
    "metadata":{
        "url":"https://giphy.com/embed/Rin3bJMT1guHPZes5u/video",
        "seconds":5
    }
}

```
