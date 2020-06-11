실행 명령어 
1. 아두이노를 연결한다. 
2. 피씨에서 아래 순으로 실행 
3. roscore 
4. rosrun rosserial_arduino serial_node.py _port:=/dev/ttyACM0
5. rosrun 패키지명 실행노드명 ( 이건 run.cpp를 빌드 시키는 패키지명에 따라 변경됨  )

주의 사항

- 아두이노 코드에 Serial.println 사용하면 로스 시리어 동작 안함. 
  따라서 전부 주석 처리했음. 

- 코드상 pulse센서 관련 코드가 없습니다. 따라서 beat_pulse 펄스는 계속 0 상태가 되서 
  따라서 사운드는 현재 코드에서 소리가 날 사황이 없을 것 같습니다.

- 실물에서 실행 시켜 보지 않았음. 따라서 실물 실행시 에러 날수 있음     

