#include <mbed.h>
#include <wakaa.h>
#include <icm20689.h>
DigitalOut myled(LED1);

Wakaa taa(LED1);


void blinky()
{
  if (myled.is_connected())
  {
    printf("The Led is Connected!");
  }

  for(;;) {
    // put your main code here, to run repeatedly:
    myled.write(1);
    printf("myled = %d \n\r", (uint8_t)myled);
    ThisThread::sleep_for(1s);
    myled.write(0);
    printf("myled = %d \n\r", (uint8_t)myled);
    ThisThread::sleep_for(1s);
  }
}

int main() {
  // put your setup code here, to run once:
  blinky();
  taa.wakaa(3);
  for(;;) {
    // put your main code here, to run repeatedly:

  }
}

