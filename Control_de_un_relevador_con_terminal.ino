#include <freertos/FreeRTOS.h>
#include <freertos/task.h>


TaskHandle_t SerialTask;

void SerialReadTask(void *pvParameters) {
  (void) pvParameters;
  String input;
  pinMode(15, OUTPUT);
  pinMode(18, OUTPUT);
  pinMode(19, OUTPUT);
  digitalWrite(15, HIGH);
  digitalWrite(18, LOW);
  digitalWrite(19, LOW);
  Serial.println("Listo para recibir comandos");

  while (true) {
        digitalWrite(19, HIGH); // Se establece el pin 15 en HIGH en cada iteración del bucle
    if (Serial.available() > 0) {
      input = Serial.readStringUntil('\n');
      input.trim();

      if (input == "ON" || input == "on") {
        digitalWrite(15, HIGH);
        digitalWrite(18, HIGH);
        digitalWrite(19, HIGH);
        Serial.print("HUB USB ENCENDIDO\n");
        vTaskDelay(100 / portTICK_PERIOD_MS); // Retraso de 1000 milisegundos
         
      } else if (input == "OFF" || input == "off") {
        digitalWrite(15, LOW);
        digitalWrite(18, LOW);
        digitalWrite(19, LOW);
        Serial.println("HUB USB APAGADO\n");
        vTaskDelay(1000 / portTICK_PERIOD_MS); // Retraso de 100 milisegundos

      } else if (input == "REINICIO" || input == "reinicio") {
        digitalWrite(15, LOW);
        digitalWrite(18, LOW);
        digitalWrite(19, LOW);
        Serial.println("HUB USB REINICIANDO\n");
        vTaskDelay(5000 / portTICK_PERIOD_MS); // Retraso de 5000 milisegundos
        digitalWrite(15, HIGH);
        digitalWrite(18, HIGH);
        digitalWrite(19, HIGH);
        Serial.println("HUB USB ENCENDIDO\n");
        vTaskDelay(100 / portTICK_PERIOD_MS); // Retraso de 10 milisegundos
      } else {
        Serial.println("Comando no reconocido");
      }
    }
    vTaskDelay(10 / portTICK_PERIOD_MS); // Retraso de 10 milisegundos
  }
}


void setup() {
  Serial.begin(115200);
  while (!Serial) {} // Espera a que se establezca la conexión serial
   
  xTaskCreate(SerialReadTask, "SerialReadTask", 2048, NULL, 1, &SerialTask);
}

void loop() {
  // No es necesario implementar loop() en un programa con FreeRTOS
}
