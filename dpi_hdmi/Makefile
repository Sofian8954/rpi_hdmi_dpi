
ARMGNU ?= aarch64-elf
COPS = -Wall -O3 -nostdlib -nostartfiles -ffreestanding -Iinclude -march=armv8-a+crc -mcpu=cortex-a53+fp+simd -mstrict-align -fno-tree-loop-vectorize -fno-tree-slp-vectorize
ASMOPS = -Iinclude

BUILD_DIR = build
SRC_DIR = src
DISK_DIR = disk

Pi3-64 : kernel8.img

listasm:
	$(ARMGNU)-objdump -D $(BUILD_DIR)/kernel8.elf > arm.asm

clean :
	-del /q $(BUILD_DIR)

$(BUILD_DIR)/%_c.o: $(SRC_DIR)/%.c
	$(ARMGNU)-gcc $(COPS) -MMD -c $< -o $@

$(BUILD_DIR)/%_s.o: $(SRC_DIR)/%.S
	$(ARMGNU)-gcc $(ASMOPS) -MMD -c $< -o $@

C_FILES = $(wildcard $(SRC_DIR)/*.c $(SRC_DIR)/*/*.c)

ASM_FILES = $(wildcard $(SRC_DIR)/*.S)
OBJ_FILES = $(C_FILES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%_c.o)
OBJ_FILES += $(ASM_FILES:$(SRC_DIR)/%.S=$(BUILD_DIR)/%_s.o)

DEP_FILES = $(OBJ_FILES:%.o=%.d)
-include $(DEP_FILES)

kernel8.img: $(SRC_DIR)/linker.ld $(OBJ_FILES)
	$(ARMGNU)-ld -T $(SRC_DIR)/linker.ld -o $(BUILD_DIR)/kernel8.elf  $(OBJ_FILES)
	$(ARMGNU)-objcopy $(BUILD_DIR)/kernel8.elf -O binary $(DISK_DIR)/kernel8.img
#	$(ARMGNU)-nm -n $(BUILD_DIR)/kernel8.elf > $(BUILD_DIR)/kernel8.map

run: clean kernel8.img
	qemu-system-aarch64 -M raspi3 -kernel $(DISK_DIR)/kernel8.img -serial stdio
