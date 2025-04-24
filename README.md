# 🔦 Projeto: Sistema de Monitoramento de Luminosidade – Hunter

Este projeto desenvolvido com **Arduino** permite monitorar a luminosidade ambiente usando um **sensor LDR**, exibindo os dados em um **display LCD 16x2** e acionando alertas visuais (LED) e sonoros (buzzer) quando a luminosidade ultrapassa um nível definido.

Além disso, inclui uma **animação personalizada com o logo da loja Hunter**, deixando o sistema mais profissional e com identidade visual.

---

## 🎯 Funcionalidades

- 📟 Exibição da luminosidade atual no display LCD
- 🚨 Alerta com LED e buzzer em ambientes muito claros
- 🔧 Valor de limite de luminosidade configurável no código
- 🎬 Animação de inicialização com logo e nome **Hunter**
- 🎯 Logo com mira estilizada e digitação letra por letra

---

## 🧰 Componentes Utilizados

| Componente        | Quantidade |
|-------------------|------------|
| Arduino Uno       | 1          |
| Display LCD 16x2  | 1          |
| Sensor LDR        | 1          |
| LED Vermelho      | 1          |
| Buzzer Piezo      | 1          |
| Resistores (10kΩ para LDR) | 1 |
| Jumpers           | Diversos   |
| Protoboard        | 1          |

---

## 🔌 Conexões

### LCD (modo 4 bits):
| Pino LCD | Pino Arduino |
|----------|--------------|
| RS       | 13           |
| E        | 12           |
| D4       | 11           |
| D5       | 10           |
| D6       | 7            |
| D7       | 6            |

### Outros:
| Componente | Pino Arduino |
|------------|--------------|
| LDR        | A0           |
| LED        | 2            |
| Buzzer     | 3            |

---

## 🔧 Como Usar

1. Monte o circuito conforme a tabela acima.
2. Faça upload do código `.ino` para o Arduino.
3. O sistema exibirá uma animação do logo **Hunter**, seguido pela exibição da luminosidade.
4. Caso a luminosidade ultrapasse o valor de `maxLum`, o alerta será ativado.

---

## 📸 Imagens do projeto

- 🛠 Montagem no Simulador Tinkercad  
  <img src="https://github.com/user-attachments/assets/0be29d4e-0fd8-483b-b33e-7d8caf12da3e" width="400"/>

- 💡 Display mostrando a luminosidade  
  <img src="https://github.com/user-attachments/assets/76359950-1ee8-4b41-b152-465aff634ca5" width="400"/>



## ⚙️ Personalização

- Para ajustar o limite de luminosidade, altere a variável:

```cpp
const int maxLum = 590;
