#include <LiquidCrystal.h>

// LCD nos pinos: RS, E, D4, D5, D6, D7
LiquidCrystal lcd(13, 12, 11, 10, 7, 6, 5);

// Pinos
const int ldrPin = A0;
const int ledPin = 2;
const int buzzerPin = 3;

// Limite de luminosidade (valor invertido)
const int maxLum = 700;

// Caracteres personalizados para o logo (mira)
byte miraCentro[8] = {
  B00000,
  B00100,
  B00100,
  B11111,
  B00100,
  B00100,
  B00000,
  B00000
};

byte miraBorda[8] = {
  B00000,
  B01110,
  B01010,
  B10001,
  B01010,
  B01110,
  B00000,
  B00000
};

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

  lcd.begin(16, 2);

  // Cria os caracteres personalizados
  lcd.createChar(0, miraCentro);
  lcd.createChar(1, miraBorda);

  // Mostra a mira
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.write(byte(1)); // Borda da mira
  lcd.write(byte(0)); // Centro da mira

  // Animação do nome HUNTER aparecendo letra por letra
  String nome = " HUNTER";
  for (int i = 0; i < nome.length(); i++) {
    lcd.print(nome[i]);
    delay(200); // atraso entre letras
  }

  // Linha de baixo: CARREGANDO... com efeito
  lcd.setCursor(0, 1);
  String loading = "CARREGANDO...";
  for (int i = 0; i < loading.length(); i++) {
    lcd.print(loading[i]);
    delay(100);
  }

  delay(1000);
  lcd.clear();
}

void loop() {
  // Inverter leitura do LDR
  int lum = 1150 - analogRead(ldrPin);

  // Mostrar leitura no LCD
  lcd.setCursor(0, 0);
  lcd.print("Lum: ");
  lcd.print(lum);
  lcd.print("    ");

  lcd.setCursor(0, 1);
  lcd.print("Max: ");
  lcd.print(maxLum);

  // Aciona alerta se passar do limite
  if (lum > maxLum) {
    digitalWrite(ledPin, HIGH);
    digitalWrite(buzzerPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
    digitalWrite(buzzerPin, LOW);
  }

  delay(200);
}
