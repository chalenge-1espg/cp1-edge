# 🔦 Sensor de Luminosidade com Display Animado - HUNTER

Bem-vindo ao repositório oficial do **Sensor de Luminosidade Inteligente da HUNTER**!  
Este projeto une tecnologia, criatividade e estilo para monitorar níveis de luz em tempo real com um toque de personalidade: o logo da sua loja aparece animado no display logo ao ligar! 😎

## 💡 Sobre o Projeto

Este sensor foi desenvolvido com foco em ambientes comerciais ou pessoais onde o controle da luminosidade é essencial. Ele não só exibe os níveis de luz, mas também avisa quando estão **acima do ideal** com um **LED vermelho** e um **buzzer** sonoro — tudo de forma clara e intuitiva no **display LCD 16x2**.

🧠 Destaques:
- Animação personalizada do logo "HUNTER" na inicialização ✨  
- Monitoramento em tempo real dos níveis de luminosidade 📈  
- Alertas visuais e sonoros para luz excessiva 🚨  
- Modo de configuração de **nível mínimo** e **máximo** com **um único botão** 🎛️  

---

## 🛠️ Componentes Utilizados

| Componente            | Função                              |
|-----------------------|--------------------------------------|
| Arduino Uno           | Cérebro do projeto 🧠                |
| Sensor LDR (A0)       | Medição da luminosidade 📷          |
| Display LCD 16x2      | Exibição dos dados e animação 🖥️     |
| LED vermelho (D3)     | Alerta visual de luz alta 🔴         |
| Buzzer (D4)           | Alerta sonoro de luz alta 🔊         |
| Botão (D2)            | Entrada para configuração 🔘         |
| Resistores de 10k/220Ω| Pull-up e proteção 🔌               |

---

## 🚀 Como Funciona

### ⚙️ Inicialização
Ao ligar, o sistema exibe uma **animação do logo da HUNTER** no LCD, simulando um alvo com um "H" personalizado.

### 🌡️ Monitoramento
O sensor lê a luminosidade ambiente e exibe o valor atual no display.  
Se ultrapassar o nível configurado, o sistema:
- Acende o LED vermelho
- Emite um som com o buzzer

### 🔧 Configuração
Pressione o botão para entrar no **modo de calibração**:
1. **Configurar mínimo**: coloque o sensor no escuro e pressione o botão
2. **Configurar máximo**: exponha o sensor à luz intensa e pressione novamente

Os valores ficam ativos até desligar (ou podem ser salvos com EEPROM, se desejar).

---

## 📸 Visual do Projeto

📷 adicionar videos e fotos do projeto funcionando

---

## 📂 Estrutura do Código

- `setup()`: Inicializa os pinos e mostra a animação
- `loop()`: Faz a leitura e exibição dos níveis
- `mostrarLogoAnimado()`: Anima o logo "HUNTER" no LCD
- `configurarNiveis()`: Define os limites de luz via botão

---
