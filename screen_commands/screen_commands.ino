  
  #include <Adafruit_GFX.h>    // Core graphics library
  #include <Adafruit_ST7735.h> // Hardware-specific library
  #include <SPI.h>
  
  #define TFT_CS     10
  #define TFT_RST    9  // you can also connect this to the Arduino reset
                        // in which case, set this #define pin to 0!
  #define TFT_DC     8
  
  // Option 1 (recommended): must use the hardware SPI pins
  // (for UNO thats sclk = 13 and sid = 11) and pin 10 must be
  // an output. This is much faster - also required if you want
  // to use the microSD card (see the image drawing example)
  Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS,  TFT_DC, TFT_RST);
  
  // Option 2: use any pins but a little slower!
  #define TFT_SCLK 13   // set these to be whatever pins you like!
  #define TFT_MOSI 11   // set these to be whatever pins you like!
  //Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);
  
    char command_input=0;
    char arg1=0;
    char arg2=0;
    char arg3=0;
    char arg4=0;
    char buf[5]={0,0,0,0,0};
    char buf_old[5]{0,0,0,0,0};
  
  byte index = 0; // Index into array; where to store the character
  int incomingByte = 0;
  
  void setup() {
    // put your setup code here, to run once:
    Serial1.begin(9600);
    Serial1.print("Hello! ST7735 TFT Test");
  
    // Use this initializer (uncomment) if you're using a 1.44" TFT
    tft.initR(INITR_144GREENTAB);   // initialize a ST7735S chip, black tab
  
    Serial1.println("Initialized");
    delay(20);
    tft.fillScreen(ST7735_BLUE);
    delay(1000);
    screen_splash_screen();
    delay(1000);
  }
  
  void screen_splash_screen() {
    tft.setTextWrap(false);
    tft.fillScreen(ST7735_BLACK);
    tft.setCursor(0, 30);
    tft.setTextColor(ST7735_WHITE);
    tft.setTextSize(2);
    tft.println("PowerBoat");
    tft.setCursor(0, 55);
    tft.println("Safety");
    tft.setCursor(0, 80);
    tft.println("Device");
  }
  
  void screen_sensor_report(int s1 , int s2 , int s3 , int s4)
  {
    tft.setTextWrap(false);
    tft.fillScreen(ST7735_BLACK);
    tft.setTextSize(2);
    
    tft.setCursor(0, 5);
    tft.setTextColor(ST7735_GREEN);
    tft.println("Report");
    
    tft.setCursor(0, 30);
    if(s1 == 49)
    {tft.setTextColor(ST7735_GREEN);
    tft.println("FSR Detect");
    } else {
      tft.setTextColor(ST7735_RED);
    tft.println("FSR failed");
    }
    
    tft.setCursor(0, 50);
    if (s2 == 49)
    {tft.setTextColor(ST7735_GREEN);
    tft.println("UPS Detect");
    } else {
      tft.setTextColor(ST7735_RED);
    tft.println("UPS failed");
    }
    
    tft.setCursor(0, 70);
    if (s3 == 49)
    {tft.setTextColor(ST7735_GREEN);
    tft.println("Cam Detect");
    } else {
      tft.setTextColor(ST7735_RED);
    tft.println("Cam failed");
    }
    
    tft.setCursor(0, 90);
    if (s4 == 49)
    {tft.setTextColor(ST7735_GREEN);
    tft.println("AXL Detect");
    } else {
      tft.setTextColor(ST7735_RED);
    tft.println("AXL failed");
    }
  }
  
  void screen_warning()
  {  
    tft.setTextWrap(false);
    tft.fillScreen(ST7735_BLACK);
    tft.setTextSize(2);
    
    tft.setCursor(0, 10);
    tft.setTextColor(ST7735_YELLOW);
    tft.println("Warning");
    tft.setCursor(0, 50);
    tft.println("Danger");
   // tft.setCursor(0, 70);
    //tft.println("Shut Down");
  }
  
  void screen_shutdown_engine()
  {  
    tft.setTextWrap(false);
    tft.fillScreen(ST7735_BLACK);
    tft.setTextSize(2);
    
    tft.setCursor(0, 10);
    tft.setTextColor(ST7735_RED);
    tft.println("Engine");
    tft.setCursor(0, 50);
    tft.println("Shut Down");
    //tft.setCursor(0, 70);
   // tft.println("Shut Down");
  }
    
  void screen_restart_engine()
  {
    tft.setTextWrap(false);
    tft.fillScreen(ST7735_BLACK);
    tft.setTextSize(2);
  
    tft.setCursor(0, 10);
    tft.setTextColor(ST7735_GREEN);
    tft.println("Driver");
    tft.setCursor(0, 50);
    tft.println("Detected");
    tft.setCursor(0, 70);
    tft.println("Unblock");
    tft.setCursor(0, 90);
    tft.println("Engine");
  }
  
  void screen_sensors_check(int s1 , int s2 , int s3 , int s4){
    
    tft.setTextWrap(false);
    tft.fillScreen(ST7735_BLACK);
    tft.setTextSize(2);
    
    tft.setCursor(0, 5);
    tft.setTextColor(ST7735_GREEN);
    tft.println("Sensor Init");
    
    tft.setCursor(0, 30);
    if(s1 == 49)
    {tft.setTextColor(ST7735_GREEN);
    tft.println("FSR check");
    } else {
      tft.setTextColor(ST7735_RED);
    tft.println("FSR failed");
    }
    
    tft.setCursor(0, 50);
    if (s2 == 49)
    {tft.setTextColor(ST7735_GREEN);
    tft.println("UPS check");
    } else {
      tft.setTextColor(ST7735_RED);
    tft.println("UPS failed");
    }
    
    tft.setCursor(0, 70);
    if (s3 == 49)
    {tft.setTextColor(ST7735_GREEN);
    tft.println("Cam check");
    } else {
      tft.setTextColor(ST7735_RED);
    tft.println("Cam failed");
    }
    
    tft.setCursor(0, 90);
    if (s4 == 49)
    {tft.setTextColor(ST7735_GREEN);
    tft.println("AXL check");
    } else {
      tft.setTextColor(ST7735_RED);
    tft.println("AXL failed");
    }
  }
  
  /*
  table of commands
  command X splash screen
  command Y sensor checckig page
  command Z Sensor Detection Page
  command A Engine Shutdown Page 
  command B Engine Restart Page
  */
  
  void loop() {
    // put your main code here, to run repeatedly:
   
      while(Serial1.available() > 0) {
       incomingByte = Serial1.read();
       buf[index] = incomingByte ;
       index++;
  
  if(buf[0] == 105)
  {
   index = 0;
   Serial1.print("i"); 
  }
  
  if(index == 5)
  {
    
    if(buf_old[0] == buf[0] && buf_old[1] == buf[1] && buf_old[2] == buf_old[2] && buf_old[3] == buf[3] && buf_old[4] == buf[4] )
    {
    index=0;}
    else {
      buf_old[0] = buf[0];
      buf_old[1] = buf[1];
      buf_old[2] = buf[2];
      buf_old[3] = buf[3];
      buf_old[4] = buf[4];
     
    index=0;
    command_input = buf[0];
    arg1 = buf[1];
    arg2 = buf[2];
    arg3 = buf[3];
    arg4 = buf[4];
    
      if(command_input == 117){
      screen_splash_screen();
      }
      else if(command_input == 118){
      screen_sensors_check(arg1,arg2,arg3,arg4);
      }
      else if(command_input == 119){
      screen_sensor_report(arg1,arg2,arg3,arg4);
      }
      else if(command_input == 120){
      screen_warning();  
      }
      else if(command_input == 122){
      screen_restart_engine();  
      }
      else if(command_input == 121){
      screen_shutdown_engine();  
      }

      else {
         tft.fillScreen(ST7735_BLACK);
        Serial.println("nope");
      }
  }
     delay(5);
    }
  }
  }
