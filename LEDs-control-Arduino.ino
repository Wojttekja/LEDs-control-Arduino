// IR
#define DECODE_NEC          
#include <IRremote.hpp>    

constexpr uint8_t IR_RECEIVE_PIN       {3}; 

int mode = 0, previous_mode = 1;


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

  IrReceiver.begin(IR_RECEIVE_PIN);
  Serial.println("Start");

  attachInterrupt(digitalPinToInterrupt(3), read_ir, RISING);


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

void read_ir()
{
  noInterrupts();
  
  if (IrReceiver.decode()) {
    if (IrReceiver.decodedIRData.protocol == NEC) {
      Serial.println(IrReceiver.decodedIRData.command);
      mode = IrReceiver.decodedIRData.command;
    }

    IrReceiver.resume();
  }
  interrupts();
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


void change_mode(int new_mode)
{
  switch (new_mode) {
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
  
      

    default:
      Serial.println("kys");
      break;
  }

}

void loop()
{
  if (mode != previous_mode) {
    Serial.println("changin");
    change_mode(mode);
    previous_mode = mode;
  }

  // Serial.println(mode);
  delay(10);
}