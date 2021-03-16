int button_state;

void setup() {
  // put your setup code here, to run once:
  pinMode(7, INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  button_state = digitalRead(7);
  Serial.println(button_state);
}
