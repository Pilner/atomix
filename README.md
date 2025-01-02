<h1 style="text-align: center">CMake Basic Template</h1>

<p style="text-align: center">To quickly setup a C/C++ Project using CMake</p>

## How to use

_Note: Make sure you have [CMake](https://cmake.org/download/) installed. To check, run `cmake --version` in your terminal_

1. Click `Use this template` or clone into a local directory

```bash
git clone https://github.com/Pilner/CMake-Template.git
```

2. Setup `CMakeLists.txt` to your liking

```C
# Minimum CMake version required
cmake_minimum_required(VERSION 3.10)

# Project name and language
project(PROJECT_NAME) // Change PROJECT_NAME

# Specify C standard
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Add include directories
include_directories(include)

# You can also include external libraries, e.g. SDL2

# Add source files
file(GLOB SOURCES "src/*.c")

# Add the executable
add_executable(PROJECT_NAME ${SOURCES}) // Change PROJECT_NAME

```

3. Once in the root directory of the repository, create a `build/` folder

```bash
mkdir build
cd build
```

4. Compile CMake using the `CMakeLists.txt`

```bash
# pwd is ../build
cmake ..
```

5. Build the CMake to Link the Libraries and Generate Executable

```bash
# pwd is ../build
cmake --build .
```

6. Execute the Generated Executable

```bash
# pwd is ../build
./PROJECT_NAME
```

7. In order to rebuild, delete `build/` and recreate steps **3 - 5**

```bash
rm -rf build
mkdir build
cd build
cmake ..
cmake --build .
```

---

## Rebuilding

To make rebuilding easier, this is a terminal config code that is put inside `.bashrc` or `.zshrc`

```bash
# CMake Build Functions
# Function to navigate to build directory and build the project
cmbuild() {
	if [ -d "build" ]; then
		cd build || { echo "Failed to enter build directory."; return 1; }
		if [ ! -d "CMakeFiles" ]; then
			cmake ..
		else
			echo "There are files in the build/ directory"
			cd ..
			return 1;
		fi
	fi

	cmake --build .
}

# Function to completely rebuild the project
cmrebuild() {
	# Check if we're already in the build directory
	if [[ "$(basename "$(pwd)")" == "build" ]]; then
		echo "You are already in the build directory. Proceeding with rebuild..."
		cd ..
		rm -rf build
		mkdir build
	else
		read "confirm?Are you sure you want to delete the build directory and rebuild? [y/N]: "
		if [[ "$confirm" =~ ^[Yy]$ ]]; then
			rm -rf build
			mkdir build || { echo "Failed to create build directory."; return 1; }
			echo "Build directory recreated."
		else
			echo "Rebuild canceled."
			return 0
		fi
	fi

  # Proceed to the build directory (if not already there)
  cd build || { echo "Failed to enter build directory."; return 1; }

  # Run cmake to configure the project
  cmake .. || { echo "CMake configuration failed."; return 1; }

  # Build the project
  cmake --build . || { echo "Build failed."; return 1; }

  echo "Rebuild complete."
}
```

This way, you can just type `cmbuild` or `cmrebuild` to quickly build out your project.
