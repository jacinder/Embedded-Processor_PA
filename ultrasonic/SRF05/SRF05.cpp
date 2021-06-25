//
// mbed library를 mbed os version 6에 맞게 일부 수정하였음
//
/* mbed SRF05 Ultrasonic Rangefiner Library
 * Copyright (c) 2007-2010, cstyles, sford
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include "SRF05.h"
#include "mbed.h"

SRF05::SRF05(PinName trigger, PinName echo) 
    : _trigger(trigger), _echo(echo) {    
        
    // Attach interrupts
    _echo.rise(callback(this, &SRF05::_rising));
    _echo.fall(callback(this, &SRF05::_falling));
    _ticker.attach(callback(this, &SRF05::_startRange), 1000ms);
}
  
void SRF05::_startRange() {
    // send a trigger pulse, 20uS long
    _trigger = 1;
    //wait (0.000002);
    _timer.reset();
    _timer.start();
    while(_timer.elapsed_time().count() < 2){} //2us 기다린다.
    _timer.stop();
    _timer.reset();
    _trigger = 0;
}

// Clear and start the timer at the begining of the echo pulse
void SRF05::_rising(void) {
    _timer.reset();
    _timer.start();
}

// Stop and read the timer at the end of the pulse
void SRF05::_falling(void) {
    _timer.stop();
    _dist = _timer.elapsed_time().count() * 0.017;
}

float SRF05::read(void) {
    // spin until there is a good value
    return (_dist);
}

SRF05::operator float() {
    return read();
}
