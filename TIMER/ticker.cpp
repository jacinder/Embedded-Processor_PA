// Nucleo board 보드의 버튼을 누를 때마다 LED2의 점멸 시간의 주기가 바뀐다.
// 500ms on/off -> 1sec on/off -> 2sec on/off -> 4sec on/off -> 125ms on/off -> 250ms on/off -> 500ms on/off ...
#include "mbed.h"

DigitalOut led2(LED2);
InterruptIn button(USER_BUTTON);
Ticker led2_ticker;
float interval = 0.5;

void timeout_cb(void){
    led2 = !led2;
}

void button_onpressed_cb(void){
    led2_ticker.detach();
    interval = interval *2;
    if(interval > 4.0){
        interval = 0.125;
    }
    led2 = 1;
    led2_ticker.attach(&timeout_cb, interval);
}

int main(){
    button.mode(PullUp);
    button.fall(&button_onpressed_cb);
    led2_ticker.attach(&timeout_cb, interval);
    while(1){
    }
}
