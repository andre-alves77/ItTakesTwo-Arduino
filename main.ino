// Definições dos pinos corretos para NodeMCU 1.0 (ESP8266)
int in_amarelo = 5; // D1
int in_azul = 4; // D2
int in_cinza = 14; // D5
int in_ciano = 12; // D6

int out_amarelo = 16; // D0
int out_azul = 0; // D3
int out_cinza = 2; // D4
int out_ciano = 13; // D7

int outs[4] = {out_amarelo, out_azul, out_cinza, out_ciano}; // Pinos de saída
int ordem[4] = {in_amarelo, in_azul, in_cinza, in_ciano}; // Pinos de entrada

void sortear() {
  randomSeed(analogRead(A0)); // Inicializa a geração de números aleatórios
  for(int i = 3; i > 0; i--) {
    int randomm = random(i + 1); // Gera um número aleatório entre 1 e i
    int temp = ordem[i]; // Salva o valor atual
    ordem[i] = ordem[randomm]; // Troca o valor com o aleatório
    ordem[randomm] = temp; // Restaura o valor salvo
  }
}

void setup() {
  Serial.begin(112500); // Inicia a comunicação serial

  // Configura os pinos de saída como saída
  for (int x = 0; x <= 3; x++) {
    pinMode(outs[x], OUTPUT);
    pinMode(ordem[x], INPUT);
  }

  sortear(); // Embaralha a ordem dos pinos de entrada
}

void loop() {
  if (Serial.available() > 0 && Serial.read() == 'p') { // Verifica se há dados disponíveis e se o caractere é 'a'
    int acertos = 0;
    for (int i = 0; i <= 3; i++) {
      digitalWrite(outs[i], HIGH); // Ativa o pino de saída
      int x = digitalRead(ordem[i]); // Lê o valor do pino de entrada
      Serial.print("Valor lido no pino ");
      Serial.print(ordem[i]);
      Serial.print(": ");
      Serial.println(x? "ativo" : "inativo"); // Imprime se o pino está ativo (1) ou inativo (0)

      if (x == 1) {
        acertos++; // Conta um acerto se o pino estiver ativo
      }

      digitalWrite(outs[i], LOW); // Desativa o pino de saída
    }
    Serial.print("Acertos: "); Serial.println(acertos); // Imprime o número total de acertos
  }
}
