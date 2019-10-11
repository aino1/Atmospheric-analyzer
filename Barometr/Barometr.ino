#include <SFE_BMP180.h>
#include <Wire.h>

SFE_BMP180 pressure;
char analogSignal = A1;
char digitalSignal = 9;
char digital_port_P = 11;
char digital_port2_P = 10;
char digital_port3_P = 2;
char digital_port_T = 8;
char digital_port2_T = 7;
char digital_port3_T = 6;
char digital_port_gas = 5;
bool sost = 0;
bool sost1 = 0;
bool sost2 = 0;
bool noGas;
int GasValue=0;

void setup(){
    Serial.begin(9600);
    pressure.begin();
    pinMode(digital_port_P,OUTPUT);
    pinMode(digital_port2_P,OUTPUT);
    pinMode(digital_port3_P,OUTPUT);
    pinMode(digital_port_T,OUTPUT);
    pinMode(digital_port2_T,OUTPUT);
    pinMode(digital_port3_T,OUTPUT);
    pinMode(digital_port_gas,OUTPUT);
  
}

void loop(){
    double P;
    pinMode(digitalSignal, INPUT);
    P = getPressure();
    Serial.println(P, 4); 
    delay(100);
}

double getPressure(){
    char status;
    double T,P,p0,a;

    noGas = digitalRead(digitalSignal);
    if (noGas){
      digitalWrite(digital_port_gas,LOW);
    } else{
      digitalWrite(digital_port_gas,HIGH);
      Serial.print('1');
    }
    status = pressure.startTemperature();
    if (status != 0){
        // ожидание замера температуры
        delay(status);
        status = pressure.getTemperature(T);
        if (status != 0){
            status = pressure.startPressure(3);
            if (status != 0){
                // ожидание замера давления
                delay(status);
                status = pressure.getPressure(P,T);
                if (status != 0){
                    Serial.println(T);
                    if ((P<950)){
                    digitalWrite(digital_port_P,HIGH);
                    digitalWrite(digital_port2_P,LOW);
                    digitalWrite(digital_port3_P,LOW);
                    }
                    if (((P>950)and(P<1050))){
                    digitalWrite(digital_port2_P,HIGH);
                    digitalWrite(digital_port_P,LOW);
                    digitalWrite(digital_port3_P,LOW);
                    }
                    if ((P>1050)){
                    digitalWrite(digital_port3_P,HIGH);
                    digitalWrite(digital_port2_P,LOW);
                    digitalWrite(digital_port_P,LOW);
                    }
                    if ((T<19)){
                      digitalWrite(digital_port2_T,HIGH);
                      digitalWrite(digital_port_T,LOW);
                      digitalWrite(digital_port3_T,LOW);
                    }
                    if ((T>18)and(T < 27)){
                      digitalWrite(digital_port3_T,HIGH);
                      digitalWrite(digital_port2_T,LOW);
                      digitalWrite(digital_port_T,LOW);
                    }
                    if ((T>27)){
                      digitalWrite(digital_port3_T,HIGH);
                      digitalWrite(digital_port2_T,LOW);
                      digitalWrite(digital_port_T,LOW);
                    }
                    
                    
                }
            }
        }
    }
}
