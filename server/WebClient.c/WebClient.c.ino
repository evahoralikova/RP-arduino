#include <SPI.h>
#include <Ethernet.h>

// Enter a MAC address for your controller below.
// Newer Ethernet shields have a MAC address printed on a sticker on the shield
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
// if you don't want to use DNS (and reduce your sketch size)
// use the numeric IP instead of the name for the server:
IPAddress server(35,163,23,102);  // numeric IP for Google (no DNS)
//IPAddress server(172,217,20,164);  // numeric IP for Google (no DNS)

//char server[] = "ec2-35-163-23-102.us-west-2.compute.amazonaws.com";    // name address for Google (using DNS)

// Set the static IP address to use if the DHCP fails to assign
IPAddress ip(192, 168, 0, 177); 

// Initialize the Ethernet client library
// with the IP address and port of the server
// that you want to connect to (port 80 is default for HTTP):
EthernetClient client;

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.println("1");

  // start the Ethernet connection:
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    // try to congifure using IP address instead of DHCP:
    Ethernet.begin(mac, ip);
  }
  // give the Ethernet shield a second to initialize:
  delay(1000);
  Serial.println("connecting...");
/*  > POST /post-temperature.php HTTP/1.1
> Host: 35.163.23.102
> User-Agent: curl/7.50.3
> Accept: *-/*
> Content-Length: 8
> Content-Type: application/x-www-form-urlencoded
*/


  // if you get a connection, report back via serial:
  if (client.connect(server, 80)) {
    Serial.println("connected");
    // Make a HTTP request:
    /*client.println("POST /post-temperature.php HTTP/1.1");
    client.println("Host: 35.163.23.102");
    client.println("Accept: *´=/*");
    client.println("Content-Length: 7");
    client.println("Content-Type: application/x-www-form-urlencoded");
    client.println("temp=23");*/
    client.println("GET /view-temperatures.php HTTP/1.1");
    client.println("Host: ec2-35-163-23-102.us-west-2.compute.amazonaws.com");
    client.println("User-Agent: curl/7.50.3");
    client.println("Accept: */*");
    client.println("Connection: close");
    client.println();
  } else {
    // if you didn't get a connection to the server:
    Serial.println("connection failed");
  }
}

void loop() {
  // if there are incoming bytes available
  // from the server, read them and print them:
  if (client.available()) {
    char c = client.read();
    Serial.print(c);
  }

  // if the server's disconnected, stop the client:
  if (!client.connected()) {
    Serial.println();
    Serial.println("disconnecting.");
    client.stop();

    // do nothing forevermore:
    while (true);
  }
}

