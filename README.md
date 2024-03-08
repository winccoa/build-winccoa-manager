# WinCC OA C++ API Manager Builder

This GitHub repository provides an out-of-the-box GitHub Action and [Azure Pipeline](.docs/AZURE.md) for building C++ API managers for WinCC OA.
It is designed to lower the barrier to entry for developers, allowing them to easily build, unit test, and package WinCC OA API managers for multiple OS and WinCC OA version combinations using a single C++ source code.

It is based on the original work from here: https://github.com/andygruber/cpp-multi-builder

## Features

- **Ease of use**: Set up with minimal configuration required.
- **Multiple OS and WinCC OA Version Support**: Build your API managers for different combinations of operating systems and WinCC OA versions.
- **C++ Package Manager Support**: Conan package manager is supported out of the box for managing C++ dependencies.
- **Automated testing and packaging**: Includes support for unit testing and packaging your API managers.
- **Debug files available**: PDB and unstripped files are kept alongside build artifacts.
- **Caching support**: Conan packages and extracted Windows API files are automatically cached in GitHub actions.
- **Multiple CI Platforms**: Use GitHub Actions or Azure Pipelines. Also works on-premises or with self-hosted runners/agents.

## Getting Started

### Prerequisites

- A GitHub account
- Basic C++ and CMake skills
- Familiarity with GitHub actions
- Access to WinCC OA API docker images (Linux) and WinCC OA MSI packages (Windows)

### Fork the repository

To get started, fork this repository into your own GitHub account. This will be the home for your C++ CMake project for building WinCC OA API managers.

### Initial general configuration

The default configuration is stored in `pipeline/createMatrix/mergekeys.yml`.

This file stores, among other things, the name of the Docker images and the locations for the WinCC OA MSI packages.
Since these prerequisites are not publicly available, they must be manually created and defined here.

#### Linux

