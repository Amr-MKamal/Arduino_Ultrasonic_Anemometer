python3 /home/pi/grabserial/grabserial -d /dev/ttyACM0 -b 9600  -o /home/pi/serialtest.json  -e  120
curl -H "Content-Type: application/json" -X POST -d "@/home/pi/serialtest.json"  https://farmtopia.farmos.net/farm/sensor/listener/a7a5d8b103e51b03d17cdf70f584ebdf?private_key=6396c8023faf3501d945fea28098442b --verbose
