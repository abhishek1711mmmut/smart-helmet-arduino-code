#include <Arduino.h>
#include <EEPROM.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>








#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>

/* Assign a unique ID to this sensor at the same time */
Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345);

void displaySensorDetails(void)
{
  sensor_t sensor;
  accel.getSensor(&sensor);
  Serial.println("------------------------------------");
  Serial.print  ("Sensor:       "); Serial.println(sensor.name);
  Serial.print  ("Driver Ver:   "); Serial.println(sensor.version);
  Serial.print  ("Unique ID:    "); Serial.println(sensor.sensor_id);
  Serial.print  ("Max Value:    "); Serial.print(sensor.max_value); Serial.println(" m/s^2");
  Serial.print  ("Min Value:    "); Serial.print(sensor.min_value); Serial.println(" m/s^2");
  Serial.print  ("Resolution:   "); Serial.print(sensor.resolution); Serial.println(" m/s^2");  
  Serial.println("------------------------------------");
  Serial.println("");
  delay(500);
}

void displayDataRate(void)
{
  Serial.print  ("Data Rate:    "); 
  
  switch(accel.getDataRate())
  {
    case ADXL345_DATARATE_3200_HZ:
      Serial.print  ("3200 "); 
      break;
    case ADXL345_DATARATE_1600_HZ:
      Serial.print  ("1600 "); 
      break;
    case ADXL345_DATARATE_800_HZ:
      Serial.print  ("800 "); 
      break;
    case ADXL345_DATARATE_400_HZ:
      Serial.print  ("400 "); 
      break;
    case ADXL345_DATARATE_200_HZ:
      Serial.print  ("200 "); 
      break;
    case ADXL345_DATARATE_100_HZ:
      Serial.print  ("100 "); 
      break;
    case ADXL345_DATARATE_50_HZ:
      Serial.print  ("50 "); 
      break;
    case ADXL345_DATARATE_25_HZ:
      Serial.print  ("25 "); 
      break;
    case ADXL345_DATARATE_12_5_HZ:
      Serial.print  ("12.5 "); 
      break;
    case ADXL345_DATARATE_6_25HZ:
      Serial.print  ("6.25 "); 
      break;
    case ADXL345_DATARATE_3_13_HZ:
      Serial.print  ("3.13 "); 
      break;
    case ADXL345_DATARATE_1_56_HZ:
      Serial.print  ("1.56 "); 
      break;
    case ADXL345_DATARATE_0_78_HZ:
      Serial.print  ("0.78 "); 
      break;
    case ADXL345_DATARATE_0_39_HZ:
      Serial.print  ("0.39 "); 
      break;
    case ADXL345_DATARATE_0_20_HZ:
      Serial.print  ("0.20 "); 
      break;
    case ADXL345_DATARATE_0_10_HZ:
      Serial.print  ("0.10 "); 
      break;
    default:
      Serial.print  ("???? "); 
      break;
  }  
  Serial.println(" Hz");  
}

void displayRange(void)
{
  Serial.print  ("Range:         +/- "); 
  
  switch(accel.getRange())
  {
    case ADXL345_RANGE_16_G:
      Serial.print  ("16 "); 
      break;
    case ADXL345_RANGE_8_G:
      Serial.print  ("8 "); 
      break;
    case ADXL345_RANGE_4_G:
      Serial.print  ("4 "); 
      break;
    case ADXL345_RANGE_2_G:
      Serial.print  ("2 "); 
      break;
    default:
      Serial.print  ("?? "); 
      break;
  }  
  Serial.println(" g");  
}

void setupAccelroMeter(void) 
{

  Serial.println("Accelerometer Test"); Serial.println("");
  
  /* Initialise the sensor */
  if(!accel.begin())
  {
    /* There was a problem detecting the ADXL345 ... check your connections */
    Serial.println("Ooops, no ADXL345 detected ... Check your wiring!");
    while(1);
  }

  /* Set the range to whatever is appropriate for your project */
  accel.setRange(ADXL345_RANGE_16_G);
  // accel.setRange(ADXL345_RANGE_8_G);
  // accel.setRange(ADXL345_RANGE_4_G);
  // accel.setRange(ADXL345_RANGE_2_G);
  
  /* Display some basic information on this sensor */
  displaySensorDetails();
  
  /* Display additional settings (outside the scope of sensor_t) */
  displayDataRate();
  displayRange();
  Serial.println("");
}









#define USE_DHT11  1

#ifdef USE_DHT11

#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#define DHT_PIN D5
#define DHTTYPE    DHT11
DHT_Unified dht(DHT_PIN, DHTTYPE);

uint32_t delayMSDHT11;
uint32_t lastDHTRead;

struct{
  double temp = 0.0;
  double humidity = 0.0;
  int error = 0;
} DHT11Data;


