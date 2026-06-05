# 🕒 Reloj Binario con Arduino

Un proyecto de electrónica y programación diseñado para representar la hora de forma visual mediante un sistema binario utilizando LEDs.

## 🎯 Objetivo
Repasar, aprender y consolidar conceptos de programación en C++ para Arduino y electrónica básica mediante el desarrollo de un reloj binario interactivo.

## 🛠️ Materiales Necesarios
*   **1x** Placa Arduino Uno.
*   **10x** LEDs (colores a elección para identificar horas y minutos).
*   **10x** Resistencias de 150 ohms (para los LEDs).
*   **2x** Resistencias de 10k ohms (resistencias pull-up/pull-down para los botones).
*   **2x** Push buttons (pulsadores).
*   **1x** Cable de alimentación de 12 volts o fuente externa.
*   Cables jumper y Protoboard.

## 📋 Prerrequisitos
*   Tener instalado el [Arduino IDE](https://www.arduino.cc/en/software).
*   Conocimientos básicos de programación.
*   Nociones básicas de electrónica.

## 💡 Planteamiento del Proyecto
El proyecto se fundamenta en los siguientes puntos clave:
1.  **Visualización:** Crear un programa que procese el tiempo y lo muestre en formato binario encendiendo y apagando los LEDs correspondientes.
2.  **Interactividad:** Permitir al usuario modificar la hora por defecto y establecer la hora actual.
3.  **Optimización:** Utilizar las **interrupciones** de Arduino (a través de los *push buttons*) para modificar los valores de forma inmediata sin bloquear el bucle principal.

## 🚀 Instalación y Uso
1. Clona o descarga los archivos de este proyecto.
2. Abre el archivo principal `.ino` en el Arduino IDE.
3. Realiza las conexiones de los LEDs y botones según los pines definidos en el código.
4. Conecta el Arduino Uno a tu computadora, compila y sube el código a la placa.
5. Usa los botones para configurar la hora deseada.

## 📌 Historial de Versiones
*   **[v2.0]** (2021-09-11) - ✨ *Release final.* Se completa el objetivo del proyecto; la modificación de la hora y los minutos funciona de manera perfecta.
*   **[v1.0]** (2021-09-09) - 🛠️ *Release inicial.* El proyecto es funcional, pero presenta detalles a mejorar con respecto a la modificación de la hora y los minutos.
