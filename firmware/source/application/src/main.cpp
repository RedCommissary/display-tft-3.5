/********************************************************************************
 * project     HMI panel of the MCU STM32F401CCU6 and TFT ILI9488 (SPI)         *
 *                                                                              *
 * file        main.cpp                                                         *
 * author      @RedCommissary                                                   *
 * date        10.02.2021                                                       *
 *                                                                              *
 ********************************************************************************/

/********************************************************************************
 * Include 
 ********************************************************************************/

#include "main.h"
#include "lvgl.h"
#include "ili9488.h"

void lv_port_disp_init();
void disp_flush (lv_disp_drv_t * disp_drv, const lv_area_t * area, lv_color_t * color_p);
void StartDisplayProcessing();
void lv_example_arc_1();

int main() {
    Application::Init();
    StartDisplayProcessing();

    lv_init();
    lv_port_disp_init();
    lv_example_arc_1();

    while(1){
        Delay::Set(5);
        lv_tick_inc(5);
    }
}

/********************************************************************************
 * Function
 ********************************************************************************/

void lv_port_disp_init() {
    ILI9488::Init();
    ILI9488::SetBrightness(80);

    static lv_disp_buf_t draw_buf_dsc;
    static lv_color_t draw_buf[LV_HOR_RES_MAX * 10];                          
    lv_disp_buf_init(&draw_buf_dsc, draw_buf, NULL, LV_HOR_RES_MAX * 10);   


    lv_disp_drv_t disp_drv;                         
    lv_disp_drv_init(&disp_drv);                    
    disp_drv.hor_res = 480;
    disp_drv.ver_res = 320;
    disp_drv.flush_cb = disp_flush;
    disp_drv.buffer = &draw_buf_dsc;
    lv_disp_drv_register(&disp_drv);
}

void disp_flush (lv_disp_drv_t * disp_drv, const lv_area_t * area, lv_color_t * color_p) {
    uint16_t xStart = area->x1;
    uint16_t xEnd = area->x2;
    uint16_t yStart = area->y1;
    uint16_t yEnd = area->y2;
    uint16_t color = lv_color_to16(*color_p);

    ILI9488::DrawFill(xStart, yStart, xEnd, yEnd, color);

    lv_disp_flush_ready(disp_drv);
}

/********************************************************************************
 * Display processing
 ********************************************************************************/

void StartDisplayProcessing() {
    RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;     

    TIM3->PSC = 42-1;
    TIM3->ARR = 200;
    TIM3->DIER |= TIM_DIER_UIE;
    TIM3->CR1  |= TIM_CR1_CEN;

    NVIC_EnableIRQ(TIM3_IRQn);
}

void sTim3::handler (void) {
    TIM3->SR &= ~TIM_SR_UIF;
    lv_task_handler();
}

/********************************************************************************
 * Example for GUI
 ********************************************************************************/

void lv_example_arc_1() {
    lv_obj_t * arc = lv_arc_create(lv_scr_act(), NULL);
    lv_arc_set_end_angle(arc, 200);
    lv_obj_set_size(arc, 150, 150);
    lv_obj_align(arc, NULL, LV_ALIGN_CENTER, 0, 0);
}