void setUpDHT11(){
dht.begin();
  Serial.println(F("DHTxx Unified Sensor Example"));
  // Print temperature sensor details.
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  Serial.println(F("------------------------------------"));
  Serial.println(F("Temperature Sensor"));
  Serial.print  (F("Sensor Type: ")); Serial.println(sensor.name);
  Serial.print  (F("Driver Ver:  ")); Serial.println(sensor.version);
  Serial.print  (F("Unique ID:   ")); Serial.println(sensor.sensor_id);
  Serial.print  (F("Max Value:   ")); Serial.print(sensor.max_value); Serial.println(F("°C"));
  Serial.print  (F("Min Value:   ")); Serial.print(sensor.min_value); Serial.println(F("°C"));
  Serial.print  (F("Resolution:  ")); Serial.print(sensor.resolution); Serial.println(F("°C"));
  Serial.println(F("------------------------------------"));
  // Print humidity sensor details.
  dht.humidity().getSensor(&sensor);
  Serial.println(F("Humidity Sensor"));
  Serial.print  (F("Sensor Type: ")); Serial.println(sensor.name);
  Serial.print  (F("Driver Ver:  ")); Serial.println(sensor.version);
  Serial.print  (F("Unique ID:   ")); Serial.println(sensor.sensor_id);
  Serial.print  (F("Max Value:   ")); Serial.print(sensor.max_value); Serial.println(F("%"));
  Serial.print  (F("Min Value:   ")); Serial.print(sensor.min_value); Serial.println(F("%"));
  Serial.print  (F("Resolution:  ")); Serial.print(sensor.resolution); Serial.println(F("%"));
  Serial.println(F("------------------------------------"));
  // Set delay between sensor readings based on sensor details.
  delayMSDHT11 = (sensor.min_delay / 1000)+200;
  lastDHTRead = millis();
}



boolean isDHTReady(){
  if( ((lastDHTRead + delayMSDHT11) < millis()) &&  ((lastDHTRead + 1000) < millis())){
    return true;
  }
  else{
    return false;
  }
}

void readDHT11(boolean printdebug){
  DHT11Data.error = 0;
  sensors_event_t event;
  dht.temperature().getEvent(&event);
  if (isnan(event.temperature)) {
    if(printdebug){
      Serial.println(F("Error reading temperature!"));
    }
    DHT11Data.error = 1;
  }
  else {
    if(printdebug){
      Serial.print(F("Temperature: "));
      Serial.print(event.temperature);
      Serial.println(F("°C"));
    }
    DHT11Data.temp =  event.temperature;//*1.8 + 32;
    Serial.println(sizeof(event.temperature));
  }
  // Get humidity event and print its value.
  dht.humidity().getEvent(&event);
  if (isnan(event.relative_humidity)) {
    if(printdebug){
      Serial.println(F("Error reading humidity!"));
    }
    DHT11Data.error = 1;
  }
  else {
    if(printdebug){
      Serial.print(F("Humidity: "));
      Serial.print(event.relative_humidity);
      Serial.println(F("%"));
    }
    DHT11Data.humidity =  event.relative_humidity;
  }
  lastDHTRead = millis();
}
#endif //USE_DHT11











///*******************************************************///
///*******************************************************///
///              SERVER CODE START FROM HERE              ///
///*******************************************************///
///*******************************************************///
#define LOLIN_LED D4
#define PRODUCTION  1
//#define DEBUG_SERVER  1
String HOME = "/"; 

/* Global vareiables are here */
unsigned long timestamp = 0;


/* Put IP Address details */
IPAddress local_ip(192,168,1,1);
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0);
ESP8266WebServer server(80);


//@auto generated code
//QR Format
//WIFI:S:MySSID;T:WPA;P:MyPassW0rd;;
//hotspot config
const char* hotspot_name = "iota0318-m";
const char* hotspot_password = "iota0318";

struct{
	String message;
	String message_class = "hide";

	String fall;
	String fall_class = "success";

	String emergency;
	String emergency_class = "success";

	String gas;
	String gas_class = "success";

	float temperature;
	String temperature_class = "success";

	int humidity;
	String humidity_class = "success";

	String btn_tourch = "OFF";
	String btn_tourch_cmd;
	String btn_tourch_class = "success";

} dataPacket;

struct{
	 const int BTN_NONE = -1;
	 const int BTN_TOURCH = 1000;
} btnAction;
int userBtnAction = btnAction.BTN_NONE;

#ifdef PRODUCTION 
String getDataJson(){
	return "{\"message\":\""+dataPacket.message+"\",\"message_class\":\""+dataPacket.message_class+"\", "
	"\"fall\":\""+dataPacket.fall+"\",\"fall_class\":\""+dataPacket.fall_class+"\", "
	"\"emergency\":\""+dataPacket.emergency+"\",\"emergency_class\":\""+dataPacket.emergency_class+"\", "
	"\"gas\":\""+dataPacket.gas+"\",\"gas_class\":\""+dataPacket.gas_class+"\", "
	"\"temperature\":\""+String(dataPacket.temperature)+"\",\"temperature_class\":\""+dataPacket.temperature_class+"\", "
	"\"humidity\":\""+String(dataPacket.humidity)+"\",\"humidity_class\":\""+dataPacket.humidity_class+"\", "
	"\"btn_tourch\":\""+dataPacket.btn_tourch+"\",\"btn_tourch_class\":\""+dataPacket.btn_tourch_class+"\"}";
}
#endif

void handel_UserAction(){
	for (uint8_t i = 0; i < server.args(); i++) {
		if(server.argName(i)== "btn_tourch"){
				userBtnAction = btnAction.BTN_TOURCH;
				dataPacket.btn_tourch_cmd = server.arg(i);
		}
	}
	server.send(200, "text/json", getDataJson());
}

