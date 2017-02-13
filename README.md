# SUMMARY
Just a modified script of Kripthor's ESP8266-WifiBeaconJam to send words as SSIDs.
https://github.com/kripthor/WiFiBeaconJam/blob/master/WiFiBeaconJam.ino

# Description
This project is a modified version from kripthor's WifiBeaconJam. I extended the SSID length to 14 Characters. The script takes the words from line 13. The words must have a max length of 10 characters. The result depends on the used devices and their wifi. Change line 13 and 41 to change the amount of words. Respect the laws of your country!

Use http://arduino.esp8266.com/versions/2.1.0-rc2/package_esp8266com_index.json.
Newer Versions does not support "wifi_send_pkt_freedom" anymore.

![alt tag](https://github.com/H-LK/ESP8266-SSID-Text-Broadcast/blob/master/SSIDs.png)
