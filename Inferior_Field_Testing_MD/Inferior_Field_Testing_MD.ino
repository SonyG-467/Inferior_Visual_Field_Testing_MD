/*
 * Author :: Sony G
 * Date :: 6th Jan, 2017
 * Code for Sweep
 * Sweep starts in 7th meridian
 * Then moves to daisy meridian corresponding to it
 * The fixation point is on the daisy meridian corresponding to 19th meridian (2nd and 3rd pixels)
 * Repeats the same  
 */


#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

// Which pin on the Arduino is connected to the NeoPixels?
#define PIN_1            30
#define PIN_3            11
// How many NeoPixels are attached to the Arduino?
int STRIP_ONE = 13;
int DAISY = 72;
int FIXATION_1, FIXATION_2, fixation;
unsigned long cur_millis=0;
int i=0;
int j=STRIP_ONE - 1;
int jj;
unsigned long delayval=1000;
int ll;
int mer[] = {7,19};

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel strip_one = Adafruit_NeoPixel(STRIP_ONE, PIN_1, NEO_GRB + NEO_KHZ800);      //Seventh meridian
Adafruit_NeoPixel daisy = Adafruit_NeoPixel(DAISY, PIN_3, NEO_GRB + NEO_KHZ800);              //Daisy meridian corresponding to Seventh meridian

void setup() {

  ll=daisyConverter(7); // To get the corresponding meridian in Daisy of the Given merdian
  Serial.println(ll);
  jj = 3 * ll;
  cur_millis=millis();
  fixation=daisyConverter(19);
  Serial.println(ll);
  FIXATION_1 = (3*fixation)+1;
  FIXATION_2 = (3*fixation)+2;
  strip_one.begin(); // This initializes the NeoPixel library.
  daisy.begin();
  Serial.begin(9600);
}


void loop() {
  //strip_one.clear();

  daisy.setPixelColor(FIXATION_1,daisy.Color(100,0,0));   // Fixing the Fixtion LEDs 
  daisy.setPixelColor(FIXATION_2,daisy.Color(100,0,0));
  daisy.show(); // To display it all the time

  if((j) >= 0 && j < 999 )  // Within the range of Strip-7 LEDs 
  {
      if(millis() - cur_millis <= delayval)   // To wait for given time i.e. delayval(1000) = 1 sec
      {}
      else
      {
        Serial.println("outside");
        Serial.println(j);
          Serial.print("In one");
          Serial.println(j);
          strip_one.clear();
           for(int k = 0; k < FIXATION_1; k++)
           {
             daisy.setPixelColor(k,daisy.Color(0,0,0)); //Clears the Daisy
           }
            daisy.show();
           Serial.println(j);
          strip_one.setPixelColor(j,strip_one.Color(0,0,100));    //Sweep on Strip-7
           Serial.println(j);
          //strip_one.setPixelColor(STRIP_ONE-1,strip_one.Color(0,0,100));
          //strip_one.setPixelColor(STRIP_ONE-2,strip_one.Color(0,0,100));
          strip_one.show();
          cur_millis = millis();  // Assigns current time
          j = j - 1;    
        }
     }

     //Sweep in Daisy
      if(j < 0) // Out of Strip-7
      {
          if(millis() - cur_millis <= delayval)   // To wait for given time
          {
            
          }
          else
          {
           strip_one.clear();
           for(int j=0;j<STRIP_ONE;j++)
           {
             strip_one.setPixelColor(j,strip_one.Color(0,0,0)); // Clears Strip - 7 before starting the sweep in Daisy
           }
           strip_one.show();
            Serial.println("Daisy cleared");
           for(int k = 0; k < DAISY; k++)
           {
             daisy.setPixelColor(k,daisy.Color(0,0,0));   // Clears thee Daisy
           }
            daisy.show();
            
           if(jj < 3 * (ll + 1))
           {
             daisy.setPixelColor(jj,daisy.Color(0,100,0));  // Sweep in Daisy
           }
           daisy.show();
           Serial.println(jj);
           cur_millis = millis();
           jj = jj + 1;
          
           if(jj >= 3*(ll+1))
           {
              j=STRIP_ONE;
              i=0;
              jj = 3 * ll;;   //Assign random to break the condition
           }
          }
      }
}
int daisyConverter(int n) {
  // converts the given meridian into the daisy "meridian"
  if (n < 8) {
    return 7 - n;
  } else {
    return -n + 31;
  }
}

