################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Project_Settings/Startup_Code/startup.c \
../Project_Settings/Startup_Code/system_MK64F12.c 

S_UPPER_SRCS += \
../Project_Settings/Startup_Code/startup_MK64F12.S 

OBJS += \
./Project_Settings/Startup_Code/startup.o \
./Project_Settings/Startup_Code/startup_MK64F12.o \
./Project_Settings/Startup_Code/system_MK64F12.o 

C_DEPS += \
./Project_Settings/Startup_Code/startup.d \
./Project_Settings/Startup_Code/system_MK64F12.d 

S_UPPER_DEPS += \
./Project_Settings/Startup_Code/startup_MK64F12.d 


# Each subdirectory must supply rules for building sources it contributes
Project_Settings/Startup_Code/%.o: ../Project_Settings/Startup_Code/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -D_DEBUG=1 -D"CPU_MK64FN1M0VMD12" -DSD_DISK_ENABLE=1 -DFREEDOM -DFRDM_K64F -DCD_USING_GPIO -I"C:\Freescale\KSDK_1.2.0/platform/drivers/inc" -I"C:\Freescale\KSDK_1.2.0/platform/osa/inc" -I"C:\Freescale\KSDK_1.2.0/platform/hal/inc" -I"C:\Freescale\KSDK_1.2.0/platform/system/inc" -I"D:/GDP/K64_FatFs_KSDK/Sources" -I"D:/GDP/K64_FatFs_KSDK/fatfs" -I"D:/GDP/K64_FatFs_KSDK/fatfs/fsl_sd_disk" -I"D:/GDP/K64_FatFs_KSDK/Project_Settings/Startup_Code" -I"D:/GDP/K64_FatFs_KSDK/SDK/board" -I"D:/GDP/K64_FatFs_KSDK/SDK/composite/inc" -I"D:/GDP/K64_FatFs_KSDK/SDK/platform/utilities" -I"D:/GDP/K64_FatFs_KSDK/SDK/platform/devices" -I"D:/GDP/K64_FatFs_KSDK/SDK/platform/osa" -I"D:/GDP/K64_FatFs_KSDK/SDK/platform/CMSIS/Include" -I"D:/GDP/K64_FatFs_KSDK/SDK/platform/devices/MK64F12/include" -I"C:\Freescale\KSDK_1.2.0/platform/composite/src/sdcard" -I"C:\Freescale\KSDK_1.2.0/platform/utilities/inc" -I"C:\Freescale\KSDK_1.2.0/platform/drivers/inc" -I"C:\Freescale\KSDK_1.2.0/platform/hal/inc" -I"C:\Freescale\KSDK_1.2.0/platform/composite/inc" -I"C:\Freescale\KSDK_1.2.0/platform/drivers/src/sdhc" -I"C:\Freescale\KSDK_1.2.0/platform/drivers/src/i2c" -I"C:\Freescale\KSDK_1.2.0/platform/utilities/src" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Project_Settings/Startup_Code/%.o: ../Project_Settings/Startup_Code/%.S
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU Assembler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


