PluginName = "Streamloots"

ROOT_DIR:=${CURDIR}
DEPS_DIR:=${ROOT_DIR}\deps

QtBaseDir := ${DEPS_DIR}\QT
QTDIR32 := $(QtBaseDir)\5.10.1\msvc2017
QTDIR64 := $(QtBaseDir)\5.10.1\msvc2017_64
CMAKE_PREFIX_PATH := $(QTDIR32)\lib\cmake\Qt5Widgets

OBSDepsBasePath := ${DEPS_DIR}\dependencies2019
DepsPath64 := $(OBSDepsBasePath)\win64
DepsPath32 := $(OBSDepsBasePath)\win32

OBSPath:=${DEPS_DIR}\obs-studio

CPPWSPath=${DEPS_DIR}\websocketpp
AsioPath=${DEPS_DIR}\asio

build_config := RelWithDebInfo

msbuild=C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\MSBuild\Current\Bin\MSBuild.exe

root:
	echo $(ROOT_DIR)

install-qt:
	SET "QtBaseDir=$(QtBaseDir)" && \
	ci\windows\install-qt-win.cmd

download-obs-deps:
	SET "DepsBasePath=$(OBSDepsBasePath)" && \
	ci\windows\download-obs-deps.cmd

prepare-obs-windows:
	SET "build_config=$(build_config)" && \
	SET "DepsPath32=$(DepsPath32)" && \
	SET "DepsPath64=$(DepsPath64)" && \
	SET "QTDIR32=$(QTDIR32)" && \
	SET "QTDIR64=$(QTDIR64)" && \
	SET "CMAKE_PREFIX_PATH=$(CMAKE_PREFIX_PATH)" && \
	SET "OBSPath=$(OBSPath)" && \
	ci\windows\prepare-obs-windows.cmd

build-obs-32:
	$(msbuild) /m /p:Configuration=$(build_config) $(OBSPath)\build32\obs-studio.sln

build-obs-64:
	$(msbuild) /m /p:Configuration=$(build_config) $(OBSPath)\build64\obs-studio.sln

prepare-cppws:
	SET "CPPWSPath=$(CPPWSPath)" && \
	SET "AsioPath=$(AsioPath)" && \
	ci\windows\prepare-cppws.cmd

prepare-dependencies:
	$(MAKE) install-qt
	$(MAKE) download-obs-deps
	$(MAKE) prepare-obs-windows
	$(MAKE) build-obs-32
	$(MAKE) build-obs-64
	$(MAKE) prepare-cppws

prepare-windows:
	SET "build_config=$(build_config)" && \
	SET "QTDIR32=$(QTDIR32)" && \
	SET "QTDIR64=$(QTDIR64)" && \
	SET "OBSPath=$(OBSPath)" && \
	SET "CPPWSPath=$(CPPWSPath)" && \
	SET "AsioPath=$(AsioPath)" && \
	ci\windows\prepare-windows.cmd

build-plugin-32:
	$(msbuild) /m /p:Configuration=$(build_config) .\build32\main.sln

build-plugin-64:
	$(msbuild) /m /p:Configuration=$(build_config) .\build64\main.sln

package-windows:
	ci\windows\package-windows.cmd

clean:
	if exist build32 rd /s /q build32
	if exist build64 rd /s /q build64
	if exist release rd /s /q release

build:
	$(MAKE) clean
	$(MAKE) prepare-windows
	$(MAKE) build-plugin-32
	$(MAKE) build-plugin-64
	$(MAKE) package-windows

build-package:
	$(MAKE) build
	$(MAKE) package-windows
	
