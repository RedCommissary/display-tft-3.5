######################################
# Target
######################################
TARGET = hmi-display

#######################################
# Type build
######################################
DEBUG = 1
OPTIMIZE = -Og

#######################################
# Path
######################################
BUILD_DIR = build
LD_DIR = system/ldscript/
LVGL_DIR = library/gui/lvgl/src/

#################################
# GNU ARM Embedded Toolchain
#################################
PREFIX = arm-none-eabi-

CC  = $(PREFIX)gcc
CXX = $(PREFIX)g++
AS  = $(PREFIX)gcc -x assembler-with-cpp
CP  = $(PREFIX)objcopy
SZ  = $(PREFIX)size

HEX = $(CP) -O ihex
BIN = $(CP) -O binary -S

######################################
# Source files
######################################
C_SOURCES =  \
library/cmsis/src/system_stm32f4xx.c \
$(LVGL_DIR)lv_hal/lv_hal_disp.c \
$(LVGL_DIR)lv_hal/lv_hal_indev.c \
$(LVGL_DIR)lv_hal/lv_hal_tick.c \
$(LVGL_DIR)lv_core/lv_disp.c \
$(LVGL_DIR)lv_core/lv_group.c \
$(LVGL_DIR)lv_core/lv_indev.c \
$(LVGL_DIR)lv_core/lv_obj.c \
$(LVGL_DIR)lv_core/lv_refr.c \
$(LVGL_DIR)lv_core/lv_style.c \
$(LVGL_DIR)lv_draw/lv_draw_arc.c \
$(LVGL_DIR)lv_draw/lv_draw_blend.c \
$(LVGL_DIR)lv_draw/lv_draw_img.c \
$(LVGL_DIR)lv_draw/lv_draw_label.c \
$(LVGL_DIR)lv_draw/lv_draw_line.c \
$(LVGL_DIR)lv_draw/lv_draw_mask.c \
$(LVGL_DIR)lv_draw/lv_draw_rect.c \
$(LVGL_DIR)lv_draw/lv_draw_triangle.c \
$(LVGL_DIR)lv_draw/lv_img_buf.c \
$(LVGL_DIR)lv_draw/lv_img_cache.c \
$(LVGL_DIR)lv_draw/lv_img_decoder.c \
$(LVGL_DIR)lv_font/lv_font_dejavu_16_persian_hebrew.c \
$(LVGL_DIR)lv_font/lv_font_fmt_txt.c \
$(LVGL_DIR)lv_font/lv_font_loader.c \
$(LVGL_DIR)lv_font/lv_font_montserrat_14.c \
$(LVGL_DIR)lv_font/lv_font.c \
$(LVGL_DIR)lv_themes/lv_theme_empty.c \
$(LVGL_DIR)lv_themes/lv_theme_material.c \
$(LVGL_DIR)lv_themes/lv_theme_mono.c \
$(LVGL_DIR)lv_themes/lv_theme_template.c \
$(LVGL_DIR)lv_themes/lv_theme.c \
$(LVGL_DIR)lv_misc/lv_anim.c \
$(LVGL_DIR)lv_misc/lv_area.c \
$(LVGL_DIR)lv_misc/lv_async.c \
$(LVGL_DIR)lv_misc/lv_bidi.c \
$(LVGL_DIR)lv_misc/lv_color.c \
$(LVGL_DIR)lv_misc/lv_debug.c \
$(LVGL_DIR)lv_misc/lv_fs.c \
$(LVGL_DIR)lv_misc/lv_gc.c \
$(LVGL_DIR)lv_misc/lv_ll.c \
$(LVGL_DIR)lv_misc/lv_log.c \
$(LVGL_DIR)lv_misc/lv_math.c \
$(LVGL_DIR)lv_misc/lv_mem.c \
$(LVGL_DIR)lv_misc/lv_printf.c \
$(LVGL_DIR)lv_misc/lv_task.c \
$(LVGL_DIR)lv_misc/lv_templ.c \
$(LVGL_DIR)lv_misc/lv_txt_ap.c \
$(LVGL_DIR)lv_misc/lv_txt.c \
$(LVGL_DIR)lv_misc/lv_utils.c \
$(LVGL_DIR)lv_widgets/lv_arc.c \
$(LVGL_DIR)lv_widgets/lv_led.c \
$(LVGL_DIR)lv_widgets/lv_bar.c \
$(LVGL_DIR)lv_widgets/lv_btn.c \
$(LVGL_DIR)lv_widgets/lv_btnmatrix.c \
$(LVGL_DIR)lv_widgets/lv_calendar.c \
$(LVGL_DIR)lv_widgets/lv_canvas.c \
$(LVGL_DIR)lv_widgets/lv_chart.c \
$(LVGL_DIR)lv_widgets/lv_checkbox.c \
$(LVGL_DIR)lv_widgets/lv_cont.c \
$(LVGL_DIR)lv_widgets/lv_cpicker.c \
$(LVGL_DIR)lv_widgets/lv_dropdown.c \
$(LVGL_DIR)lv_widgets/lv_gauge.c \
$(LVGL_DIR)lv_widgets/lv_img.c \
$(LVGL_DIR)lv_widgets/lv_imgbtn.c \
$(LVGL_DIR)lv_widgets/lv_keyboard.c \
$(LVGL_DIR)lv_widgets/lv_label.c \
$(LVGL_DIR)lv_widgets/lv_led.c \
$(LVGL_DIR)lv_widgets/lv_line.c \
$(LVGL_DIR)lv_widgets/lv_linemeter.c \
$(LVGL_DIR)lv_widgets/lv_list.c \
$(LVGL_DIR)lv_widgets/lv_msgbox.c \
$(LVGL_DIR)lv_widgets/lv_objmask.c \
$(LVGL_DIR)lv_widgets/lv_objx_templ.c \
$(LVGL_DIR)lv_widgets/lv_page.c \
$(LVGL_DIR)lv_widgets/lv_roller.c \
$(LVGL_DIR)lv_widgets/lv_slider.c \
$(LVGL_DIR)lv_widgets/lv_spinbox.c \
$(LVGL_DIR)lv_widgets/lv_spinner.c\
$(LVGL_DIR)lv_widgets/lv_switch.c \
$(LVGL_DIR)lv_widgets/lv_table.c \
$(LVGL_DIR)lv_widgets/lv_tabview.c \
$(LVGL_DIR)lv_widgets/lv_textarea.c \
$(LVGL_DIR)lv_widgets/lv_tileview.c \
$(LVGL_DIR)lv_widgets/lv_win.c

