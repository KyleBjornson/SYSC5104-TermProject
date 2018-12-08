# Only modify USER_OBJECTS and INCLUDE_USER_PATHS! Do not modify anything else

GCC_BIN = 
PROJECT = LineTrackingRobot_ECDBoostNBMED
DEVSDIR = ./pdevslib/boost/simulation/pdevs
OBJECTS = ./internal/hwTime.o ./internal/eTime.o
DEVS_OBJECTS =
SYS_OBJECTS = ./mbed-src/targets/cmsis/TARGET_STM/TARGET_STM32F4/TARGET_NUCLEO_F411RE/TOOLCHAIN_GCC_ARM/startup_stm32f411xe.o ./mbed-src/targets/hal/TARGET_STM/TARGET_STM32F4/pwmout_api.o ./mbed-src/targets/hal/TARGET_STM/TARGET_STM32F4/serial_api.o ./mbed-src/targets/hal/TARGET_STM/TARGET_STM32F4/pinmap.o ./mbed-src/targets/hal/TARGET_STM/TARGET_STM32F4/sleep.o ./mbed-src/targets/hal/TARGET_STM/TARGET_STM32F4/us_ticker.o ./mbed-src/targets/hal/TARGET_STM/TARGET_STM32F4/port_api.o ./mbed-src/targets/hal/TARGET_STM/TARGET_STM32F4/gpio_api.o ./mbed-src/targets/hal/TARGET_STM/TARGET_STM32F4/rtc_api.o ./mbed-src/targets/hal/TARGET_STM/TARGET_STM32F4/mbed_overrides.o ./mbed-src/targets/hal/TARGET_STM/TARGET_STM32F4/spi_api.o ./mbed-src/targets/hal/TARGET_STM/TARGET_STM32F4/gpio_irq_api.o ./mbed-src/targets/hal/TARGET_STM/TARGET_STM32F4/analogout_api.o ./mbed-src/targets/hal/TARGET_STM/TARGET_STM32F4/i2c_api.o ./mbed-src/targets/hal/TARGET_STM/TARGET_STM32F4/analogin_api.o ./mbed-src/targets/hal/TARGET_STM/TARGET_STM32F4/TARGET_NUCLEO_F411RE/PeripheralPins.o ./mbed-src/targets/cmsis/TARGET_STM/TARGET_STM32F4/stm32f4xx_hal_flash_ramfunc.o ./mbed-src/targets/cmsis/TARGET_STM/TARGET_STM32F4/stm32f4xx_hal_i2c.o ./mbed-src/targets/cmsis/TARGET_STM/TARGET_STM32F4/stm32f4xx_hal_uart.o ./mbed-src/targets/cmsis/TARGET_STM/TARGET_STM32F4/stm32f4xx_hal_dma_ex.o ./mbed-src/targets/cmsis/TARGET_STM/TARGET_STM32F4/stm32f4xx_hal_tim_ex.o ./mbed-src/targets/cmsis/TARGET_STM/TARGET_STM32F4/stm32f4xx_hal_hcd.o ./mbed-src/targets/cmsis/TARGET_STM/TARGET_STM32F4/stm32f4xx_hal_dac.o ./mbed-src/targets/cmsis/TARGET_STM/TARGET_STM32F4/stm32f4xx_hal_sd.o ./mbed-src/targets/cmsis/TARGET_STM/TARGET_STM32F4/stm32f4xx_hal_i2c_ex.o ./mbed-src/targets/cmsis/TARGET_STM/TARGET_STM32F4/stm32f4xx_hal_qspi.o ./mbed-src/targets/cmsis/TARGET_STM/TARGET_STM32F4/stm32f4xx_hal_dma2d.o ./mbed-src/targets/cmsis/TARGET_STM/TARGET_STM32F4/stm32f4xx_hal_rcc_ex.o ./mbed-src/targets/cmsis/TARGET_STM/TARGET_STM32F4/stm32f4xx_hal_cryp.o ./mbed-src/targets/cmsis/TARGET_STM/TARGET_STM32F4/stm32f4xx_hal_pwr_ex.o ./mbed-src/targets/cmsis/TARGET_STM/TARGET_STM32F4/stm32f4xx_hal_flash_ex.o ./mbed-src/targets/cmsis/TARGET_STM/TARGET_STM32F4/stm32f4xx_hal_rcc.o ./mbed-src/targets/cmsis/TARGET_STM/TARGET_STM32F4/stm32f4xx_hal_i2s_ex.o ./mbed-src/targets/cmsis/TARGET_STM/TARGET_STM32F4/stm32f4xx_hal_iwdg.o ./mbed-src/targets/cmsis/TARGET_STM/TARGET_STM32F4/stm32f4xx_hal_sdram.o ./mbed-src/targets/cmsis/TARGET_STM/TARGET_STM32F4/stm32f4xx_hal_spi.o ./mbed-src/targets/cmsis/TARGET_STM/TARGET_STM32F4/stm32f4xx_hal_rng.o ./mbed-src/targets/cmsis/TARGET_STM/TARGET_STM32F4/stm32f4xx_hal_nand.o ./mbed-src/targets/cmsis/TARGET_STM/TARGET_STM32F4/stm32f4xx_hal_smartcard.o ./mbed-src/targets/cmsis/TARGET_STM/TARGET_STM32F4/stm32f4xx_hal_crc.o ./mbed-src/targets/cmsis/TARGET_STM/TARGET_STM32F4/stm32f4xx_hal_gpio.o ./mbed-src/targets/cmsis/TARGET_STM/TARGET_STM32F4/stm32f4xx_hal_cryp_ex.o ./mbed-src/targets/cmsis/TARGET_STM/TARGET_STM32F4/stm32f4xx_hal_rtc.o ./mbed-src/targets/cmsis/TARGET_STM/TARGET_STM32F4/stm32f4xx_hal_hash_ex.o ./mbed-src/targets/cmsis/TARGET_STM/TARGET_STM32F4/stm32f4xx_hal_adc_ex.o ./mbed-src/targets/cmsis/TARGET_STM/TARGET_STM32F4/stm32f4xx_hal.o ./mbed-src/targets/cmsis/TARGET_STM/TARGET_STM32F4/stm32f4xx_ll_usb.o ./mbed-src/targets/cmsis/TARGET_STM/TARGET_STM32F4/stm32f4xx_hal_sai.o ./mbed-src/targets/cmsis/TARGET_STM/TARGET_STM32F4/stm32f4xx_hal_hash.o ./mbed-src/targets/cmsis/TARGET_STM/TARGET_STM32F4/stm32f4xx_hal_wwdg.o ./mbed-src/targets/cmsis/TARGET_STM/TARGET_STM32F4/stm32f4xx_hal_i2s.o ./mbed-src/targets/cmsis/TARGET_STM/TARGET_STM32F4/stm32f4xx_hal_irda.o ./mbed-src/targets/cmsis/TARGET_STM/TARGET_STM32F4/stm32f4xx_ll_fsmc.o ./mbed-src/targets/cmsis/TARGET_STM/TARGET_STM32F4/stm32f4xx_hal_ltdc.o ./mbed-src/targets/cmsis/TARGET_STM/TARGET_STM32F4/stm32f4xx_hal_dma.o ./mbed-src/targets/cmsis/TARGET_STM/TARGET_STM32F4/stm32f4xx_hal_pccard.o ./mbed-src/targets/cmsis/TARGET_STM/TARGET_STM32F4/stm32f4xx_hal_eth.o ./mbed-src/targets/cmsis/TARGET_STM/TARGET_STM32F4/stm32f4xx_hal_msp_template.o ./mbed-src/targets/cmsis/TARGET_STM/TARGET_STM32F4/stm32f4xx_hal_fmpi2c.o ./mbed-src/targets/cmsis/TARGET_STM/TARGET_STM32F4/stm32f4xx_hal_sai_ex.o ./mbed-src/targets/cmsis/TARGET_STM/TARGET_STM32F4/stm32f4xx_hal_rtc_ex.o ./mbed-src/targets/cmsis/TARGET_STM/TARGET_STM32F4/stm32f4xx_hal_pcd_ex.o ./mbed-src/targets/cmsis/TARGET_STM/TARGET_STM32F4/stm32f4xx_hal_fmpi2c_ex.o ./mbed-src/targets/cmsis/TARGET_STM/TARGET_STM32F4/stm32f4xx_hal_adc.o ./mbed-src/targets/cmsis/TARGET_STM/TARGET_STM32F4/stm32f4xx_ll_sdmmc.o ./mbed-src/targets/cmsis/TARGET_STM/TARGET_STM32F4/stm32f4xx_hal_dcmi_ex.o ./mbed-src/targets/cmsis/TARGET_STM/TARGET_STM32F4/stm32f4xx_hal_usart.o ./mbed-src/targets/cmsis/TARGET_STM/TARGET_STM32F4/stm32f4xx_hal_pwr.o ./mbed-src/targets/cmsis/TARGET_STM/TARGET_STM32F4/stm32f4xx_hal_dac_ex.o ./mbed-src/targets/cmsis/TARGET_STM/TARGET_STM32F4/stm32f4xx_hal_cec.o ./mbed-src/targets/cmsis/TARGET_STM/TARGET_STM32F4/stm32f4xx_hal_spdifrx.o ./mbed-src/targets/cmsis/TARGET_STM/TARGET_STM32F4/stm32f4xx_ll_fmc.o ./mbed-src/targets/cmsis/TARGET_STM/TARGET_STM32F4/stm32f4xx_hal_dcmi.o ./mbed-src/targets/cmsis/TARGET_STM/TARGET_STM32F4/stm32f4xx_hal_tim.o ./mbed-src/targets/cmsis/TARGET_STM/TARGET_STM32F4/stm32f4xx_hal_sram.o ./mbed-src/targets/cmsis/TARGET_STM/TARGET_STM32F4/stm32f4xx_hal_cortex.o ./mbed-src/targets/cmsis/TARGET_STM/TARGET_STM32F4/stm32f4xx_hal_pcd.o ./mbed-src/targets/cmsis/TARGET_STM/TARGET_STM32F4/stm32f4xx_hal_can.o ./mbed-src/targets/cmsis/TARGET_STM/TARGET_STM32F4/stm32f4xx_hal_flash.o ./mbed-src/targets/cmsis/TARGET_STM/TARGET_STM32F4/stm32f4xx_hal_nor.o ./mbed-src/targets/cmsis/TARGET_STM/TARGET_STM32F4/TARGET_NUCLEO_F411RE/cmsis_nvic.o ./mbed-src/targets/cmsis/TARGET_STM/TARGET_STM32F4/TARGET_NUCLEO_F411RE/hal_tick.o ./mbed-src/targets/cmsis/TARGET_STM/TARGET_STM32F4/TARGET_NUCLEO_F411RE/system_stm32f4xx.o ./mbed-src/common/us_ticker_api.o ./mbed-src/common/semihost_api.o ./mbed-src/common/lp_ticker_api.o ./mbed-src/common/error.o ./mbed-src/common/pinmap_common.o ./mbed-src/common/gpio.o ./mbed-src/common/ticker_api.o ./mbed-src/common/wait_api.o ./mbed-src/common/rtc_time.o ./mbed-src/common/board.o ./mbed-src/common/assert.o ./mbed-src/common/mbed_interface.o ./mbed-src/common/InterruptIn.o ./mbed-src/common/FileSystemLike.o ./mbed-src/common/I2C.o ./mbed-src/common/SerialBase.o ./mbed-src/common/InterruptManager.o ./mbed-src/common/SPI.o ./mbed-src/common/FilePath.o ./mbed-src/common/LocalFileSystem.o ./mbed-src/common/CAN.o ./mbed-src/common/TimerEvent.o ./mbed-src/common/Ticker.o ./mbed-src/common/Ethernet.o ./mbed-src/common/SPISlave.o ./mbed-src/common/FileLike.o ./mbed-src/common/RawSerial.o ./mbed-src/common/retarget.o ./mbed-src/common/Timeout.o ./mbed-src/common/BusInOut.o ./mbed-src/common/CallChain.o ./mbed-src/common/Stream.o ./mbed-src/common/Serial.o ./mbed-src/common/FileBase.o ./mbed-src/common/Timer.o ./mbed-src/common/BusIn.o ./mbed-src/common/BusOut.o ./mbed-src/common/I2CSlave.o  
USER_OBJECTS = ./main.o ./SWO/SWO.o ./user_drivers/SeeedShieldBot/SeeedStudioShieldBot.o  #./user_drivers/ParallaxShield/ParallaxRobotShield.o
INCLUDE_PATHS = -I. -I./internal -I./pdevslib -I$(DEVSDIR) -I$(DEVSDIR)/basic_models -I"C:\repo\DEVS\boost_1_57_0" -I./mbed-src -I./mbed-src/targets -I./mbed-src/targets/hal -I./mbed-src/targets/hal/TARGET_STM -I./mbed-src/targets/hal/TARGET_STM/TARGET_STM32F4 -I./mbed-src/targets/hal/TARGET_STM/TARGET_STM32F4/TARGET_NUCLEO_F411RE -I./mbed-src/targets/cmsis -I./mbed-src/targets/cmsis/TARGET_STM -I./mbed-src/targets/cmsis/TARGET_STM/TARGET_STM32F4 -I./mbed-src/targets/cmsis/TARGET_STM/TARGET_STM32F4/TARGET_NUCLEO_F411RE -I./mbed-src/targets/cmsis/TARGET_STM/TARGET_STM32F4/TARGET_NUCLEO_F411RE/TOOLCHAIN_GCC_ARM -I./mbed-src/common -I./mbed-src/hal -I./mbed-src/api 
INCLUDE_USER_PATHS = -I./user_models -I./user_drivers -I./user_drivers/SeeedShieldBot -I./SWO #-I./user_drivers/ParallaxShield
LIBRARY_PATHS = 
LIBRARIES =  
LINKER_SCRIPT = ./mbed-src/targets/cmsis/TARGET_STM/TARGET_STM32F4/TARGET_NUCLEO_F411RE/TOOLCHAIN_GCC_ARM/STM32F411XE.ld

