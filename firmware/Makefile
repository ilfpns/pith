TARGET  = pith

CC      = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy
SIZE    = arm-none-eabi-size

BUILD   = build

MCU_FLAGS = -mcpu=cortex-m3 -mthumb -mfloat-abi=soft

# if you add *.h file then you have to add new path
# -I(fimename) EX : -Iinc
CFLAGS  = $(MCU_FLAGS) -DSTM32F103xB -Iinc -g -O0 -Wall \
          -ffunction-sections -fdata-sections -fno-common -std=gnu11

ASFLAGS = $(MCU_FLAGS) -g -x assembler-with-cpp

LDFLAGS = $(MCU_FLAGS) -Tlinker/stm32f103xb.ld -nostartfiles \
          -specs=nano.specs -specs=nosys.specs \
          -Wl,--gc-sections -Wl,-Map=$(BUILD)/$(TARGET).map

SRCS_C  = src/main.c src/syscalls.c startup/system_stm32f1xx.c
SRCS_S  = startup/startup_stm32f103xb.s

OBJS    = $(SRCS_C:%.c=$(BUILD)/%.o) $(SRCS_S:%.s=$(BUILD)/%.o)

.PHONY: all clean flash

all: $(BUILD)/$(TARGET).bin

$(BUILD)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD)/%.o: %.s
	@mkdir -p $(dir $@)
	$(CC) $(ASFLAGS) -c $< -o $@

$(BUILD)/$(TARGET).elf: $(OBJS) linker/stm32f103xb.ld
	$(CC) $(LDFLAGS) -o $@ $(OBJS)
	$(SIZE) $@

$(BUILD)/$(TARGET).bin: $(BUILD)/$(TARGET).elf
	$(OBJCOPY) -O binary $< $@

flash: $(BUILD)/$(TARGET).bin
	st-flash write $(BUILD)/$(TARGET).bin 0x8000000

clean:
	rm -rf $(BUILD)
