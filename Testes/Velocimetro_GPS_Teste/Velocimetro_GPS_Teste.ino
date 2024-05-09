#import "components.h"
//----------------------------------------BITMAP----------------------------------------//
// 'icon_satellite', 16x16px
const unsigned char bitmap_icon_satellite [] PROGMEM = {
	0x00, 0x00, 0x0c, 0x00, 0x3e, 0x08, 0x7c, 0x1c, 0x38, 0x3e, 0x50, 0x1f, 0x80, 0x0f, 0xc0, 0x07, 
	0xe0, 0x03, 0xf2, 0x15, 0xe6, 0x38, 0x54, 0x3c, 0x08, 0x78, 0x36, 0x70, 0x66, 0x20, 0x00, 0x00
};
//----------------------------------------SPEED FUNCTION----------------------------------------//
void speedometer() {
  String gps_speed = String(gps.speed.kmph(), 0);
  display.setFont(ArialMT_Plain_24);
  display.setTextAlignment(TEXT_ALIGN_CENTER);
  display.drawString(64, 40, gps_speed); 

  // KM/H PRINT
  display.setFont(ArialMT_Plain_16);
  display.setTextAlignment(TEXT_ALIGN_RIGHT);
  display.drawString(128, 48, "KM/H");
}
//----------------------------------------SATELLITES FUNCTION----------------------------------------//
void satellites() {
  String satellites = String(gps.satellites.value(), 3);
  display.drawXbm(112, 0, 16, 16, bitmap_icon_satellite);
  display.setFont(ArialMT_Plain_10);
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.drawString(91,0,satellites);
}
//----------------------------------------ALTITUDE----------------------------------------//
void altitude() {
  String altitude = String(gps.altitude.meters(), 2);
  display.setFont(ArialMT_Plain_10);
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.drawString(0,22,"ALT:");
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.setFont(ArialMT_Plain_10);
  display.drawString(25,22, altitude+" m");
}
//----------------------------------------LATITUDE AND LONGITUDE FUNCTION----------------------------------------//
void altitude_longitude() {

  //LATITUDE//
  double latitude = gps.location.lat();
  int degreesLat = (int)latitude; 
  double minutesLat = (-1)*((latitude - degreesLat) * 60);
  int secondsLat = ((minutesLat - (int)minutesLat) * 60);
  String latitudeSTR = String(degreesLat) + "°" + String((int)minutesLat) + "'" + String(secondsLat) + "\"";
  display.setFont(ArialMT_Plain_10);
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.drawString(0,0,"LAT:");
  display.setFont(ArialMT_Plain_10);
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.drawString(25,0,latitudeSTR);

  //LONGITUDE//
  double longitude = gps.location.lng();
  int degreesLong = (int)longitude;
  double minutesLong = (-1)*((longitude - degreesLong) * 60);
  int secondsLong = ((minutesLong - (int)minutesLong) * 60);
  String longitudeSTR = String(degreesLong) + "°" + String((int)minutesLong) + "'" + String(secondsLong) + "\"";
  display.setFont(ArialMT_Plain_10);
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.drawString(0,12,"LNG:");
  display.setFont(ArialMT_Plain_10);
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.drawString(25,12,longitudeSTR);

  //LATITIDE AND LONGITUDE SERIAL PRINT//
  Serial.print("Latitude: "+latitudeSTR);
  Serial.println(" Longitude: "+longitudeSTR);
  Serial.print("");
  Serial.println("------------------------------------------");
  Serial.print("");
}
//----------------------------------------SETUP----------------------------------------//
void setup() {
  Serial.begin(115200);                                                                // Serial initialization 115200 baund rate
  ss.begin(9600);                                                                      // GPS initialization 9600 baund rate

  if (!display.init())                                                                 // If display does not detect will print a serial menssage
  {                                        
    Serial.println(F("Check Wiring!"));
    Serial.print(F("Display not allocated"));
    for (;;);
  } 
  display.clear();                                                                     // Clear the display
  display.init();                                                                      // Display initialization
  display.flipScreenVertically();                                                      
}
//----------------------------------------LOOP----------------------------------------//
void loop() {
  boolean newData = false;                                                            // Variable to indicate if a newdata was inserted
  for (unsigned long start = millis(); millis() - start < 1000;)
  {
    while (ss.available())
    {
      if (gps.encode(ss.read()))
      {
        newData = true;
      }
    }
  }
    if (gps.speed.isValid()) {                                                        

      speedometer();
      satellites();
      //faltitude();
      altitude_longitude();

      display.display();
      delay(500);
      display.clear();
    } 
     else {                                                                              // If the speed isnt avaible will show a message
       display.setFont(ArialMT_Plain_16);
       display.setTextAlignment(TEXT_ALIGN_CENTER_BOTH);
       display.drawString(64, 23, "Por Favor Espere");
       display.setFont(ArialMT_Plain_10);
       display.drawString(64, 41, "Sem conexão com o satélite");

       display.display();
       delay(1500);
       display.clear();
     }
  }
