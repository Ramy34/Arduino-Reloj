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
int modo = 0; //Estado Inicial
int i; //Variable de control

//Variables del reloj
byte hora = B1100; 
byte minuto = B000000;
int segundos = 0;

void setup(){
    //Inicializamos el puerto serial
    Serial.begin(9600);
    
    //Inicializamos los leds como salidas
    for(i = 0; i < horaSize; i++){
        pinMode(horas[i], OUTPUT);
    }
    
    for(i = 0; i < minSize; i++){
        pinMode(minutos[i], OUTPUT);
    }

    //Inicialimamos el boton de modo como una interrupción
    pinMode(pulsadorCuenta, INPUT_PULLUP);
    pinMode(pulsadorModo, INPUT_PULLUP);

    attachInterrupt(digitalPinToInterrupt(pulsadorCuenta), aumentarCuenta, FALLING);
    attachInterrupt(digitalPinToInterrupt(pulsadorModo), aumentarModo, FALLING);
}

void loop(){
    Serial.print("Modo: ");
    Serial.println(modo);
    reloj();
}

//Función del reloj
void reloj(){
    //Avanzan los segundos
    segundos++;
    if(segundos == 60){ //En caso de que los segundos completen una vuelta se reinician
        segundos = 0;
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
    mostrarHora(hora);
    mostrarMinutos(minuto);
    mensajesSerial();
    delay(valorDelay);
}

//Funciones que despliegan los valores en los leds
void mostrarHora(byte hora){
    for(i = 0; i < horaSize; i++){
        digitalWrite(horas[i], getBit(hora, i));
    }
}

void mostrarMinutos(byte minuto){
  for(i = 0; i < minSize; i++){
    digitalWrite(minutos[i], getBit(minuto, i));
    }
}

//Función que nos regresa el valor de un bit
bool getBit(byte N, int pos){  // pos = 7 6 5 4 3 2 1 0
       int b = N >> pos ;       // Shift bits
       b = b & 1 ;              // coger solo el ultimo bit
       return b ;
}

//Funciones de las intrrrupciones
void aumentarModo(){
    if(modo == 2){
        modo = 0;
    }else{
        modo++;
    }
}

void aumentarCuenta(){
    switch(modo){
        case 0: //Cambiar las horas
            hora++;
            if(hora == B1101){
                hora = B0001;
            }
            mostrarHora(hora);
            mostrarMinutos(B000000);
            break;
        case 1: //Cambiar los minutos
            minuto++;
            if(minuto == B111100){
                minuto = B000000;
            }
            mostrarHora(B0000);
            mostrarMinutos(minuto);
            break;
        case 2: //Reiniciar los minutos
            segundos = 0;
            break;
        default:
            break;
    }
}

void mensajesSerial(){
    Serial.print("Hora: ");
    Serial.print(hora);
    Serial.print(" Minutos: ");
    Serial.print(minuto);
    Serial.print(" Segundos: ");
    Serial.println(segundos);
}
