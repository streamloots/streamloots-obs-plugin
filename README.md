# Streamloots - OBS Plugin

## Source folder structure
```
server # files related to server connection and request handler
use-case # process server request and run the use case
utils #obs and other utils like timers
plugin-main.cpp #file that runs obs, setup the server

```

## OBS notes

### Important types
- obs_scene_t: Represents an scene in obs
- obs_source_t: Represents a source ( attached or not to obs ), cannot apply transform
- obs_sceneitem_t: Represents a source attached to an scene, can apply transform operations
- obs_data_t: Similar to a json, can be ussed for source properties, or pass data.

More information:  https://obsproject.com/docs/reference-core-objects.html

### Reference repos
- https://github.com/Palakis/obs-websocket
- https://github.com/obsproject/obs-studio

### How to know the real property names on a source to set?
OBS Api documentation it's unclear about this point. It  only contains documentation about the methods to call to configure props. These methods recieves a `propId`.
However, this params is defined as a plain string and there is not documentation about what are the posible values.

So to workaround is to get that props directly from the OBS.
1. Configure a source manually on obs with the configuration you wanted
2. Name the source with an unique identifier. Like `sample`
3. Use this code on any of the use-cases of the plugin:
```
obs_source_t *sampleSource = obs_get_source_by_name("sample");
obs_data_t * sampleProperties=obs_source_get_settings(sampleSource);
const char* json=obs_data_get_json(sampleProperties);
blog(LOG_INFO, "sourceProperties :%s", json);
```
4. Execute the use case by sending a request from Postman
5. Check the log for the JSON serializacion of the source settings

## Todo's
- Save current state of scene in case something goes wrong, or to restore after timeout
- Process request each for thread

## Introduction

This plugin includes:

- The CMake project file
- Boilerplate plugin source code
- GitHub Actions workflows and repository actions
- Build scripts for Windows, macOS, and Linux

## GitHub Actions & CI

The scripts contained in `github/scripts` can be used to build and package the plugin and take care of setting up obs-studio as well as its own dependencies. A default workflow for GitHub Actions is also provided and will use these scripts.

### Retrieving build artifacts

Each build produces installers and packages that you can use for testing and releases. These artifacts can be found on the action result page via the "Actions" tab in your GitHub repository.

#### Building a Release

Simply create and push a tag and GitHub Actions will run the pipeline in Release Mode. This mode uses the tag as its version number instead of the git ref in normal mode.

### Signing and Notarizing on macOS

On macOS, Release Mode builds can be signed and sent to Apple for notarization if the necessary codesigning credentials are added as secrets to your repository. **You'll need a paid Apple Developer Account for this.**

- On your Apple Developer dashboard, go to "Certificates, IDs & Profiles" and create two signing certificates:
    - One of the "Developer ID Application" type. It will be used to sign the plugin's binaries
    - One of the "Developer ID Installer" type. It will be used to sign the plugin's installer
- Using the Keychain app on macOS, export these two certificates and keys into a .p12 file **protected with a strong password**
- Encode the .p12 file into its base64 representation by running `base64 YOUR_P12_FILE`
- Add the following secrets in your Github repository settings:
    - `MACOS_SIGNING_APPLICATION_IDENTITY`: Name of the "Developer ID Application" signing certificate generated earlier
    - `MACOS_SIGNING_INSTALLER_IDENTITY`: Name of "Developer ID Installer" signing certificate generated earlier
    - `MACOS_SIGNING_CERT`: Base64-encoded string generated above
    - `MACOS_SIGNING_CERT_PASSWORD`: Password used to generate the .p12 certificate
    - `MACOS_NOTARIZATION_USERNAME`: Your Apple Developer account's username
    - `MACOS_NOTARIZATION_PASSWORD`: Your Apple Developer account's password (use a generated "app password" for this)
