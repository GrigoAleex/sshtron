```
                      /$$$$$$  /$$$$$$  /$$   /$$ /$$$$$$$$/$$$$$$$   /$$$$$$  /$$   /$$
                     /$$__  $$/$$__  $$| $$  | $$|__  $$__/ $$__  $$ /$$__  $$| $$$ | $$
                    | $$  \__/ $$  \__/| $$  | $$   | $$  | $$  \ $$| $$  \ $$| $$$$| $$
                    |  $$$$$$|  $$$$$$ | $$$$$$$$   | $$  | $$$$$$$/| $$  | $$| $$ $$ $$
                     \____  $$\____  $$| $$__  $$   | $$  | $$__  $$| $$  | $$| $$  $$$$
                     /$$  \ $$/$$  \ $$| $$  | $$   | $$  | $$  \ $$| $$  | $$| $$\  $$$
                    |  $$$$$$/  $$$$$$/| $$  | $$   | $$  | $$  | $$|  $$$$$$/| $$ \  $$
                     \______/ \______/ |__/  |__/   |__/  |__/  |__/ \______/ |__/  \__/
```
    
## Overview

`sshtron` is a simple tool that allows users to manage multiple SSH connections simultaneously by keeping all credentials (except SSH passwords) in one place. You can SSH directly into your server from `sshtron`. This application is designed to be cross-platform. If you encounter any issues, please report them under the Issues section of this repository.

## Features

- **Multiple SSH Connections:** Manage and connect to multiple SSH servers from a single interface.
- **Credential Management:** Store all SSH credentials securely (excluding passwords).
- **Cross-Platform:** Compatible with various operating systems.

## Prerequisites

- `make` utility

## Installation

1. Clone the repository:
    ```sh
    git clone https://github.com/GrigoAleex/sshtron.git
    cd sshtron
    ```

2. Build the executable:
    ```sh
    make
    ```

3. The executable will be located in the `build` folder:
    ```sh
    build/sshtron
    ```

## Adding `sshtron` to PATH

### Linux/Debian

1. Open your terminal.
2. Add the following line to your `.bashrc` or `.bash_profile` file:
    ```sh
    export PATH=$PATH:/path/to/sshtron/build
    ```
3. Apply the changes:
    ```sh
    source ~/.bashrc
    ```

### macOS

1. Open your terminal.
2. Add the following line to your `.bash_profile` or `.zshrc` file:
    ```sh
    export PATH=$PATH:/path/to/sshtron/build
    ```
3. Apply the changes:
    ```sh
    source ~/.bash_profile
    ```

### Windows

1. Open the Start Search, type in "env", and select "Edit the system environment variables".
2. In the System Properties window, click on the "Environment Variables" button.
3. In the Environment Variables window, select the `Path` variable in the "System variables" section and click "Edit".
4. Click "New" and add the path to the `sshtron` executable:
    ```
    C:\path\to\sshtron\build
    ```
5. Click "OK" to close all windows.

## Usage

Run the `sshtron` executable to start managing your SSH connections.

### Example Usage

```sh
sshtron
```

## Issue Reporting

If you encounter any issues, please report them [here](https://github.com/GrigoAleex/sshtron/issues).

## FAQ

**Q: How do I edit a connection?**

A: You can not. Delete it and create a new one.

## Contributing

Contributions are welcome! Please follow these steps to contribute:

1. Fork the repository.
2. Create a new branch (`git checkout -b feature-branch`).
3. Make your changes.
4. Commit your changes (`git commit -m 'Add some feature'`).
5. Push to the branch (`git push origin feature-branch`).
6. Open a Pull Request.

## License

This project is licensed under the GNU GPL License. See the [LICENSE](LICENSE) file for details.

## Contact

For questions, please open an issue in the repository.