Linux builds are based on Docker images.
The API images generated from the public repo [https://github.com/andygruber/build-winccoa-docker-image](https://github.com/andygruber/build-winccoa-docker-image) are compatible.
For example:
```
  container_image: 'agruberetm/winccoa:v3.19.10-api'
```

Also provide the following credentials in the GitHub secrets:
- DOCKERHUB_USER
- DOCKERHUB_PASSWORD

#### Windows

Windows is much more complicated.
This is just a sample implementation, replace it with something more suitable for your environment.

- On a machine with WinCC OA >= 3.19 installed, go to `C:\ProgramData\Package Cache` and search for `Base.msi` and `APIcpp.msi`.
- Make these files available on a secure server where the path is a combination of `msi_download_server` and `msi_download_info`, see below.
- In addition take `C:\Windows\System32\WibuCm64.dll`, zip it to `NODEPLOY_CODEMETER.zip` and provide it as OneDrive link as well.
- For example:
    ```
    msi_download_server: "https://www.for.example/artifactory"
    msi_download_info: "winccoa/3.19.10"
    ```

Also provide the following credentials in the GitHub secrets:
- WINCCOA_USER
- WINCCOA_PASSWORD

### Adding your C++ CMake project

Place your C++ source code anywhere in the repository, along with a `CMakeLists.txt` file.
This is where you'll define your project and its dependencies.

### Configuration

Create a `build-config.yml` file in your repository along with the `CMakeLists.txt` file.
This file specifies the build configurations for different operating systems and WinCC OA versions.
Here's an example based on the demo-driver provided in the `demoDrv` directory:

```yaml
demoDriver:
  configuration:
    win_3_19_relwithdebinfo:
      <<: *_win_3_19_relwithdebinfo
    win_3_20_relwithdebinfo:
      <<: *_win_3_20_relwithdebinfo
    debian_3_20_relwithdebinfo:
      <<: *_debian_3_20_relwithdebinfo
    debian_3_19_relwithdebinfo:
      <<: *_debian_3_19_relwithdebinfo
```

For C++ package management, create a `conanfile.txt` or `conanfile.py` file in addition to your `CMakeLists.txt` file.

### Using packaging and testing

To use unit testing and/or packaging, include the necessary CMake files for packaging and testing as follows:
```cmake
project(demoDrv
  VERSION 0.1.0
)
# make sure to place the include commands after the project
# command specifying the project name and version
include(../cmake/packaging.cmake)
include(../cmake/testing.cmake)
```

These includes will enable the GitHub actions pipeline to perform automated testing and packaging of your project.

Testing also requires the [googletest](https://github.com/google/googletest) framework, just merge the following line to your `conanfile.py`:
```python
    def requirements(self):
        self.requires("gtest/1.14.0")
```

A complete example of a `conanfile.py` can be found [here](.docs/BUILD.md#conan).

### Packaging details

#### Key Features

- Automatically selects the packaging format based on the target OS.
  - **Windows**: Packages are generated as ZIP files.
  - **Debian-based Linux**: Packages are generated as DEB files.
  - **Red Hat-based Linux**: Packages are generated as RPM files.
- Configures the `CPACK_PACKAGING_INSTALL_PREFIX` to ensure correct installation paths, with special handling for WinCC OA environments on Linux.

#### Customization

Besides the mentioned [Key Features](#key-features) CPack standard settings are used.

It is recommended to set `CPACK_PACKAGE_CONTACT`, otherwise it is automatically set to `undefined`.
For example:
```cmake
set(CPACK_PACKAGE_CONTACT "Your name or company")
```

For further customization, such as including additional files in the package or changing package metadata, see the [CPack documentation](https://cmake.org/cmake/help/latest/module/CPack.html).

### To add a new test

1. **Define test sources**:
List all the source files associated with your test.
For a large test suite, you may want to separate your test sources from your main application sources.

2. **Use the `add_gtest_with_xml` Macro**:
This macro is used to compile the test sources into an executable, link it with Google Test and any necessary project libraries, and set up XML output for the test results.
The basic syntax is:

   ```cmake
   add_gtest_with_xml(TARGET_NAME TARGET_LIBRARY TEST_SOURCES)
   ```

   - `TARGET_NAME`: A unique name for your test executable.
   - `TARGET_LIBRARY`: The library your test executable should be linked against. This is usually your project's main library.
   - `TEST_SOURCES`: The source files for your test.

3. **Example**:
For a hypothetical binary named `demoDrv` that tests the functionality in `demoDrvLib`, you might write:

   ```cmake
   set(TEST_SOURCES demoDrvTest.cxx)
   add_gtest_with_xml(demoDrv demoDrvLib ${TEST_SOURCES})
   ```

4. **Integration with CMakeLists.txt**:
Add your test configuration to a `CMakeLists.txt` in your project's test directory.
If your project structure does not already include a test directory, create one as shown:

   ```cmake
   add_subdirectory(tests)
   ```

### Build Pipeline

The `build.yml` GitHub action workflow file orchestrates the build process.
It prepares the build environment, installs the necessary dependencies, and executes the build according to the configurations specified in `build-config.yml`.

Its use in Azure DevOps is described [here](.docs/AZURE.md).

This process is triggered by push or pull request events to the main branch, or can be triggered manually.

When the build is run, certain directories are automatically set:
- **build directory**: is set set to `build/make`
- **install dir**: is set to `build/install` via the `CMAKE_INSTALL_PREFIX` cache variable
- **packaging dir**: is set to `build/deploy` via the `CPACK_OUTPUT_FILE_PREFIX` cache variable

**Note:** The automation looks in these paths for the build artifacts, such as test results or generated binaries.
If you make changes, make sure these directories are still set correctly by the automation.

## Local Build Environment Setup

For detailed instructions on setting up your local build environment, including configuring Conan and CMake for different build types, see the [Build Environment Setup Guide](.docs/BUILD.md).
This guide provides step-by-step instructions to help you get started quickly and efficiently.

## Support

If you have any questions or need support, please consider opening an issue in the repository. Contributions to improve the build process or add new features are welcome.
