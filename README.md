Simple ESP8266 + HC-SR04 (distance) sensor used to report distance (in cm) to ThinkSpeak channel

Required header files to compile:

``WIFIConfig.h``
```C
#ifndef WIFIConfig_h
#define WIFIConfig_h

// library interface description
class WIFIConfig
{
  public:
    WIFIConfig(void);
    static const char* ssid;
    static const char* password;
};

#endif
```

``ThingSpeakConfig.h``
```C
#ifndef ThingSpeakConfig_h
#define ThingSpeakConfig_h

// library interface description
class ThingSpeakConfig
{
  public:
    ThingSpeakConfig(void);
    static const unsigned long channelID;
    static const char* writeAPIKey;
};

#endif
```

@todo:
Header files could be change to offer #define insteaf of static props.