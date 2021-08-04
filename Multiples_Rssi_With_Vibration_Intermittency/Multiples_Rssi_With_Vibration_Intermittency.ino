#include <WiFi.h> //ESP32 Core WiFi Library
#include "SSD1306.h"
#include <stdio.h>

SSD1306 display(0x3c, 5, 4);
char *forkLiftSsids = "ESP32_ACCESS_POINT Zhone_4D23 Segall";
int VIBRACALL = 2;
char contadorRisco = 0;
char contadorAtencao = 0;

void setup() {
    pinMode(VIBRACALL, OUTPUT);
    display.init();
    display.clear();
}

void loop() {
    display.clear();
    display.setFont(ArialMT_Plain_24);
    byte available_networks = WiFi.scanNetworks(); //escaneia as redes
    int forkLifts = 0;
    float rssi = -200;

    for (int network = 0; network < available_networks; network++) {
        char ssid[sizeof(WiFi.SSID(network))];

        for(int i=0; i<sizeof(WiFi.SSID(network)); i++) {
            ssid[i] = WiFi.SSID(network)[i];
        }
    
        if((strstr(forkLiftSsids, ssid) != NULL)) {
            float localRssi = WiFi.RSSI(network);
            forkLifts++;

            if (localRssi > rssi) {
                rssi = localRssi;
            }
        }
    }

    if (forkLifts == 0) {
        display.clear();
        display.setFont(ArialMT_Plain_24);
        display.drawString(0, 0, "SEGURO");
    }
    else {
        if (rssi > -70) {
            display.drawString(0, 0, "PERIGO");
            digitalWrite(VIBRACALL, HIGH);

            contadorAtencao = 0;
            contadorRisco = 0;
        }
        else if (rssi > -85) {
            display.drawString(0, 0, "RISCO");

            if (contadorRisco < 5) {         
                digitalWrite(VIBRACALL, HIGH);
            }
            else {
                digitalWrite(VIBRACALL, LOW);

                if(contadorRisco == 9) {
                    contadorRisco = 0;
                }
            }

            contadorAtencao = 0;
            contadorRisco++;
        }
        else if (rssi > -100) {
            display.drawString(0, 0, "ATENCAO");

            if(contadorAtencao < 10) {
                digitalWrite(VIBRACALL, HIGH);
            }
            else {
                digitalWrite(VIBRACALL, LOW);

                if(contadorAtencao == 20) {
                    contadorAtencao = 0;
                }
            }
        
            contadorRisco = 0;
            contadorAtencao++;
        }
        else {
            display.drawString(0, 0, "SEGURO");
            digitalWrite(VIBRACALL, LOW);
        }

        char buf[10];
        gcvt(rssi, 4, buf);
        strcat(buf, " dBm");
        display.setFont(ArialMT_Plain_16);
        display.drawString(0, 28, buf);

        char number[99];
        itoa(forkLifts, number, 10);
        strcat(number, " Empilhadeira(s)");
        display.setFont(ArialMT_Plain_16);
        display.drawString(0, 48, number);
    }

    display.display();
    delay(10);
}
