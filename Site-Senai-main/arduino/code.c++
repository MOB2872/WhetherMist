#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

#define RELE_PIN 3

// Define o pino 2 do arduino como o do sensor DHT22
#define DHT_PIN 2

// Define o modelo do sensor DHT
#define DHTTYPE DHT22

#define INTERVALO 5000

DHT dht(DHT_PIN, DHTTYPE);

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(9600);
   Serial.println("INICIANDO SISTEMA");
  dht.begin();
  lcd.init();
  lcd.backlight();
  lcd.setCursor(3, 0);
  lcd.print("INICIANDO");
  delay(5000);
  lcd.clear();
  pinMode(RELE_PIN, OUTPUT);
}

void loop() {

 // put your main code here, to run repeatedly:
// Cria variáveis que irão receber os dados do sensor
  float h = 0, t = 0, f = 0;
// Recebe a umidade
 delay(500);
  h = dht.readHumidity();
  // Recebe a temperatura em graus Celsius
  delay(500);
  t = dht.readTemperature();
  // Lógica para eliminar resultados indesejados
  if(isnan(h) || isnan(t) || t == 0 || h == 0){
    Serial.println(F("Falha na leitura do sensor"));
    lcd.setCursor(0, 0);
    lcd.print("Falha no sensor DHT22");
  }
  // Se estiver tudo ok com a leitura, transmite os dados via bluetooth
  else{
    // Temperatura
    Serial.print(t);
    Serial.print("ºC");
    Serial.print(",");
    lcd.setCursor(0, 1);


    // Umidade
    Serial.print(h);
    Serial.print("%");
    Serial.println();
    
    // Print na tela LCD
    lcd.clear();
    lcd.setCursor(0, 0); 
    lcd.print("Temp.: ");
    lcd.print(t);
    lcd.print("C");
    lcd.setCursor(0, 1);
    lcd.print("Umidade: ");
    lcd.print(h);
    lcd.print("%");
}
if(h < 80){
  digitalWrite(RELE_PIN, LOW);
}
else {
  digitalWrite(RELE_PIN, HIGH);
}
}