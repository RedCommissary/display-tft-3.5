/********************************************************************************
 * class        Settings periphery use MCU                                      *
 *                                                                              *
 * file         Periphery.h                                                     *
 * author       @RedCommissary                                                  *
 * date         10.02.2021                                                      *
 *                                                                              *
 ********************************************************************************/

#pragma once

/********************************************************************************
 * Include 
 ********************************************************************************/

#include "Pinout.h"
#include "startupF401.h"

/********************************************************************************
 * Class Periphery
 ********************************************************************************/
namespace BSP {
    class Periphery {
        public:
            static void Init();
            struct Clock {
                static void Init();
            };
            struct Led {
                enum class Status {on, off, toggle};
                static void Yellow (Status status);
                static void Green (Status status);
            };
            struct Button {
                static void Init();
                static void ResetFlag();
            };
            struct Buzzer {
                static void Init (uint16_t frequence);
                static void SetDuty (uint16_t duty);
            };
    };
}