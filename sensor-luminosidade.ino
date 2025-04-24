#include <LiquidCrystal.h> // Biblioteca para controlar o display LCD

// Inicializa o LCD nos pinos: RS, E, D4, D5, D6, D7
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

// Pinos
const int ldrPin = A0;     // Pino analógico conectado ao sensor LDR
const int ledPin = 3;      // Pino digital conectado ao LED
const int buzzerPin = 4;   // Pino digital conectado ao buzzer
const int botaoPin = 2;    // Pino digital conectado ao botão

// Níveis de luminosidade
int nivelLuminosidade = 0; // Variável para armazenar o valor lido do LDR
int nivelMin = 200;        // Valor mínimo padrão de luminosidade
int nivelMax = 800;        // Valor máximo padrão de luminosidade

// Variáveis de controle de configuração
bool modoConfig = false;   // Indica se o sistema está no modo de configuração
int etapaConfig = 0;       // Etapa atual da configuração (mínimo ou máximo)

// Caractere personalizado para o "H" estilizado
byte Hhunter[8] = {
  B10001, // Linha 1 do caractere
  B10001, // Linha 2 do caractere
  B11111, // Linha 3 do caractere
  B10001, // Linha 4 do caractere
  B10001, // Linha 5 do caractere
  B10001, // Linha 6 do caractere
  B10001, // Linha 7 do caractere
  B00000  // Linha 8 do caractere
};

void setup() {
  // Configura os pinos como entrada ou saída
  pinMode(ledPin, OUTPUT);
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

    // Verifica se o nível de luminosidade excede o máximo permitido
    if (nivelLuminosidade > nivelMax) {
      digitalWrite(ledPin, HIGH); // Acende o LED
      tone(buzzerPin, 1000);      // Ativa o buzzer com frequência de 1000 Hz
    } else {
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
  lcd.print("Config. Min..."); // Exibe mensagem de configuração do mínimo
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
    lcd.print("     "); // Limpa o restante da linha com espaços
    delay(200);
  }

  nivelMin = analogRead(ldrPin); // Salva o nível mínimo configurado
  lcd.clear();
  lcd.print("Min salvo: ");
  lcd.print(nivelMin);
  delay(1000);

  lcd.clear();
  lcd.print("Config. Max..."); // Exibe mensagem de configuração do máximo
  delay(1000);

  // Aguarda o botão ser solto
  while (digitalRead(botaoPin) == LOW);

  // Lê o valor do LDR até o botão ser pressionado novamente
  while (digitalRead(botaoPin) == HIGH) {
    int leitura = analogRead(ldrPin);
    lcd.setCursor(0, 1);
    lcd.print(leitura);
    lcd.print("     "); // Limpa o restante da linha com espaços
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
