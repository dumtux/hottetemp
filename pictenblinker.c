#define __PCB__

#if defined(__PCB__)
#include <10f222.h>
#fuses IOSC4,NOWDT,NOPROTECT, NOMCLR
#use delay(clock=4000000)
#define GP0 PIN_B0
#define GP1 PIN_B1
#define GP2 PIN_B2
#define GP3 PIN_B3

#elif defined(__PCM__)
#include <12C671.h>
#fuses INTRC,NOWDT,NOPROTECT, NOMCLR
#use delay(clock=4000000)
#define GP0 PIN_A0
#define GP1 PIN_A1
#define GP2 PIN_A2
#define GP3 PIN_A3
#define GP4 PIN_A4
#define GP5 PIN_A5

#endif


#define LED1 GP0
#define LED2 GP1
#define BTN1 GP2
#define BTN2 GP3


void blink_1 (void)
{
   output_low (LED1);
   output_low (LED2);

   for (int i=0; i<10; i++) {
      output_high (LED1);
      delay_ms (500);
      output_low (LED1);
      delay_ms (500);
   }
}

void blink_2 (void)
{
   output_low (LED1);
   output_low (LED2);

   for (int i=0; i<10; i++) {
      output_high (LED2);
      delay_ms (500);
      output_low (LED2);
      delay_ms (500);
   }
}

void main() {
#if defined(__PCB__)
   setup_counters (RTCC_INTERNAL,RTCC_DIV_2);
                               // See .h file for other special
                               // options for setup_counters
#else
   setup_counters (RTCC_INTERNAL,RTCC_DIV_2);
#endif

   output_high (LED1);
   output_high (LED2);
   delay_ms (1000);
   output_low (LED1);
   output_low (LED2);
   delay_ms (500);
   output_high (LED1);
   output_high (LED2);
   delay_ms (1000);
   output_low (LED1);
   output_low (LED2);

   while (TRUE) {
      if (!input (BTN1))
         blink_1 ();
      if (!input (BTN2))
         blink_2 ();
   }
}

