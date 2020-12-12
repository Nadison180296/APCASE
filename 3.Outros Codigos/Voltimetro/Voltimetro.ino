int Pin = 36;    //Pino
float LerTensao = 0;   //Ler a tensao no pino
float TensaoNaBateria=0; //Tensao na bateria


void setup() {
  Serial.begin(115200);
  pinMode(Pin, INPUT);   //Define a porta como entrada
}



void loop() {
  LerTensao = analogRead(Pin);
  TensaoNaBateria = (LerTensao*2*(4.0/4096));
  Serial.println("Valor de input");
  Serial.println(LerTensao);
  Serial.println("Valor de tensão");
  Serial.println(TensaoNaBateria);
  delay(1000);
}
