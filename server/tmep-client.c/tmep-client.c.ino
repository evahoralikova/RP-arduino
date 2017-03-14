/*
 
 Simple sketch for sending data to the TMEP.cz 
 
 This sketch connects to a a web server and makes a request
 using a Wiznet Ethernet shield. You can use the Arduino Ethernet shield, or
 the Adafruit Ethernet shield, either one will work, as long as it's got
 a Wiznet Ethernet module on board.
 
 Uses code examples:
 
 http://www.arduino.cc/en/Tutorial/WebClientRepeating
 http://www.arduino.cc/en/Tutorial/DhcpAddressPrinter
 
 */
 
#include <SPI.h>
#include <Ethernet.h>
#include <DHT.h>
 
#define DHTPIN 2     // Data wire is plugged into port 2 on the Arduino
 #define typDHT11 DHT11     // DHT 11
//#define typDHT22 DHT22   // DHT 22 (AM2302)


#define pinDHT 5
#define typDHT11 DHT11     // DHT 11
DHT mojeDHT(pinDHT, typDHT11);

// Uncomment whatever type you're using!
//#define DHTTYPE DHT11   // DHT 11
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)
 
// initialize DHT sensor.
DHT dht(DHTPIN, DHTTYPE);
 
// assign a MAC address for the ethernet controller.
// fill in your address here:
byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};
 
// initialize the library instance:
EthernetClient client;
 
//char server[] = "tst.tmep.cz";   // domain.tmep.cz
char server[] = "dejvice-balkon.tmep.cz"; 
char guid[] = "tep";        // guid
 
unsigned long lastConnectionTime = 0;              // last time you connected to the server, in milliseconds
const unsigned long postingInterval = 60L * 1000L; // delay between updates, in milliseconds
// the "L" is needed to use long type numbers
 
void setup() {
  // start serial port:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
 
  // give the ethernet module time to boot up:
  delay(1000);
  // start the Ethernet connection:
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    // no point in carrying on, so do nothing forevermore:
    for (;;)
      ;
    }
  printIPAddress();
  dht.begin();
 mojeDHT.begin();
    
  
}
 
void loop() {
  float tep = mojeDHT.readTemperature();
  float vlh = mojeDHT.readHumidity();
  char teplotaStr[10];
  if (tep<10){
     dtostrf(tep,1,0,teplotaStr);
  }else {
    dtostrf(tep,2,0,teplotaStr);
  }
 
  char vlhkostStr[10];
  dtostrf(vlh,2,0,vlhkostStr);
  // kontrola, jestli jsou načtené hodnoty čísla pomocí funkce isnan
  Serial.println(teplotaStr);
  Serial.println(vlhkostStr);
  if (isnan(tep) || isnan(vlh)) {
    // při chybném čtení vypiš hlášku
    Serial.println("Chyba při čtení z DHT senzoru!");
  } else {
    // pokud jsou hodnoty v pořádku,
    // vypiš je po sériové lince
    Serial.print("Teplota: "); 
    Serial.print(tep);
    Serial.print(" stupnu Celsia, ");
    Serial.print("vlhkost: "); 
    Serial.print(vlh);
    Serial.println("  %");
  }
  
  switch (Ethernet.maintain())
  {
    case 1:
      //renewed fail
      Serial.println("Error: renewed fail");
      break;
 
    case 2:
      //renewed success
      Serial.println("Renewed success");
 
      //print your local IP address:
      printIPAddress();
      break;
 
    case 3:
      //rebind fail
      Serial.println("Error: rebind fail");
      break;
 
    case 4:
      //rebind success
      Serial.println("Rebind success");
 
      //print your local IP address:
      printIPAddress();
      break;
 
    default:
      //nothing happened
      break;
  }
 
 
 
  // if there's incoming data from the net connection.
  // send it out the serial port.  This is for debugging
  // purposes only:
  if (client.available()) {
    char c = client.read();
    Serial.write(c);
  }

 
  // if ten seconds have passed since your last connection,
  // then connect again and send data:
  if (millis() - lastConnectionTime > postingInterval) {
    httpRequest(teplotaStr,vlhkostStr);
  }
 for(int i=0;i<90
  ;i++){
    delay(1000);
  }
}
 
// this method makes a HTTP connection to the server:
void httpRequest(char* teplotaStr, char* vlhkostStr) {
  // close any connection before send a new request.
  // This will free the socket on the WiFi shield
  client.stop();
 
  // Read temperature
 /* float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
 
  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print("\t Humidity: ");
  Serial.println(h); */
 
  // if there's a successful connection:
  if (client.connect(server, 80)) {
    Serial.print("connecting...");
    // send the HTTP GET request:
    client.print("GET /index.php?");
    client.print(guid);
    client.print("=");
    //client.print(t);
    client.print(teplotaStr);
    client.print("&humV=");
    //client.print(h);
    client.print(vlhkostStr);
    client.println(" HTTP/1.1");
    client.print("Host: ");
    client.println(server);
    client.println("User-Agent: arduino-ethernet");
    client.println("Connection: close");
    client.println();
 
    Serial.println(" done.");
    // note the time that the connection was made:
    lastConnectionTime = millis();
  } else {
    // if you couldn't make a connection:
    Serial.println(" connection failed");
  }
}
 
void printIPAddress()
{
  Serial.print("My IP address: ");
  for (byte thisByte = 0; thisByte < 4; thisByte++) {
    // print the value of each byte of the IP address:
    Serial.print(Ethernet.localIP()[thisByte], DEC);
    Serial.print(".");
  }
 
  Serial.println();
}

