/********************************************************************************
 * class        Settings LED                                                    *
 *                                                                              *
 * file         LED.h                                                           *
 * author       @RedCommissary                                                  *
 * date         13.02.2021                                                      *
 *                                                                              *
 ********************************************************************************/

#pragma once

/********************************************************************************
 * Include 
 ********************************************************************************/

#include "Pinout.h"

/********************************************************************************
 * Class Led
 ********************************************************************************/
class Led {
    public:
        enum class Status {on, off, toggle};

        static void Yellow (Status status) {
                switch (status) {
                case Status::on:
                    Gpio::Set<4>(GPIOB);
                    break;
                case Status::off:
                    Gpio::Reset<4>(GPIOB);
                    break;
                case Status::toggle:
                    Gpio::Toggle<4>(GPIOB);
                    break;
                default:
                    Gpio::Reset<4>(GPIOB);
                    break;
                }
        }

        static void Green (Status status) {
            switch (status) {
            case Status::on:
                Gpio::Set<5>(GPIOB);
                break;
            case Status::off:
                Gpio::Reset<5>(GPIOB);
                break;
            case Status::toggle:
                Gpio::Toggle<5>(GPIOB);
                break;
            default:
                Gpio::Reset<5>(GPIOB);
                break;
            }
        }
};