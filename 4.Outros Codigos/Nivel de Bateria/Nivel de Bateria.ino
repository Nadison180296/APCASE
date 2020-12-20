int Pin = A0;    //Pino
float LerTensao = 0.0;   //Ler a tensao no pino
float TensaoNaBateria=0; //Tensao na bateria

const int Blue = D8;     //LED azul
const int Green = D7;    //LED verde
const int Red = D6;      //LED vermelho

void setup() {
  Serial.begin(9600);
  pinMode(Blue, OUTPUT); //Define a porta como saída
  pinMode(Green, OUTPUT);//Define a porta como saída
  pinMode(Red, OUTPUT);  //Define a porta como saída
  pinMode(Pin, INPUT);   //Define a porta como entrada
}

//Funções responsáveis por executar o brilho selecionado
void RedFuncao(){
  digitalWrite(Blue, LOW);
  digitalWrite(Green, LOW);
  digitalWrite(Red, HIGH);
}
void BlueFuncao(){
  digitalWrite(Blue, HIGH);
  digitalWrite(Green, LOW);
  digitalWrite(Red, LOW);
}
void GreenFuncao(){
  digitalWrite(Blue, LOW);
  digitalWrite(Green, HIGH);
  digitalWrite(Red, LOW);
}

void loop() {
  LerTensao = analogRead(Pin);
  TensaoNaBateria = 2*(LerTensao*(3.3/1024));
  Serial.println("Valor de input");
  Serial.println(LerTensao);
  Serial.println("Valor de tensão");
  Serial.println(TensaoNaBateria);
  delay(500);
  
  if(TensaoNaBateria <= (2.7)){RedFuncao(); Serial.println("Bateria baixa"); delay(500);}                          //Bateria baixa
  if(TensaoNaBateria > (2.7) || TensaoNaBateria < (3.3)){ BlueFuncao();Serial.println("Bateria normal");delay(500);} //Bateria normal
  if(TensaoNaBateria >= (3.3)){GreenFuncao(); Serial.println("Bateria alta");delay(500);}                          //Bateria Alta        
}
