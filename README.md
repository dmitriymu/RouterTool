# Router Configuration / MAC Generator App

![My screenshot](images/screenshot.png "Optional Title")


A cross-platform C++ application (using wxWidgets and libssh) that allows you to:

1. Connect via SSH to a remote device (e.g., a router).
2. Generate random MAC addresses based on a vendor prefix (loaded from CSV).
3. Maintain notes in a simple text editor.

## Features

- **SSH Connection**: Connect, authenticate, and issue commands on remote devices.
- **MAC Address Generation**: Pick a vendor prefix, generate the last 3 octets randomly.
- **Notes Window**: Create or load a local text file for storing simple text notes.
- Built with [wxWidgets](https://www.wxwidgets.org/) for the GUI, [libssh](https://www.libssh.org/) for SSH.

---

## Requirements

1. **C++17** or later compiler
2. **wxWidgets** (must be installed and findable by CMake)
3. **libssh** (installed and findable by CMake)
4. **CMake** (version 3.10 or higher)

---

## Building & Running

### macOS

1. **Install Dependencies**
   Using [Homebrew](https://brew.sh/):
   ```bash
   brew install wxwidgets libssh
   ```


(You may need to install **pkg-config** as well if it’s not already installed.)

**2.**	**Clone the Repository**

```
git clone https://github.com/YourUsername/YourRepo.git
cd YourRepo
```

**3. Build**

```
mkdir build && cd build
cmake ..
make
```

**4. Run**

```
./RoCom
```


**Linux**

**1.**	**Install Dependencies**

On Debian/Ubuntu:

```
sudo apt-get update
sudo apt-get install build-essential cmake pkg-config libwxgtk3.0-gtk3-dev libssh-dev
```

**2.**	**Clone the Repository**

```
git clone https://github.com/YourUsername/YourRepo.git
cd YourRepo
```

**3.**	**Build**

```
mkdir build && cd build
cmake ..
make
```

**4. Run**

```
./RoCom
```


**Windows**

**1.**	**Install Dependencies**

 • You can either build [wxWidgets](https://www.wxwidgets.org/) from source or install it via a package manager such as [vcpkg](https://github.com/microsoft/vcpkg).

 • Similarly, build or install [libssh](https://www.libssh.org/).

 • Make sure **cmake** is on your system path (e.g., part of Visual Studio or installed from https://cmake.org/).

**2.**	**Clone the Repository**

```
git clone https://github.com/YourUsername/YourRepo.git
cd YourRepo
```

**3.**	**Generate Project Files**

From a Visual Studio Developer command prompt or PowerShell:

```
mkdir build
cd build
cmake .. -G "Visual Studio 17 2022" -A x64
```

(Adjust the generator and architecture to match your setup.)

**4. Build**

  • Open the generated **.sln** file in Visual Studio and build, **or** from command line:

```
msbuild RoCom.sln /p:Configuration=Release
```

  • The resulting **.exe** will be in something like **build/Release/RoCom.exe**.

**5. Run**

Double-click **RoCom.exe** in the output folder, or run from the command line:

```
.\Release\RoCom.exe
```

---



**Usage**

After building:

**1.**	**Launch** **RoCom**.

**2.**	**Enter** IP, username, and password for your router or target device.

**3.**	**Click** **Connect** to establish SSH connection.

**4.**	**MAC Generator** opens a new window for searching vendors and generating MAC addresses.

**5.**	**Notes** opens a text window for reading/editing local notes (saved to **notes.txt**).

---



## License

This project is licensed under the [MIT License](LICENSE).
