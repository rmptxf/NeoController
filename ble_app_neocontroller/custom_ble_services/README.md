This is the **ble_nps.c** and the **ble_nps.c** files for the custom ble service I designed to communicate to the nRF52 SOC for driving the neopixel.

The **nps** (neo pixel) ble service has one characteristic which is the **command char**, it's the one used to send control data to the nRF52 SOC. 

The command char has one property enabled which is the **Write** property, so the mobile app can write to it.
The command char data size is set to **3**, this is due to that the mobile app just sends the the RGB data (r,g,b). The data size is also set to 1 byte, as the RGB max values is 1 byte.
