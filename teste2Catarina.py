import serial
import time

# Define the serial port and baud rate
arduino_serial_port = 'COM5'  # Replace 'COMx' with your Arduino's serial port
baud_rate = 9600

ser = serial.Serial(arduino_serial_port, baud_rate)
time.sleep(2)  # Allow some time for the serial connection to establish

def receive_data():
    # Read data from the Arduino
    data = ser.readline().decode('utf-8').rstrip()
    return data

def process_data(data):
    # Process and print the received data
    print(f"Received data from Arduino: {data}")
    # Add more processing logic here if needed

def send_command(command):
    # Send a command to the Arduino
    ser.write(command.encode())

# Main program execution
try:
    # Example: Sending a command to toggle an LED on the Arduino
    send_command("TOGGLE_LED")

    while True:
        if ser.in_waiting >= 17:
            sensor_data = receive_data()
            process_data(sensor_data)
        time.sleep(0.2)  # Adjust sleep time as needed

except KeyboardInterrupt:
    ser.close()
