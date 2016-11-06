################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../fatfs/fsl_sd_disk/src/fsl_sd_disk.c 

OBJS += \
./fatfs/fsl_sd_disk/src/fsl_sd_disk.o 

C_DEPS += \
./fatfs/fsl_sd_disk/src/fsl_sd_disk.d 


# Each subdirectory must supply rules for building sources it contributes
fatfs/fsl_sd_disk/src/%.o: ../fatfs/fsl_sd_disk/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -D_DEBUG=1 -D"CPU_MK64FN1M0VMD12" -DSD_DISK_ENABLE=1 -DFREEDOM -DFRDM_K64F -DCD_USING_GPIO -I"C:\Freescale\KSDK_1.2.0/platform/drivers/inc" -I"C:\Freescale\KSDK_1.2.0/platform/osa/inc" -I"C:\Freescale\KSDK_1.2.0/platform/hal/inc" -I"C:\Freescale\KSDK_1.2.0/platform/system/inc" -I"D:/GDP/K64_FatFs_KSDK/Sources" -I"D:/GDP/K64_FatFs_KSDK/fatfs" -I"D:/GDP/K64_FatFs_KSDK/fatfs/fsl_sd_disk" -I"D:/GDP/K64_FatFs_KSDK/Project_Settings/Startup_Code" -I"D:/GDP/K64_FatFs_KSDK/SDK/board" -I"D:/GDP/K64_FatFs_KSDK/SDK/composite/inc" -I"D:/GDP/K64_FatFs_KSDK/SDK/platform/utilities" -I"D:/GDP/K64_FatFs_KSDK/SDK/platform/devices" -I"D:/GDP/K64_FatFs_KSDK/SDK/platform/osa" -I"D:/GDP/K64_FatFs_KSDK/SDK/platform/CMSIS/Include" -I"D:/GDP/K64_FatFs_KSDK/SDK/platform/devices/MK64F12/include" -I"C:\Freescale\KSDK_1.2.0/platform/composite/src/sdcard" -I"C:\Freescale\KSDK_1.2.0/platform/utilities/inc" -I"C:\Freescale\KSDK_1.2.0/platform/drivers/inc" -I"C:\Freescale\KSDK_1.2.0/platform/hal/inc" -I"C:\Freescale\KSDK_1.2.0/platform/composite/inc" -I"C:\Freescale\KSDK_1.2.0/platform/drivers/src/sdhc" -I"C:\Freescale\KSDK_1.2.0/platform/drivers/src/i2c" -I"C:\Freescale\KSDK_1.2.0/platform/utilities/src" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


