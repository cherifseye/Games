import serial
import time

class SerialPort():
    def __init__(self, port, baudrate=9600):
        self.ser = serial.Serial(port, baudrate)

    def portIsOpen(self):
        return self.ser.is_open

    def openPort(self):
        if not self.portIsOpen():
            self.ser.open()

    def closePort(self):
        if self.portIsOpen():
            self.ser.close()

    def sendCommand(self, command):
        self.ser.write(command.encode())

    def readline(self, timeout=1):
        start_time = time.time()
        data = ''
        while True:
            if self.ser.in_waiting > 0:
                data += self.ser.read(self.ser.in_waiting).decode('utf-8', 'ignore')
                if '\n' in data:
                    break
            if time.time() - start_time > timeout:
                break
        return data.strip()

# Create a SerialPort object
arduino = SerialPort('/dev/ttyACM0') 