#include <LiquidCrystal.h>

// Inicializa o LCD nos pinos: RS, E, D4, D5, D6, D7
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

// Pinos
const int ldrPin = A0;
const int ledPin = 3;
const int buzzerPin = 4;
const int botaoPin = 2;

// Níveis de luminosidade
int nivelLuminosidade = 0;
int nivelMin = 200;
int nivelMax = 800;

// Variáveis de controle de configuração
bool modoConfig = false;
int etapaConfig = 0;

// Caractere personalizado para o "H" estilizado
byte Hhunter[8] = {
  B10001,
  B10001,
  B11111,
  B10001,
  B10001,
  B10001,
  B10001,
  B00000
};

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(botaoPin, INPUT_PULLUP);

  lcd.begin(16, 2); // Inicia o display 16x2
  mostrarLogoAnimado(); // Exibe logo da HUNTER

  // ativa modo de configuração ao pressionar botão
  attachInterrupt(digitalPinToInterrupt(botaoPin), configurarNiveis, FALLING);
}

void loop() {
  if (!modoConfig) {
    nivelLuminosidade = analogRead(ldrPin); // Lê sensor

    // Exibe valor no LCD
    lcd.setCursor(0, 0);
    lcd.print("Luminosidade:     ");
    lcd.setCursor(0, 1);
    lcd.print("Nivel: ");
    lcd.print(nivelLuminosidade);
    lcd.print("     ");

    // Se passar do nível máximo, aciona LED e buzzer
    if (nivelLuminosidade > nivelMax) {
      digitalWrite(ledPin, HIGH);
      tone(buzzerPin, 1000);
    } else {
      digitalWrite(ledPin, LOW);
      noTone(buzzerPin);
    }

    delay(500);
  }
}

// Função chamada por interrupção para configurar níveis
void configurarNiveis() {
  modoConfig = true;
  etapaConfig = 1;
  lcd.clear();
  lcd.print("Config. Min...");
  delay(1000);
  lcd.clear();
  lcd.print("Lum: ");
  lcd.setCursor(0, 1);

  // Espera botão ser solto
  while (digitalRead(botaoPin) == LOW);

  // Aguarda e mostra leitura até botão ser pressionado novamente
  while (digitalRead(botaoPin) == HIGH) {
    int leitura = analogRead(ldrPin);
    lcd.setCursor(0, 1);
    lcd.print(leitura);
    lcd.print("     ");
    delay(200);
  }

  nivelMin = analogRead(ldrPin); // Salva nível mínimo
  lcd.clear();
  lcd.print("Min salvo: ");
  lcd.print(nivelMin);
  delay(1000);

  lcd.clear();
  lcd.print("Config. Max...");
  delay(1000);

  while (digitalRead(botaoPin) == LOW);

  while (digitalRead(botaoPin) == HIGH) {
    int leitura = analogRead(ldrPin);
    lcd.setCursor(0, 1);
    lcd.print(leitura);
    lcd.print("     ");
    delay(200);
  }

  nivelMax = analogRead(ldrPin); // Salva nível máximo
  lcd.clear();
  lcd.print("Max salvo: ");
  lcd.print(nivelMax);
  delay(1000);

  modoConfig = false;
  lcd.clear();
}

// Animação do logo HUNTER no LCD
void mostrarLogoAnimado() {
  lcd.clear();
  lcd.createChar(0, Hhunter);

  // Moldura estilo alvo
  lcd.setCursor(5, 0); lcd.print("-");
  lcd.setCursor(10, 0); lcd.print("-");
  lcd.setCursor(5, 1); lcd.print("|");
  lcd.setCursor(10, 1); lcd.print("|");
  delay(500);

  // "H" no centro
  lcd.setCursor(7, 0);
  lcd.write(byte(0));
  delay(500);

  // Nome da loja
  lcd.clear();
  lcd.setCursor(3, 0);
  lcd.print("HUNTER");
  delay(1000);

  lcd.clear();
}
