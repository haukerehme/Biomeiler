/* 
 * File:   main.cpp
 * Author: hauke
 *
 * Created on 16. Juli 2015, 11:58
 */

#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include "dht22.h"
#include "HC_SR501.h"
#include "max7219led.h"
#include "Ausgabe.h"
#include "DS18B20.h"
#include "Relais.h"
using namespace std;

/*
 * Programmablauf:
 * Die Werte der verschiedenen Sensoren (Lufttemperatur, Wassertemperatur und 
 * Luftfeuchtigkeit) werden jede Minute gemessen und in eine 
 * CSV-Datei geschrieben. Außerdem sollen die Werte auch in eine HTML-Datei 
 * geschrieben werden. Diese HTML-Datei ist aus dem Internet abrufbar.
 * Wenn der Bewegungssensor eine Bewegung registriert, 
 * werden die aktuellen Werte auf dem Max7219 Display ausgegeben.
 */
int main(int argc, char** argv) {
    float luftfeuchtigkeit,lufttemperatur, wassertemperatur;
    lufttemperatur = 1.0;
    luftfeuchtigkeit = 1.0;
    dht22 *dht;
    HCSR501 *hc = new HCSR501();
    Ausgabe *aus;
    DS18B20 *ds;
    Relais *re = new Relais();
    time_t sek;
    struct tm *ts;
    int altTime;
    bool offenesFenster = false;
    aus = new Ausgabe();
       
        
    while(true){
        
        
        sek = time(NULL);
        ts = localtime(&sek);
        
        if(/*ts->tm_min % 5 == 0 &&*/ ts->tm_min!=altTime){
            
             
            altTime = ts->tm_min;
//            dht = new dht22();
//            while(dht->readDHT(17,&lufttemperatur,&luftfeuchtigkeit) != 0){sleep(1);}
//            delete(dht);
                /*int i = dht->readDHT(17,&lufttemperatur,&luftfeuchtigkeit);
                if(i == 0 ){
                    break;
                }
            }*/
            wassertemperatur = 0;
            ds = new DS18B20();
            wassertemperatur = ds->getTemp();
            delete(ds);
            printf("Wassertemp: %.1f\n", wassertemperatur);
            //printf("Temperatur: %.2f `C\n",lufttemperatur);
            //printf("Luftfeuchtigkeit: %.1f %\n",luftfeuchtigkeit);
                        
            //aus->ausgabeText(lufttemperatur,luftfeuchtigkeit,wassertemperatur);
            aus->writeCSV(lufttemperatur,luftfeuchtigkeit,wassertemperatur);
//            aus->writeWWW(lufttemperatur,luftfeuchtigkeit,wassertemperatur);
            printf("Wait 50 Seconds\n");
            sleep(50);
            printf("Das Warten hat ein Ende\n");
            //dht->~dht22();
            
            
        }
        else{
            printf("Wait 5 Seconds\n");
            sleep(5);
            printf("Das Warten hat ein Ende\n");
        }
    }
    
    return 0;
}