#ifdef DEBUG_SERVER
String getTestClass(){
	int r = random(0,4);
	switch (r){
		case 0: return "primary";
		case 1: return "secondary";
		case 2: return "success";
		case 3: return "danger";
		case 4: return "warning";
	}
}
String getDataJson(){
	return "{\"message\":\""+String(random(10,99))+"\",\"message_class\":\""+getTestClass()+"\", "
	"\"fall\":\""+String(random(10,99))+"\",\"fall_class\":\""+getTestClass()+"\", "
	"\"emergency\":\""+String(random(10,99))+"\",\"emergency_class\":\""+getTestClass()+"\", "
	"\"gas\":\""+String(random(10,99))+"\",\"gas_class\":\""+getTestClass()+"\", "
	"\"temperature\":\""+String(random(10,99))+"\",\"temperature_class\":\""+getTestClass()+"\", "
	"\"humidity\":\""+String(random(10,99))+"\",\"humidity_class\":\""+getTestClass()+"\", "
	"\"btn_tourch\":\""+String(random(10,99))+"\",\"btn_tourch_class\":\""+getTestClass()+"\"}";
}
#endif



// auto generated code
void forwardTo(String location){
  server.sendHeader("Location", location, true);
  server.send( 302, "text/plain", "");
}

void handle_Home() {
  server.send( 200, "text/html", getTemplate());
}

void handle_DataRequest(){ 
  server.send( 200, "text/json", getDataJson());
}


void handle_NotFound(){
  forwardTo(HOME);
}


void setUpServer(){
    delay(500);
    WiFi.softAP(hotspot_name, hotspot_password);
    WiFi.softAPConfig(local_ip, gateway, subnet);
    delay(100);

    server.begin();
    delay(300);
    
    Serial.println("server started.");

}






#define GAS_PIN A0
#define LED_PIN D7
#define BUTTON_PIN D6




void setUpGPIO(void);

void setup() {
  delay(500);
  Serial.begin(115200);
  Serial.println("\n\nstartng...");
  dataPacket.btn_tourch = "OFF";
  setUpServer();
  setUpGPIO();
#ifdef USE_DHT11
  setUpDHT11();
#endif //USE_DHT11
  timestamp = millis();
  Wire.begin();
  setupAccelroMeter();
}

