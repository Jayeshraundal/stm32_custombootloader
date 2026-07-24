# STM32 Custom Bootloader

This repository contains a simple STM32 bootloader project built for the STM32F446RETx microcontroller. The goal of the project is to boot a firmware application from flash, verify that the application image is valid, and then jump to the application code safely.

## Project Overview

The workspace is split into two main parts:

- Bootloader project: [Bootloader_dev](Bootloader_dev)
  - Starts in the bootloader firmware region.
  - Reads the application header from flash.
  - Validates the application using a magic number, reset handler address, size limit, and CRC.
  - If the application is valid, it transfers control to the application.

- Application project: [application](application)
  - Contains the user firmware image.
  - Stores a small application header and the application code in flash.

## How the Bootloader Works

1. The bootloader firmware starts after reset.
2. It initializes UART and prints a small message to indicate that the bootloader is running.
3. It checks the application header stored in flash.
4. It validates the image using:
   - a magic number
   - valid reset handler location
   - allowed size range
   - CRC32 match
5. If everything is correct, it resets the MCU peripherals, updates the stack pointer, and jumps to the application reset handler.

## Flash Memory Layout

The project uses a simple flash layout defined in [Bootloader_dev/Core/Inc/flash_layout.h](Bootloader_dev/Core/Inc/flash_layout.h):

- Bootloader region: `0x08000000` to `0x08008000`
- Application header region: `0x08008000` to `0x0800C000`
- Application code region: `0x0800C000`

This organization keeps the bootloader separate from the application firmware and allows the bootloader to verify the application before execution.

## Folder Structure

- [Bootloader_dev](Bootloader_dev): bootloader firmware source files and linker files
- [application](application): sample application firmware source files
- [Drivers](Drivers): STM32 HAL and CMSIS driver sources
- [README.md](README.md): project documentation

