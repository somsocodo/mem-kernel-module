# mem-kernel-module

A linux kernel module for reading usermode process memory using IOCTL.

## Warning & Disclaimer

This program reads process memory for educational and debugging purposes only. Do not use this program for malicious intent, illegal activities, or to gain an unfair advantage in any system, software, or game.

By using this software, you acknowledge the following:

- Misuse of this module, including its use to bypass security mechanisms or violate terms of service (such as in online games), may result in penalties, including account suspension or permanent bans.
- I, the developer, am not responsible for any actions taken using this software, nor for any resulting penalties, damages, or legal consequences. The responsibility of using this software lies entirely with the user.
Use responsibly and at your own risk.

## Usage

See c++ & rust client example for Counter-Strike 2 in ``./examples``
- Note compiled examples must be run as sudo to access the device

#### Build/load module + clean up build artifacts
- ``make && make load && make clean``
- unload ``make unload``

#### Build/run client
- note kernel module must be loaded
- ``cd client-example``
- ``make && sudo ./build/client-example``

## VS Code includes

- ``cp .vscode/c_cpp_properties.json.example .vscode/c_cpp_properties.json``
- Replace ``<version>`` with kernel version (``uname -r``). <br/> E.g. for for Fedora Linux 40 (Workstation Edition) x86_64: ``"/usr/src/kernels/6.10.6-200.fc40.x86_64/include"`` 

## References

- IOCTL: https://embetronicx.com/tutorials/linux/device-drivers/ioctl-tutorial-in-linux/
- CS2 client example offsets: https://github.com/a2x/cs2-dumper
- https://github.com/spx01/baseqware-v3