############################################################################### 
AS      = $(GCC_BIN)arm-none-eabi-as
CC      = $(GCC_BIN)arm-none-eabi-gcc
CPP     = $(GCC_BIN)arm-none-eabi-g++
LD      = $(GCC_BIN)arm-none-eabi-gcc
OBJCOPY = $(GCC_BIN)arm-none-eabi-objcopy
OBJDUMP = $(GCC_BIN)arm-none-eabi-objdump
SIZE    = $(GCC_BIN)arm-none-eabi-size 

ifeq ($(HARDFP),1)
	FLOAT_ABI = hard
else
	FLOAT_ABI = softfp
endif


CPU = -mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=$(FLOAT_ABI) 
CC_FLAGS = $(CPU) -c -g -fno-common -fmessage-length=0 -Wall -Wextra -fno-exceptions -ffunction-sections -fdata-sections -fomit-frame-pointer -fpermissive -MMD -MP
CC_SYMBOLS = -DTARGET_NUCLEO_F411RE -DTARGET_M4 -DTARGET_CORTEX_M -DTARGET_STM -DTARGET_STM32F4 -DTARGET_STM32F411RE -DTOOLCHAIN_GCC_ARM -DTOOLCHAIN_GCC -D__CORTEX_M4 -DARM_MATH_CM4 -D__FPU_PRESENT=1 -DMBED_BUILD_TIMESTAMP=1438050002.93 -D__MBED__=1 -DTARGET_FF_ARDUINO -DTARGET_FF_MORPHO 

