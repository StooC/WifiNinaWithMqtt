# WifiNinaWithMqtt
A basic example of using PubSubClient with WifiNina library to access a **local** broker. This sketch just connects to WiFi and then subscribes to the topic "test/hello" using a username & password to access the broker. Any message recevied is then printed to the Serial for debugging.

Note this example is based on using [PlatformIO](https://platformio.org) with the [PyPortal M4 Environment](https://docs.platformio.org/en/latest/boards/atmelsam/adafruit_pyportal_m4.html) although it should work with any device that supports the WiFiNina library. 

# Secrets.h
This file is used to define various passwords and configuration environment specific, the following values need to be designed or removed from the code to compile

    #define WIFI_NAME       ""
    #define WIFI_PWD        ""

    #define MQTT_USERNAME   ""
    #define MQTT_PASSWORD   ""

    #define MQTT_BROKER_IP3 0
    #define MQTT_BROKER_IP4 0

Note that as this is a local broker is it assumed it will be on address 192.168.X.X so just defined last two numbers. 

To access a external broker such as a cloud broker you need to change to use MQTT client creation to use a string instead of a IP address. The use of a hostname for a local broker requires mDNS which would add lot of extra code to this example. 