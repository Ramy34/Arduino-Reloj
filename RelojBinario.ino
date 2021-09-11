//Programa: Reloj_Binario
//Autor: Ramsés Castro Molano
//Fecha: 09/09/2020

//Constantes de la hora
byte horas[] = {10, 11, 12, 13};

//Constantes de los minutos
byte minutos[] = {4, 5, 6, 7, 8, 9};

//Constantes de control
const int pulsadorModo = 3;
const int pulsadorCuenta = 2;

//Tamaños de los arreglos
int minSize = sizeof(minutos) / sizeof(byte);
int horaSize = sizeof(horas) / sizeof(byte);

//Variables globales
int valorDelay = 1000; //1 segundo
int modo = -1;
int i; //Variable de control

//Reloj
byte hora = B1100; 
byte minuto = B000000;
int segundo = 0;

void setup(){
    //Inicializamos el puerto serial
    Serial.begin(9600);
    
    //Inicializamos los botones como entradas
    pinMode(pulsadorModo, INPUT);
    pinMode(pulsadorCuenta, INPUT);
    
    //Inicializamos los leds como salidas
    for(i = 0; i < horaSize; i++){
        pinMode(horas[i], OUTPUT);
    }
    
    for(i = 0; i < minSize; i++){
        pinMode(minutos[i], OUTPUT);
    }
}

void loop(){
    Serial.print("Modo: ");
    Serial.println(modo);

    switch(modo){
        case -1: //Caso inicial, prende y apaga los leds
            for(i=0; i < horaSize; i++){
                digitalWrite(horas[i], !digitalRead(horas[i]));
            }
            for(i=0; i < minSize; i++){
                digitalWrite(minutos[i], !digitalRead(minutos[i]));
            }
            delay(valorDelay/5);
            break;
            
        case 0://Reloj
            //Mostramos la hora y los minutos
            mostrarHora(hora);
            mostrarMinutos(minuto);
            Reloj();
            Serial.print("Hora: ");
            Serial.print(hora);
            Serial.print(" Minuto: ");
            Serial.print(minuto);
            Serial.print(" Segundo: ");
            Serial.println(segundo);
            break;
        
        case 1://Editor de la Hora
            while (modo == 1){
                if(digitalRead(pulsadorCuenta) == HIGH){
                    hora++;
                    if(hora == B1101){
                        hora = B0001;
                    }
                    mostrarHora(hora);
                    segundo = 0;
                }
                if(digitalRead(pulsadorModo) == HIGH){
                    modo++;
                }
                Reloj();
            }
            break;
        
        case 2://Editor de los minutos
            while (modo == 2){
                if(digitalRead(pulsadorCuenta) == HIGH){
                    minuto++;
                    if(minuto == B111100){
                        minuto = B0000;
                    }
                    mostrarMinutos(minuto);
                    segundo = 0;
                }
                if(digitalRead(pulsadorModo) == HIGH){
                    modo=0;
                }
                Reloj();
            }
        break;
    }
    //Hacemos la lectura del botón de modo
    if(digitalRead(pulsadorModo) == HIGH){
        if (modo == 2){
            modo = 0;
        }
        else{
            modo++;
        }
        delay(valorDelay/4);
    }
}

void Reloj(){
    //Avanzan los segundos
    segundo++;
    if(segundo == 60){ //En caso de que los segundos completen una vuelta se reinician
        segundo = 0;
        minuto++;
    }
    if(minuto == B111100){ //En caso de que los minutos completen una vuelta se reinician
        minuto = 0;
        hora++;
    }
    if(hora == B1101){ //En caso de que las horas lleguen a 12 se va a 1
        hora = 1;
    }
    //Espera un segundo
    delay(valorDelay);
}

void mostrarHora(byte hora){
    for(i = 0; i < horaSize; i++){
        digitalWrite(horas[i], GetBit(hora, i));
    }
}

void mostrarMinutos(byte minuto){
  for(i = 0; i < minSize; i++){
    digitalWrite(minutos[i], GetBit(minuto, i));
    }
}

bool GetBit(byte N, int pos){  // pos = 7 6 5 4 3 2 1 0
       int b = N >> pos ;       // Shift bits
       b = b & 1 ;              // coger solo el ultimo bit
       return b ;
}