LD_FLAGS = $(CPU) -Wl,--gc-sections --specs=nano.specs -u _printf_float -u _scanf_float -Wl,--wrap,main -Wl,-Map=$(PROJECT).map,--cref
LD_SYS_LIBS = -lstdc++ -lsupc++ -lm -lc -lgcc -lnosys


ifeq ($(DEBUG), 1)
  CC_FLAGS += -DDEBUG -O0
else
  CC_FLAGS += -DNDEBUG -Os
endif

.PHONY: all clean lst size

all: $(PROJECT).bin $(PROJECT).hex size


clean:
	rm -f $(PROJECT).bin $(PROJECT).elf $(PROJECT).hex $(PROJECT).map $(PROJECT).lst $(OBJECTS) $(DEVS_OBJECTS) $(USER_OBJECTS) $(SYS_OBJECTS) $(DEPS)


.asm.o:
	$(CC) $(CPU) -c -x assembler-with-cpp -o $@ $<
.s.o:
	$(CC) $(CPU) -c -x assembler-with-cpp -o $@ $<
.S.o:
	$(CC) $(CPU) -c -x assembler-with-cpp -o $@ $<

.c.o:
	$(CC)  $(CC_FLAGS) $(CC_SYMBOLS) -std=gnu99 $(INCLUDE_PATHS) $(INCLUDE_USER_PATHS) -o $@ $<

