#!/usr/bin/env bash
set -euo pipefail

cd "$(dirname "$0")/firmware"

CC=arm-none-eabi-gcc
OBJCOPY=arm-none-eabi-objcopy
SIZE=arm-none-eabi-size

BUILD=build
TARGET=pith

MCU_FLAGS="-mcpu=cortex-m3 -mthumb -mfloat-abi=soft"
CFLAGS="$MCU_FLAGS -DSTM32F103xB -Iinc -g -O0 -Wall -ffunction-sections -fdata-sections -fno-common -std=gnu11"
ASFLAGS="$MCU_FLAGS -g -x assembler-with-cpp"
LDFLAGS="$MCU_FLAGS -Tlinker/stm32f103xb.ld -nostartfiles -specs=nano.specs -specs=nosys.specs -Wl,--gc-sections -Wl,-Map=$BUILD/$TARGET.map"

if [ "${1:-}" = "clean" ]; then
    rm -rf "$BUILD"
    echo "cleaned $BUILD/"
    exit 0
fi

mkdir -p "$BUILD"

$CC $CFLAGS -c src/main/main.c -o "$BUILD/main.o"
$CC $CFLAGS -c src/main/syscalls.c -o "$BUILD/syscalls.o"
$CC $CFLAGS -c src/clock/clock_setting.c -o "$BUILD/clock_setting.o"
$CC $CFLAGS -c startup/system_stm32f1xx.c -o "$BUILD/system_stm32f1xx.o"
$CC $ASFLAGS -c startup/startup_stm32f103xb.s -o "$BUILD/startup_stm32f103xb.o"

$CC $LDFLAGS -o "$BUILD/$TARGET.elf" \
    "$BUILD/main.o" "$BUILD/syscalls.o" "$BUILD/clock_setting.o" "$BUILD/system_stm32f1xx.o" "$BUILD/startup_stm32f103xb.o"

$OBJCOPY -O binary "$BUILD/$TARGET.elf" "$BUILD/$TARGET.bin"

$SIZE "$BUILD/$TARGET.elf"