void setUpGPIO(){
	pinMode(LOLIN_LED,OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
}




uint32_t led_time_stamp = 0;
void blinkLed(int mil){
  if(led_time_stamp+mil < millis()){
      led_time_stamp = millis();
      if(digitalRead(LOLIN_LED) == 0){
          digitalWrite(LOLIN_LED, HIGH);
      }
      else{
        digitalWrite(LOLIN_LED, LOW);
      } 
  }
}






uint32_t lcd_update_time = 0;

int fall = 0;
int emer = 0;

int tourch = 0;

void loop() {
  server.handleClient();
  blinkLed(500);
  if(userBtnAction != btnAction.BTN_NONE){
    if(userBtnAction == btnAction.BTN_TOURCH){
      if(dataPacket.btn_tourch_cmd == "ON"){
          tourch = 1;
          dataPacket.btn_tourch_class = "danger";
          dataPacket.btn_tourch = "ON";
          digitalWrite(LED_PIN, HIGH);
      }
      else{
          tourch = 0;
          dataPacket.btn_tourch_class = "success";
          dataPacket.btn_tourch = "OFF";
          digitalWrite(LED_PIN, LOW);
      }
    }
    //
    userBtnAction = btnAction.BTN_NONE;
    Serial.println("Button clicked");
  }

  


    if(lcd_update_time+500 < millis()){
        lcd_update_time = millis();
        


        dataPacket.temperature = DHT11Data.temp;
        dataPacket.humidity = DHT11Data.humidity;


        if(dataPacket.temperature  > 45.0){
          dataPacket.temperature_class = "danger";
        }
        else{
          dataPacket.temperature_class = "success";
        }

        if(dataPacket.humidity  > 75.0){
          dataPacket.humidity_class = "danger";
        }
        else{
          dataPacket.humidity_class = "success";
        }


        sensors_event_t event; 
        accel.getEvent(&event);
        /* Display the results (acceleration is measured in m/s^2) */
        Serial.print("X: "); Serial.print(event.acceleration.x); Serial.print("  ");
        Serial.print("Y: "); Serial.print(event.acceleration.y); Serial.print("  ");
        Serial.print("Z: "); Serial.print(event.acceleration.z); Serial.print("  ");Serial.println("m/s^2 ");

        if(event.acceleration.x > 6.0){
          dataPacket.message = "Fall Detected!";
          dataPacket.message_class = "danger";
          fall = 1;
        }
        else if(event.acceleration.x < -6.0){
          dataPacket.message = "Fall Detected!";
          dataPacket.message_class = "danger";
          fall = 1;
        }
        else if(event.acceleration.y > 6.0){
          dataPacket.message = "Fall Detected!";
          dataPacket.message_class = "danger";
          fall = 1;
        }
        else if(event.acceleration.y < -6.0){
          dataPacket.message = "Fall Detected!";
          dataPacket.message_class = "danger";
          fall = 1;
        }
        else{        
          dataPacket.message_class = "hide";
          dataPacket.message = "";
          fall = 0;
        }
        
      
        if(digitalRead(BUTTON_PIN) == 0){
          dataPacket.emergency = "Emergency help required!";
          dataPacket.emergency_class = "danger";
          emer = 1;
        }
        else{
          dataPacket.emergency = "Safe";
          dataPacket.emergency_class = "success";
          emer = 0;
        }

        if(analogRead(GAS_PIN) < 400){
          dataPacket.gas = "Detected";
          dataPacket.gas_class = "danger";
        }
        else {
           dataPacket.gas = "Not Detected";
           dataPacket.gas_class = "success";
        }
        
    }

	
  


  #ifdef USE_DHT11
    if(isDHTReady()){
      readDHT11(false /*debug*/);
      if(DHT11Data.error == 1){
        Serial.println("DHT READ ERROR!");
      }else{
         Serial.print("Temp:");
         Serial.println(DHT11Data.temp);
         Serial.print("Hum:");
         Serial.println(DHT11Data.humidity);
      }
    }
  #endif //USE_DHT11
}



String getTemplate(){
	return 	"<!DOCTYPE html>\n"
	"<html>\n"
	"<head>\n"
	"<style>"
	"body{\n"
	"background-color: #F1FCFF;\n"
	"padding:0px;\n"
	"margin:0px;\n"
	"text-align: center;\n"
	"}\n"
	"header{\n"
	"height:35px;\n"
	"padding:10px;\n"
	"text-align:left;\n"
	"display: flex;\n"
	"background-color: #0093E9;\n"
	"position:fixed;\n"
	"width:100%;\n"
	"z-index:100;\n"
	"top:0;\n"
	"}\n"
	"footer{\n"
	"padding:20px;\n"
	"}\n"
	"\n"
	"form{\n"
	"margin:15px auto 0px auto;\n"
	"max-width:90%;\n"
	"background-color: #AAAAAA;\n"
	"padding: 15px 0 15px 0;\n"
	"border-radius: 5px;\n"
	"}\n"
	"\n"
	"button{\n"
	"margin:8px auto 0px auto;\n"
	"width:90%;\n"
	"background-color: #AAAAAA;\n"
	"padding: 10px 0 10px 0;\n"
	"border-radius: 5px;\n"
	"font-size: 24px;\n"
	"font-weight: bold;\n"
	"color:white;\n"
	"border: none;\n"
	"}\n"
	"button:active {\n"
	"width:89%;\n"
	"padding: 10px 0 10px 0;\n"
	"color:black;\n"
	"}\n"
	"input{\n"
	"margin:8px auto 0px auto;\n"
	"width:90%;\n"
	"padding: 10px 0 10px 0;\n"
	"border-radius: 5px;\n"
	"font-size: 22px;\n"
	"color:black;\n"
	"border: none;\n"
	"}\n"
	"\n"
	"label{\n"
	"margin:15px auto 0px auto;\n"
	"width:90%;\n"
	"padding: 0px 0 0px 0;\n"
	"font-size: 22px;\n"
	"display:block;\n"
	"}\n"
	"\n"
	".radio-group{\n"
	"margin:15px auto 15px auto;\n"
	"font-size: 24px;\n"
	"width:100%;\n"
	"display:flex;\n"
	"flex-direction: row;\n"
	"text-align:left;\n"
	"}\n"
	".radio-label{\n"
	"margin:0px;\n"
	"padding:0px;\n"
	"}\n"
	".radio{\n"
	"width:32px;\n"
	"margin:0px 10px 0px 15px;\n"
	"}\n"
	"\n"
	".content{\n"
	"margin-top:70px;\n"
	"}\n"
	".connection{\n"
	"margin-left:20px;\n"
	"color: white;\n"
	"}\n"
	".online{\n"
	"margin: 8px 0 0 -8px;\n"
	"font-size: 16px;\n"
	"color:white;\n"
	"}\n"
	".card{\n"
	"margin:15px auto 0px auto;\n"
	"max-width:90%;\n"
	"padding: 15px 0 15px 0;\n"
	"border-radius: 5px;\n"
	"}\n"
	".primary{\n"
	"background-color: #8BC6EC;\n"
	"visibility: visible;\n"
	"}\n"
	".secondary{\n"
	"background-color: #AAAAAA;\n"
	"visibility: visible;\n"
	"}\n"
	".success{\n"
	"background-color: #82c063;\n"
	"visibility: visible;\n"
	"}\n"
	".danger{\n"
	"background-color: #F76666;\n"
	"visibility: visible;\n"
	"}\n"
	".warning{\n"
	"background-color: #E3D377;\n"
	"visibility: visible;\n"
	"}\n"
	".hide{\n"
	"visibility: hidden;\n"
	"}\n"
	"@media only screen and (min-width: 500px) {\n"
	".card {\n"
	"max-width:400px;\n"
	"}\n"
	"button{\n"
	"max-width:400px;\n"
	"}\n"
	"form{\n"
	"max-width:400px;\n"
	"}\n"
	"label{\n"
	"max-width:400px;\n"
	"}\n"
	"}\n"
	"\n"
	"h1 {\n"
	"margin: 2px;\n"
	"color: white;\n"
	"}\n"
	"h2 {\n"
	"margin: 2px;\n"
	"color: black;\n"
	"}\n"
	"</style>\n"
	"<meta charset='utf-8'>\n"
	"<meta http-equiv='X-UA-Compatible' content='IE=edge'>\n"
	"<title>Iot</title>\n"
	"<meta name='viewport' content='width=device-width, initial-scale=1'>\n"
	"<link rel='stylesheet' type='text/css' media='screen' href='main.css'>\n"
	"\n"
	"</head>\n"
	"<body onload=\"liveDataAjax()\">\n"
	"<header>\n"
	"<span class=\"connection\" id=\"connected\">\n"
	"<svg xmlns=\"http://www.w3.org/2000/svg\" width=\"32\" height=\"32\" fill=\"currentColor\" class=\"connected\" viewBox=\"0 0 16 16\">\n"
	"<path d=\"M15.384 6.115a.485.485 0 0 0-.047-.736A12.444 12.444 0 0 0 8 3C5.259 3 2.723 3.882.663 5.379a.485.485 0 0 0-.048.736.518.518 0 0 0 .668.05A11.448 11.448 0 0 1 8 4c2.507 0 4.827.802 6.716 2.164.205.148.49.13.668-.049z\"/>\n"
	"<path d=\"M13.229 8.271a.482.482 0 0 0-.063-.745A9.455 9.455 0 0 0 8 6c-1.905 0-3.68.56-5.166 1.526a.48.48 0 0 0-.063.745.525.525 0 0 0 .652.065A8.46 8.46 0 0 1 8 7a8.46 8.46 0 0 1 4.576 1.336c.206.132.48.108.653-.065zm-2.183 2.183c.226-.226.185-.605-.1-.75A6.473 6.473 0 0 0 8 9c-1.06 0-2.062.254-2.946.704-.285.145-.326.524-.1.75l.015.015c.16.16.407.19.611.09A5.478 5.478 0 0 1 8 10c.868 0 1.69.201 2.42.56.203.1.45.07.61-.091l.016-.015zM9.06 12.44c.196-.196.198-.52-.04-.66A1.99 1.99 0 0 0 8 11.5a1.99 1.99 0 0 0-1.02.28c-.238.14-.236.464-.04.66l.706.706a.5.5 0 0 0 .707 0l.707-.707z\"/>\n"
	"</svg>\n"
	"</span>\n"
	"<span class=\"connection\" id=\"disconnected\">\n"
	"<svg xmlns=\"http://www.w3.org/2000/svg\" width=\"32\" height=\"32\" fill=\"currentColor\" class=\"connected\" viewBox=\"0 0 16 16\">\n"
	"<path d=\"M10.706 3.294A12.545 12.545 0 0 0 8 3C5.259 3 2.723 3.882.663 5.379a.485.485 0 0 0-.048.736.518.518 0 0 0 .668.05A11.448 11.448 0 0 1 8 4c.63 0 1.249.05 1.852.148l.854-.854zM8 6c-1.905 0-3.68.56-5.166 1.526a.48.48 0 0 0-.063.745.525.525 0 0 0 .652.065 8.448 8.448 0 0 1 3.51-1.27L8 6zm2.596 1.404.785-.785c.63.24 1.227.545 1.785.907a.482.482 0 0 1 .063.745.525.525 0 0 1-.652.065 8.462 8.462 0 0 0-1.98-.932zM8 10l.933-.933a6.455 6.455 0 0 1 2.013.637c.285.145.326.524.1.75l-.015.015a.532.532 0 0 1-.611.09A5.478 5.478 0 0 0 8 10zm4.905-4.905.747-.747c.59.3 1.153.645 1.685 1.03a.485.485 0 0 1 .047.737.518.518 0 0 1-.668.05 11.493 11.493 0 0 0-1.811-1.07zM9.02 11.78c.238.14.236.464.04.66l-.707.706a.5.5 0 0 1-.707 0l-.707-.707c-.195-.195-.197-.518.04-.66A1.99 1.99 0 0 1 8 11.5c.374 0 .723.102 1.021.28zm4.355-9.905a.53.53 0 0 1 .75.75l-10.75 10.75a.53.53 0 0 1-.75-.75l10.75-10.75z\"/>\n"
	"</svg>\n"
	"</span>\n"
	"<span class=\"connection\">\n"
	"<p class=\"online\" id=\"online\" >Online</p>\n"
	"</span>\n"
	"</header>\n"
	"\n"
	"<div class=\"content\">\n"
	"<div class=\"card hide\" id=\"message\">\n"
	"<span></span>\n"
	"<h1></h1>\n"
	"</div>\n"
	"<div class=\"card primary\" id=\"fall\">\n"
	"<span>\n"
	"<h3>Fall</h3>\n"
	"<svg xmlns=\"http://www.w3.org/2000/svg\" width=\"48\" height=\"48\" fill=\"red\" class=\"bi bi-water\" viewBox=\"0 0 16 16\">\n"
	"<path d=\"M8 3a1.5 1.5 0 1 0 0-3 1.5 1.5 0 0 0 0 3\"/>\n"
	"<path d=\"m5.93 6.704-.846 8.451a.768.768 0 0 0 1.523.203l.81-4.865a.59.59 0 0 1 1.165 0l.81 4.865a.768.768 0 0 0 1.523-.203l-.845-8.451A1.5 1.5 0 0 1 10.5 5.5L13 2.284a.796.796 0 0 0-1.239-.998L9.634 3.84a.7.7 0 0 1-.33.235c-.23.074-.665.176-1.304.176-.64 0-1.074-.102-1.305-.176a.7.7 0 0 1-.329-.235L4.239 1.286a.796.796 0 0 0-1.24.998l2.5 3.216c.317.316.475.758.43 1.204Z\"/>\n"
	"</svg>\n"
	"</span>\n"
	"<h1>Not Detected</h1>\n"
	"</div>\n"
	"<div class=\"card primary\" id=\"humidity\">\n"
	"<span>\n"
	"<h3>Humidity</h3>\n"
	"<svg xmlns=\"http://www.w3.org/2000/svg\" width=\"48\" height=\"48\" fill=\"white\" class=\"bi bi-thermometer-half\" viewBox=\"0 0 16 16\">\n"
	"<path d=\"M13.5 0a.5.5 0 0 0 0 1H15v2.75h-.5a.5.5 0 0 0 0 1h.5V7.5h-1.5a.5.5 0 0 0 0 1H15v2.75h-.5a.5.5 0 0 0 0 1h.5V15h-1.5a.5.5 0 0 0 0 1h2a.5.5 0 0 0 .5-.5V.5a.5.5 0 0 0-.5-.5h-2zM7 1.5l.364-.343a.5.5 0 0 0-.728 0l-.002.002-.006.007-.022.023-.08.088a28.458 28.458 0 0 0-1.274 1.517c-.769.983-1.714 2.325-2.385 3.727C2.368 7.564 2 8.682 2 9.733 2 12.614 4.212 15 7 15s5-2.386 5-5.267c0-1.05-.368-2.169-.867-3.212-.671-1.402-1.616-2.744-2.385-3.727a28.458 28.458 0 0 0-1.354-1.605l-.022-.023-.006-.007-.002-.001L7 1.5zm0 0-.364-.343L7 1.5zm-.016.766L7 2.247l.016.019c.24.274.572.667.944 1.144.611.781 1.32 1.776 1.901 2.827H4.14c.58-1.051 1.29-2.046 1.9-2.827.373-.477.706-.87.945-1.144zM3 9.733c0-.755.244-1.612.638-2.496h6.724c.395.884.638 1.741.638 2.496C11 12.117 9.182 14 7 14s-4-1.883-4-4.267z\"/>\n"
	"</svg>\n"
	"</span>\n"
	"<h1>30 &deg; C</h1>\n"
	"</div>\n"
	"<div class=\"card primary\" id=\"temperature\">\n"
	"<span>\n"
	"<h3>Temperature</h3>\n"
	"<svg xmlns=\"http://www.w3.org/2000/svg\" width=\"48\" height=\"48\" fill=\"yellow\" class=\"bi bi-thermometer-half\" viewBox=\"0 0 16 16\">\n"
	"<path d=\"M9.5 12.5a1.5 1.5 0 1 1-2-1.415V6.5a.5.5 0 0 1 1 0v4.585a1.5 1.5 0 0 1 1 1.415z\"/>\n"
	"<path d=\"M5.5 2.5a2.5 2.5 0 0 1 5 0v7.55a3.5 3.5 0 1 1-5 0V2.5zM8 1a1.5 1.5 0 0 0-1.5 1.5v7.987l-.167.15a2.5 2.5 0 1 0 3.333 0l-.166-.15V2.5A1.5 1.5 0 0 0 8 1z\"/>\n"
	"</svg>\n"
	"</span>\n"
	"<h1>30%</h1>\n"
	"</div>\n"
	"<div class=\"card primary\" id=\"gas\">\n"
	"<span>\n"
	"<h3>Carbon monoxide (CO), methane (CH4)</h3>\n"
	"<svg xmlns=\"http://www.w3.org/2000/svg\" width=\"48\" height=\"48\" fill=\"yellow\" class=\"bi bi-thermometer-half\" viewBox=\"0 0 16 16\">\n"
	"<path d=\"M12.5 2A2.5 2.5 0 0 0 10 4.5a.5.5 0 0 1-1 0A3.5 3.5 0 1 1 12.5 8H.5a.5.5 0 0 1 0-1h12a2.5 2.5 0 0 0 0-5m-7 1a1 1 0 0 0-1 1 .5.5 0 0 1-1 0 2 2 0 1 1 2 2h-5a.5.5 0 0 1 0-1h5a1 1 0 0 0 0-2M0 9.5A.5.5 0 0 1 .5 9h10.042a3 3 0 1 1-3 3 .5.5 0 0 1 1 0 2 2 0 1 0 2-2H.5a.5.5 0 0 1-.5-.5\"/>\n"
	"</svg>\n"
	"</span>\n"
	"<h1>30%</h1>\n"
	"</div>\n"
	"<div class=\"card primary\" id=\"emergency\">\n"
	"<span>\n"
	"<h3>Emergency</h3>\n"
	"<svg xmlns=\"http://www.w3.org/2000/svg\" width=\"48\" height=\"48\" fill=\"yellow\" class=\"bi bi-thermometer-half\" viewBox=\"0 0 16 16\">\n"
	"<path d=\"M8.5 5.034v1.1l.953-.55.5.867L9 7l.953.55-.5.866-.953-.55v1.1h-1v-1.1l-.953.55-.5-.866L7 7l-.953-.55.5-.866.953.55v-1.1zM13.25 9a.25.25 0 0 0-.25.25v.5c0 .138.112.25.25.25h.5a.25.25 0 0 0 .25-.25v-.5a.25.25 0 0 0-.25-.25zM13 11.25a.25.25 0 0 1 .25-.25h.5a.25.25 0 0 1 .25.25v.5a.25.25 0 0 1-.25.25h-.5a.25.25 0 0 1-.25-.25zm.25 1.75a.25.25 0 0 0-.25.25v.5c0 .138.112.25.25.25h.5a.25.25 0 0 0 .25-.25v-.5a.25.25 0 0 0-.25-.25zm-11-4a.25.25 0 0 0-.25.25v.5c0 .138.112.25.25.25h.5A.25.25 0 0 0 3 9.75v-.5A.25.25 0 0 0 2.75 9zm0 2a.25.25 0 0 0-.25.25v.5c0 .138.112.25.25.25h.5a.25.25 0 0 0 .25-.25v-.5a.25.25 0 0 0-.25-.25zM2 13.25a.25.25 0 0 1 .25-.25h.5a.25.25 0 0 1 .25.25v.5a.25.25 0 0 1-.25.25h-.5a.25.25 0 0 1-.25-.25z\"/>\n"
	"<path d=\"M5 1a1 1 0 0 1 1-1h4a1 1 0 0 1 1 1v1a1 1 0 0 1 1 1v4h3a1 1 0 0 1 1 1v7a1 1 0 0 1-1 1H1a1 1 0 0 1-1-1V8a1 1 0 0 1 1-1h3V3a1 1 0 0 1 1-1zm2 14h2v-3H7zm3 0h1V3H5v12h1v-3a1 1 0 0 1 1-1h2a1 1 0 0 1 1 1zm0-14H6v1h4zm2 7v7h3V8zm-8 7V8H1v7z\"/>\n"
	"</svg>\n"
	"</span>\n"
	"<h1>30%</h1>\n"
	"</div>\n"
	"<div class=\"card primary\" id=\"loaction\">\n"
	"<span>\n"
	"<a href=\"https://www.google.com/maps/place/ABES+Engineering+College/@28.6342933,77.4433814,17z/data=!3m1!4b1!4m6!3m5!1s0x390cee22c60837b7:0x7c35343eceb7bde0!8m2!3d28.6342886!4d77.4459563!16s%2Fm%2F0jk_wyv?entry=ttu\">\n"
	"<svg xmlns=\"http://www.w3.org/2000/svg\" width=\"48\" height=\"48\" fill=\"yellow\" class=\"bi bi-thermometer-half\" viewBox=\"0 0 16 16\">\n"
	"<path fill-rule=\"evenodd\" d=\"M8 1a3 3 0 1 0 0 6 3 3 0 0 0 0-6M4 4a4 4 0 1 1 4.5 3.969V13.5a.5.5 0 0 1-1 0V7.97A4 4 0 0 1 4 3.999zm2.493 8.574a.5.5 0 0 1-.411.575c-.712.118-1.28.295-1.655.493a1.3 1.3 0 0 0-.37.265.3.3 0 0 0-.057.09V14l.002.008.016.033a.6.6 0 0 0 .145.15c.165.13.435.27.813.395.751.25 1.82.414 3.024.414s2.273-.163 3.024-.414c.378-.126.648-.265.813-.395a.6.6 0 0 0 .146-.15l.015-.033L12 14v-.004a.3.3 0 0 0-.057-.09 1.3 1.3 0 0 0-.37-.264c-.376-.198-.943-.375-1.655-.493a.5.5 0 1 1 .164-.986c.77.127 1.452.328 1.957.594C12.5 13 13 13.4 13 14c0 .426-.26.752-.544.977-.29.228-.68.413-1.116.558-.878.293-2.059.465-3.34.465s-2.462-.172-3.34-.465c-.436-.145-.826-.33-1.116-.558C3.26 14.752 3 14.426 3 14c0-.599.5-1 .961-1.243.505-.266 1.187-.467 1.957-.594a.5.5 0 0 1 .575.411\"/>\n"
	"</svg>\n"
	"</a>\n"
	"</span>\n"
	"<h1>Location</h1>\n"
	"</div>\n"
	"\n"
	"<h3>Flashlight</h3>\n"
	"<div>\n"
	"<button onclick=\"onClickBtn('btn_tourch')\" id=\"btn_tourch\">FORWARD</button>\n"
	"</div>\n"
	"\n"
	"\n"
	"\n"
	"\n"
	"</div>\n"
	"<footer>\n"
	"\n"
	"</footer>\n"
	"\n"
	"<script>"
	"var DRT = 500;\n"
	"function updateCSSClass(element, css){\n"
	"    if(css != 'primary')\n"
	"        element.classList.remove('primary');\n"
	"    if(css != 'secondary')\n"
	"        element.classList.remove('secondary');\n"
	"    if(css != 'success')\n"
	"        element.classList.remove('success');\n"
	"    if(css != 'danger')\n"
	"        element.classList.remove('danger');\n"
	"    if(css != 'warning')\n"
	"        element.classList.remove('warning');\n"
	"    if(css != 'hide')\n"
	"        element.classList.remove('hide');\n"
	"    element.classList.add(css);\n"
	"}\n"
	"\n"
	"function updateData(data){\n"
	"\tdocument.getElementById(\"message\").children[1].innerHTML = \"\"+data.message+\"\";\n"
	"\tupdateCSSClass(document.getElementById(\"message\"), data.message_class);\n"
	"\tdocument.getElementById(\"fall\").children[1].innerHTML = \"\"+data.fall+\"\";\n"
	"\tupdateCSSClass(document.getElementById(\"fall\"), data.fall_class);\n"
	"\tdocument.getElementById(\"emergency\").children[1].innerHTML = \"\"+data.emergency+\"\";\n"
	"\tupdateCSSClass(document.getElementById(\"emergency\"), data.emergency_class);\n"
	"\tdocument.getElementById(\"gas\").children[1].innerHTML = \"\"+data.gas+\"\";\n"
	"\tupdateCSSClass(document.getElementById(\"gas\"), data.gas_class);\n"
	"\tdocument.getElementById(\"temperature\").children[1].innerHTML = \"\"+data.temperature+\" &deg;C\";\n"
	"\tupdateCSSClass(document.getElementById(\"temperature\"), data.temperature_class);\n"
	"\tdocument.getElementById(\"humidity\").children[1].innerHTML = \"\"+data.humidity+\" %\";\n"
	"\tupdateCSSClass(document.getElementById(\"humidity\"), data.humidity_class);\n"
	"\tdocument.getElementById(\"btn_tourch\").innerHTML = \"\"+data.btn_tourch+\"\";\n"
	"\tupdateCSSClass(document.getElementById(\"btn_tourch\"), data.btn_tourch_class);\n"
	"}\n"
	"\n"
	"function getCommand(btn_id, value){\n"
	"\tif(btn_id == \"btn_tourch\"){\n"
	"\t\tif(value == 'ON'){\n"
	"\t\t\treturn 'OFF';\n"
	"\t\t}else{\n"
	"\t\t\treturn 'ON';\n"
	"\t\t}\n"
	"\t}    \n"
	"}\n"
	"\n"
	"function onClickBtn(btn_id){\n"
	"\tvar val = document.getElementById(btn_id).innerHTML;\n"
	"\tvar cmd = getCommand(btn_id,val);\n"
	"    console.log(cmd)\n"
	"\tsendButtonClick('/act?'+btn_id+'='+cmd)\n"
	"}\n"
	"\n"
	"\n"
	"\n"
	"function updateNetwork(connected){\n"
	"    if(connected){\n"
	"        document.getElementById('disconnected').style.display = 'none';\n"
	"        document.getElementById('connected').style.display = 'block';\n"
	"        document.getElementById('online').innerHTML = 'Online';\n"
	"    }\n"
	"    else{\n"
	"        document.getElementById('connected').style.display = 'none';\n"
	"        document.getElementById('disconnected').style.display = 'block';\n"
	"        document.getElementById('online').innerHTML = 'Offline';\n"
	"    }\n"
	"}\n"
	"\n"
	"\n"
	"function sendButtonClick(url){\n"
	"\t\n"
	"    const xhr = new XMLHttpRequest();\n"
	"    xhr.open('GET', url, true);\n"
	"    xhr.onload = () => {\n"
	"        if(xhr.readyState === XMLHttpRequest.DONE && xhr.status === 200) {\n"
	"            var data= JSON.parse(xhr.responseText);\n"
	"            updateData(data);\n"
	"            updateNetwork(true);\n"
	"        }\n"
	"    }\n"
	"    xhr.onerror = function() {\n"
	"        updateNetwork(false);\n"
	"    };\n"
	"    xhr.send();\n"
	"}\n"
	"\n"
	"\n"
	"\n"
	"\n"
	"var netcount = 0;\n"
	"function reconnect(){\n"
	"    if(netcount == 0){\n"
	"        console.log(\"Retrying\");\n"
	"        document.getElementById('online').innerHTML = 'Retrying..';\n"
	"        setTimeout(liveDataAjax,1000);\n"
	"        return\n"
	"    }\n"
	"    netcount -= 1;\n"
	"    console.log(\"count\",netcount);\n"
	"    document.getElementById('online').innerHTML = 'Offline ('+netcount+')';\n"
	"    setTimeout(reconnect, 1000);\n"
	"}\n"
	"function liveDataAjax(){\n"
	"    const xhr = new XMLHttpRequest();\n"
	"    xhr.open('GET', '/data.json', true);\n"
	"    xhr.onload = () => {\n"
	"        if(xhr.readyState === XMLHttpRequest.DONE && xhr.status === 200) {\n"
	"            var data= JSON.parse(xhr.responseText);\n"
	"            updateData(data);\n"
	"            updateNetwork(true);\n"
	"            setTimeout(liveDataAjax, DRT);\n"
	"        }\n"
	"        else if (xhr.readyState === XMLHttpRequest.DONE){\n"
	"            updateNetwork(false);\n"
	"            netcount = 5;\n"
	"            reconnect();\n"
	"        }\n"
	"    };\n"
	"    xhr.onerror = function() {\n"
	"        updateNetwork(false);\n"
	"        netcount = 5;\n"
	"        reconnect();\n"
	"    };\n"
	"    xhr.send();\t\n"
	"}\n"
	"\n"
	"</script>\n"
	"</body>\n"
	"</html>";
}