.cpp.o:
	$(CPP) $(CC_FLAGS) $(CC_SYMBOLS) -std=gnu++11 $(INCLUDE_PATHS) $(INCLUDE_USER_PATHS) -o $@ $<



$(PROJECT).elf: $(OBJECTS) $(DEVS_OBJECTS) $(USER_OBJECTS) $(SYS_OBJECTS)
	$(LD) $(LD_FLAGS) -T$(LINKER_SCRIPT) $(LIBRARY_PATHS) -o $@ $^ $(LIBRARIES) $(LD_SYS_LIBS) $(LIBRARIES) $(LD_SYS_LIBS)


$(PROJECT).bin: $(PROJECT).elf
	$(OBJCOPY) -O binary $< $@

$(PROJECT).hex: $(PROJECT).elf
	@$(OBJCOPY) -O ihex $< $@

$(PROJECT).lst: $(PROJECT).elf
	@$(OBJDUMP) -Sdh $< > $@

lst: $(PROJECT).lst

size: $(PROJECT).elf
	$(SIZE) $(PROJECT).elf

DEPS = $(OBJECTS:.o=.d) $(SYS_OBJECTS:.o=.d) $(DEVS_OBJECTS:.o=.d) $(USER_OBJECTS:.o=.d)
-include $(DEPS) 


