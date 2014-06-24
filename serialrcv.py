from serial import Serial
import subprocess

port = Serial("/dev/ttyAMA0",9600,timeout=2)
process = subprocess.Popen("./gpiopwm", stdin=subprocess.PIPE)

while True:
    line = port.readline()
    process.stdin.write(line)
        print line + "bytes written"
        
