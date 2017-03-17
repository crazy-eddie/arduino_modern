
generate_arduino_firmware(standard
    SRCS standard.cpp
    PORT  /dev/ttyACM0
    SERIAL picocom @SERIAL_PORT@ -b 9600 -l
    BOARD uno)