CXX_SOURCES = \
system/startup/startupF401.cpp \
application/src/main.cpp \
application/src/Application.cpp \
library/system/Delay.cpp \
library/drivers/ili9488/ili9488.cpp

#######################################
# Macros for GCC
#######################################
C_DEFS =  \
-DSTM32F401xC

C_INCLUDES =  \
system/startup/ \
application/inc \
library/cmsis/inc \
library/bsp \
library/drivers/ili9488 \
library/gui/lvgl \
library/gui \
library/system
 
#######################################
# Flags
#######################################
CPU = -mcpu=cortex-m4
FPU = -mfpu=fpv4-sp-d16
FLOAT-ABI = -mfloat-abi=hard
MCU = $(CPU) -mthumb $(FPU) $(FLOAT-ABI)

ASFLAGS = $(MCU) $(OPTIMIZE) -Wall -fdata-sections -ffunction-sections
CFLAGS = -c $(MCU) $(DEFS) $(OPTIMIZE) $(addprefix -I,$(C_INCLUDES)) -std=c11 -Wall -fdata-sections -ffunction-sections
CXXFLAGS = -c $(MCU) $(DEFS) $(OPTIMIZE) $(addprefix -I,$(C_INCLUDES)) -std=c++17 -Wall -fdata-sections -ffunction-sections

LDSCRIPT = $(LD_DIR)stm32f401cc.ld
LIBS = -lc -lm -lnosys  
LDFLAGS = $(MCU) -specs=nosys.specs -T$(LDSCRIPT) $(LIBS) -Wl,-Map=$(BUILD_DIR)/$(TARGET).map,--cref -Wl,--gc-sections
LDFLAGS += -mcpu=cortex-m4 -mthumb

ifeq ($(DEBUG), 1)
CFLAGS += -g -gdwarf-2
CXXFLAGS += -g -gdwarf-2
endif

#################################
# Object List
#################################
OBJECTS += $(addsuffix .o,$(addprefix $(BUILD_DIR)/$(TARGET),$(basename $(C_SOURCES))))
OBJECTS += $(addsuffix .o,$(addprefix $(BUILD_DIR)/$(TARGET),$(basename $(CXX_SOURCES))))

#################################
# Target Output Files
#################################
TARGET_ELF = $(BUILD_DIR)/$(TARGET).elf
TARGET_HEX = $(BUILD_DIR)/$(TARGET).hex
TARGET_BIN = $(BUILD_DIR)/$(TARGET).bin

#################################
# Build
#################################
$(BUILD_DIR)/$(TARGET)%.o: %.cpp
	@mkdir -p $(dir $@)
	@echo $<
	@$(CXX) -c -o $@ $(CXXFLAGS) $<

$(BUILD_DIR)/$(TARGET)%.o: %.c
	@mkdir -p $(dir $@)
	@echo $<
	@$(CC) -c -o $@ $(CFLAGS) $<

$(TARGET_ELF): $(OBJECTS)
	$(CXX) -o $@ $^ $(LDFLAGS)
	$(SZ) $(TARGET_ELF)

$(TARGET_HEX): $(TARGET_ELF)
	$(HEX) $< $@

$(TARGET_BIN): $(TARGET_ELF)
	$(BIN) $< $@

#################################
# Recipes
#################################
.PHONY: all clean

all: $(TARGET_ELF) $(TARGET_HEX) $(TARGET_BIN)

clean:
	-rm -fR $(BUILD_DIR)