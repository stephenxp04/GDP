################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../SDK/board/board.c \
../SDK/board/gpio_pins.c \
../SDK/board/hardware_init.c \
../SDK/board/pin_mux.c 

OBJS += \
./SDK/board/board.o \
./SDK/board/gpio_pins.o \
./SDK/board/hardware_init.o \
./SDK/board/pin_mux.o 

C_DEPS += \
./SDK/board/board.d \
./SDK/board/gpio_pins.d \
./SDK/board/hardware_init.d \
./SDK/board/pin_mux.d 


# Each subdirectory must supply rules for building sources it contributes
SDK/board/%.o: ../SDK/board/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -D_DEBUG=1 -D"CPU_MK64FN1M0VMD12" -DSD_DISK_ENABLE=1 -DFREEDOM -DFRDM_K64F -DCD_USING_GPIO -I"C:\Freescale\KSDK_1.2.0/platform/drivers/inc" -I"C:\Freescale\KSDK_1.2.0/platform/osa/inc" -I"C:\Freescale\KSDK_1.2.0/platform/hal/inc" -I"C:\Freescale\KSDK_1.2.0/platform/system/inc" -I"D:/GDP/K64_FatFs_KSDK/Sources" -I"D:/GDP/K64_FatFs_KSDK/fatfs" -I"D:/GDP/K64_FatFs_KSDK/fatfs/fsl_sd_disk" -I"D:/GDP/K64_FatFs_KSDK/Project_Settings/Startup_Code" -I"D:/GDP/K64_FatFs_KSDK/SDK/board" -I"D:/GDP/K64_FatFs_KSDK/SDK/composite/inc" -I"D:/GDP/K64_FatFs_KSDK/SDK/platform/utilities" -I"D:/GDP/K64_FatFs_KSDK/SDK/platform/devices" -I"D:/GDP/K64_FatFs_KSDK/SDK/platform/osa" -I"D:/GDP/K64_FatFs_KSDK/SDK/platform/CMSIS/Include" -I"D:/GDP/K64_FatFs_KSDK/SDK/platform/devices/MK64F12/include" -I"C:\Freescale\KSDK_1.2.0/platform/composite/src/sdcard" -I"C:\Freescale\KSDK_1.2.0/platform/utilities/inc" -I"C:\Freescale\KSDK_1.2.0/platform/drivers/inc" -I"C:\Freescale\KSDK_1.2.0/platform/hal/inc" -I"C:\Freescale\KSDK_1.2.0/platform/composite/inc" -I"C:\Freescale\KSDK_1.2.0/platform/drivers/src/sdhc" -I"C:\Freescale\KSDK_1.2.0/platform/drivers/src/i2c" -I"C:\Freescale\KSDK_1.2.0/platform/utilities/src" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


