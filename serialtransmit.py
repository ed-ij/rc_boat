from serial import Serial
import subprocess

subp = subprocess.Popen("./jscode",stdout=subprocess.PIPE)
port = Serial("/dev/ttyAMA0",9600,timeout=2)

while True:
    for line in iter(subp.stdout.readline, ''):
        port.write(line),
        print line,

subp.close
