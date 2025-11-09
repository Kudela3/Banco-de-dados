#include <IRremote.h>


#include <SoftwareSerial.h>

SoftwareSerial SerialBT(10, 11);

String dado;
bool estado;
bool lampada;
int valor;
String unit;
int ctrl_lamp = 0;

unsigned long tempo;

int pinRelay = 3;
int pinLamp = 2;
int RECV_PIN = 4;
int pinrelay = 5;

IRrecv irrecv(RECV_PIN);
decode_results results;

void setup() {
  Serial.begin(9600);
  SerialBT.begin(9600);
  pinMode(pinRelay, OUTPUT);
  pinMode(pinrelay, OUTPUT);
  pinMode(pinLamp, INPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);

  digitalWrite(3, HIGH);
  irrecv.enableIRIn();
}

int on = 0;
unsigned long last = millis();


void loop() {


  

  if (SerialBT.available() > 0) {
    dado = SerialBT.readString();
    //Serial.println(dado);
    if ((dado.indexOf("L") >= 0)) {

            if(digitalRead(2) == HIGH ){
                                       delay(100);Serial.println("LAMPADA JÁ ESTÁ LIGADA");
                                       digitalWrite(3, LOW);}

            if(digitalRead(2) == LOW ){digitalWrite(3, HIGH);}
    }
    

    
    if ((dado.indexOf("D") >= 0)){

             if(digitalRead(2) == HIGH ){digitalWrite(3, HIGH);}
             if(digitalRead(2) == LOW ){
                                       delay(100);Serial.println("LAMPADA JÁ ESTÁ DESLIGADA");
                                       digitalWrite(3, LOW);ctrl_lamp = 0;
         
                                        }
                                  

    }
    
  }



  /*if (estado == true) {
    digitalWrite(3, LOW);
  }
  if (estado == false) {
    digitalWrite(3, HIGH);
  }
*/

  if (dado.length() > 0) {
    int indice = -1;
    for (int i = 0; i < dado.length(); i++) {
      if (!isDigit(dado[i])) {
        indice = i;
        break;
      }
    }

    if (indice != -1) {
      String partNum = dado.substring(0, indice);

      unit = dado.substring(indice);

      valor = partNum.toInt();
    } else {
      valor = dado.toInt();
      unit = "";
    }

  }
    if (unit == "MINUTOS") {
      tempo = valor * 60000;

   
        digitalWrite(3, HIGH);
        delay(100);
        digitalWrite(3, LOW);
        delay(tempo);
        digitalWrite(3, HIGH);
        unit = " ";
        valor = 0;
    

    }
    if (unit == "HORAS") {
      tempo = valor * 60000;
      tempo = tempo * 60;
    }





    if (irrecv.decode(&results)) {
      // If it's been at least 1/4 second since the last
      // IR received, toggle the relay
      if (millis() - last > 250) {
        on = !on;
        digitalWrite(pinrelay, on ? HIGH : LOW);
        digitalWrite(13, on ? HIGH : LOW);

      }
      last = millis();
      irrecv.resume(); // Receive the next value

    }




    /*      Serial.print("Número: ");
            Serial.println(valor);
            Serial.print("Texto: ");
            Serial.println(unit);
            Serial.print(dado);
            Serial.println("----------");
            delay(3000);
    */
 
  if (estado == true) {


    /*  if(digitalRead(2)==LOW){
        Serial.print(dado);
        Serial.print("   ");
        Serial.print(valor);
        Serial.print("   ");
        Serial.print(unit);
        Serial.print("  ");
        Serial.print(tempo);
        Serial.println();
        Serial.println();
        delay(2000);
        if(tempo>0){
        digitalWrite(3,HIGH);
        delay(tempo);
        digitalWrite(3,LOW);
        dado = 'L';
        valor = 0;
        unit = dado;
        tempo = 0;

        }
        }*/
  }

  if (estado == false) {
    /*  if(digitalRead(2)==HIGH){
      Serial.print(dado);
      Serial.println();
      delay(2000);
      digitalWrite(3,LOW);
      dado = 'D';
      valor = 0;
      unit = dado;
      tempo = 0;
      }

      }

      if((estado==false)&&(digitalRead(2)==HIGH)){

      if (irrecv.decode(&results)) {
      // If it's been at least 1/4 second since the last
      // IR received, toggle the relay
      if (millis() - last > 250) {
      on = !on;
      digitalWrite(pinrelay, on ? HIGH : LOW);
      digitalWrite(13, on ? HIGH : LOW);

      }
      last = millis();
      irrecv.resume(); // Receive the next value
      }*/
  }




}
