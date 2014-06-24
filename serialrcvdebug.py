from serial import Serial
import subprocess

port = Serial("/dev/ttyAMA0",9600,timeout=2)
process = subprocess.Popen("./gpiopwm", stdin=subprocess.PIPE)
# process = subprocess.Popen("./gpiopwm", stdin=subprocess.PIPE, stdout=subprocess.PIPE)
#thrust = 01500
while True:
    line = port.readline()
#    process.stdin.write(str(thrust)+"\n")
    process.stdin.write(line)
        print line + "bytes written"
#    for output in iter(process.stdout.readline, ''):
#        print output,
