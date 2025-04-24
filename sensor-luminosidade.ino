#include <LiquidCrystal.h> // Biblioteca para controlar o display LCD

// Inicializa o LCD nos pinos: RS, E, D4, D5, D6, D7
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

// Pinos
const int ldrPin = A0;     // Pino analógico conectado ao sensor LDR
const int ledVermelho = 3; // Pino digital conectado ao LED vermelho
const int ledAmarelo = 4;  // Pino digital conectado ao LED amarelo
const int ledVerde = 5;    // Pino digital conectado ao LED verde
const int buzzerPin = 6;   // Pino digital conectado ao buzzer
const int botaoPin = 2;    // Pino digital conectado ao botão

// Níveis de luminosidade
int nivelLuminosidade = 0; // Variável para armazenar o valor lido do LDR
int nivelMin = 0;          // Valor mínimo padrão de luminosidade
int nivelMax = 800;        // Valor máximo padrão de luminosidade

// Variáveis de controle de configuração
bool modoConfig = false;   // Indica se o sistema está no modo de configuração
int etapaConfig = 0;       // Etapa atual da configuração (mínimo ou máximo)

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
  // Configura os pinos como entrada ou saída
  pinMode(ledVermelho, OUTPUT);
  pinMode(ledAmarelo, OUTPUT);
  pinMode(ledVerde, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(botaoPin, INPUT_PULLUP); // Botão com resistor pull-up interno

  // Inicializa o display LCD com 16 colunas e 2 linhas
  lcd.begin(16, 2);
  mostrarLogoAnimado(); // Exibe a animação do logo "HUNTER"

  // Configura uma interrupção para ativar o modo de configuração ao pressionar o botão
  attachInterrupt(digitalPinToInterrupt(botaoPin), configurarNiveis, FALLING);
}

void loop() {
  if (!modoConfig) { // Executa apenas se não estiver no modo de configuração
    nivelLuminosidade = analogRead(ldrPin); // Lê o valor do sensor LDR

    // Exibe o valor da luminosidade no LCD
    lcd.setCursor(0, 0);
    lcd.print("Luminosidade:     "); // Limpa a linha com espaços
    lcd.setCursor(0, 1);
    lcd.print("Nivel: ");
    lcd.print(nivelLuminosidade);
    lcd.print("     "); // Limpa o restante da linha com espaços

    // Classifica os níveis de luminosidade
    if (nivelLuminosidade < 150) {
      lcd.setCursor(4, 1);
      lcd.print("= ESCURO"); // Exibe "ESCURO" no LCD
      digitalWrite(ledPin, HIGH); // Acende o LED
      tone(buzzerPin, 1000);      // Ativa o buzzer com frequência de 1000 Hz
    } else if (nivelLuminosidade < 300) {
      lcd.setCursor(4, 1);
      lcd.print("= FRACO"); // Exibe "FRACO" no LCD
      digitalWrite(ledPin, LOW);  // Apaga o LED
      noTone(buzzerPin);          // Desativa o buzzer
    } else if (nivelLuminosidade < 450) {
      lcd.setCursor(4, 1);
      lcd.print("= MODERADO"); // Exibe "MODERADO" no LCD
      digitalWrite(ledPin, LOW);  // Apaga o LED
      noTone(buzzerPin);          // Desativa o buzzer
    } else {
      lcd.setCursor(4, 1);
      lcd.print("= FORTE"); // Exibe "FORTE" no LCD
      digitalWrite(ledPin, LOW);  // Apaga o LED
      noTone(buzzerPin);          // Desativa o buzzer
    }

    delay(500); // Aguarda 500 ms antes de atualizar novamente
  }
}

// Função chamada por interrupção para configurar os níveis de luminosidade
void configurarNiveis() {
  modoConfig = true; // Ativa o modo de configuração
  etapaConfig = 1;   // Define a etapa inicial como configuração do nível mínimo
  lcd.clear();
  lcd.print("Config. Min...");
  delay(1000);
  lcd.clear();
  lcd.print("Lum: ");
  lcd.setCursor(0, 1);

  // Aguarda o botão ser solto
  while (digitalRead(botaoPin) == LOW);

  // Lê o valor do LDR até o botão ser pressionado novamente
  while (digitalRead(botaoPin) == HIGH) {
    int leitura = analogRead(ldrPin);
    lcd.setCursor(0, 1);
    lcd.print(leitura);
    lcd.print("     ");
    delay(200);
  }

  nivelMin = analogRead(ldrPin); // Salva o nível mínimo configurado
  lcd.clear();
  lcd.print("Min salvo: ");
  lcd.print(nivelMin);
  delay(1000);

  lcd.clear();
  lcd.print("Config. Max...");
  delay(1000);

  // Aguarda o botão ser solto
  while (digitalRead(botaoPin) == LOW);

  // Lê o valor do LDR até o botão ser pressionado novamente
  while (digitalRead(botaoPin) == HIGH) {
    int leitura = analogRead(ldrPin);
    lcd.setCursor(0, 1);
    lcd.print(leitura);
    lcd.print("     ");
    delay(200);
  }

  nivelMax = analogRead(ldrPin); // Salva o nível máximo configurado
  lcd.clear();
  lcd.print("Max salvo: ");
  lcd.print(nivelMax);
  delay(1000);

  modoConfig = false; // Sai do modo de configuração
  lcd.clear();
}

// Função para ativar LEDs e buzzer
void ativarAlerta(int ledPin, bool buzzerAtivo) {
  // Desliga todos os LEDs e o buzzer antes de ativar o alerta
  digitalWrite(ledVermelho, LOW);
  digitalWrite(ledAmarelo, LOW);
  digitalWrite(ledVerde, LOW);
  digitalWrite(buzzerPin, LOW);

  // Ativa o LED correspondente
  digitalWrite(ledPin, HIGH);

  // Ativa o buzzer, se necessário
  if (buzzerAtivo) {
    tone(buzzerPin, 262, 500); // Frequência de 262 Hz (nota C4) por 500 ms
  }
}

// Animação do logo HUNTER no LCD
void mostrarLogoAnimado() {
  lcd.clear();
  lcd.createChar(0, Hhunter); // Cria o caractere personalizado "H"

  // Exibe moldura estilo alvo
  lcd.setCursor(5, 0); lcd.print("-");
  lcd.setCursor(10, 0); lcd.print("-");
  lcd.setCursor(5, 1); lcd.print("|");
  lcd.setCursor(10, 1); lcd.print("|");
  delay(500);

  // Exibe o "H" no centro
  lcd.setCursor(7, 0);
  lcd.write(byte(0)); // Escreve o caractere personalizado
  delay(500);

  // Exibe o nome "HUNTER"
  lcd.clear();
  lcd.setCursor(3, 0);
  lcd.print("HUNTER");
  delay(1000);

  lcd.clear(); // Limpa o display
}