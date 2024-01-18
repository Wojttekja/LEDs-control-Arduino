// IR
#define DECODE_NEC          
#include <IRremote.hpp>    

constexpr uint8_t IR_RECEIVE_PIN       {11};  // -> PD2 physical Pin 4.


// LEDy
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

#define PIN 6
#define NUMPIXELS 50
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);


void setup()
{
   Serial.begin(9600);
  

  // IR
  IrReceiver.begin(IR_RECEIVE_PIN);
  
  Serial.print(F("Ready to receive IR signals at pin "));
  Serial.println(IR_RECEIVE_PIN);


  // LEDy - jakies poczatkowe zaklecie
  #if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
  #endif
  
  pixels.begin();
  pixels.clear();
  pixels.show();

  // żeby nie zapalał się pierwszy pixel na niebiesko
  delay(10);
  pixels.clear();
  pixels.show();
}


void rozpoznanie(int komenda) {
  switch (komenda) {

    // kolory + off
    case 22:
      pixels.clear();
      pixels.show();
      break;
    
    case 12 :
      pixels.fill(pixels.Color(255, 2, 2), 0, 50);
      pixels.show();
      break;

    case 24 :
      pixels.fill(pixels.Color(255, 255, 255), 0, 50);
      pixels.show();
      break;

    case 94 :
      pixels.fill(pixels.Color(30, 0, 255), 0, 50);
      pixels.show();
      break;

    case 8 :
      pixels.fill(pixels.Color(255, 0, 50), 0, 50);
      pixels.show();
      break;

    case 28 :
      pixels.fill(pixels.Color(255, 70, 21), 0, 50);
      pixels.show();
      break;

    case 90 :
      pixels.fill(pixels.Color(128, 139, 0), 0, 50);
      pixels.show();
      break;


    // jasność
    case 25 :
      pixels.setBrightness(pixels.getBrightness()-10);
      pixels.show();
      break;
    
    case 13 :
      pixels.setBrightness(pixels.getBrightness()+10);
      pixels.show();
      break;

    // tecza
    case 66 :
      // przez minutę - 3 razy
      for (int i = 0; i < 3; i++) {
        rainbow(10);
      }

      pixels.clear();
      pixels.show();
      break;
  
    // wolniej
    case 82 : 
      while (2 == 2) {
        rainbow(40);
      }

      pixels.clear();
      pixels.show();
      break;

    // szybciej
    case 74 : 
        while (1 == 1) {
          rainbow(10);
        }


        pixels.clear();
        pixels.show();
        break;
    }
}

void rainbow(int wait) {
  for(long firstPixelHue = 0; firstPixelHue < 5*65536; firstPixelHue += 256) {
    for(int i=0; i<pixels.numPixels(); i++) { 
      int pixelHue = firstPixelHue + (i * 65536L / pixels.numPixels());
      pixels.setPixelColor(i, pixels.gamma32(pixels.ColorHSV(pixelHue)));
    }
    pixels.show();
    delay(wait);
  }
}


void loop() {
  if (IrReceiver.decode()) {

    // jeżeli nierozpoznano
    if (IrReceiver.decodedIRData.protocol == UNKNOWN) {
        // Nie rozpoznano, lepiej strzelaj tym pilotem
        // IrReceiver.printIRResultRawFormatted(&Serial, true);
        Serial.println("Nie rozpoznano, lepiej strzelaj tym pilotem");
    }

    // tutaj rozpoznaje dobrze komendy
    if (IrReceiver.decodedIRData.protocol == NEC) {  
			Serial.println(IrReceiver.decodedIRData.command);

      rozpoznanie(IrReceiver.decodedIRData.command);

    }

    IrReceiver.resume();
  } 
}