import serial
import numpy as np
import matplotlib.pyplot as plt

ser = serial.Serial('/dev/cu.usbmodem14201', 9600, timeout=1)  # open serial port

print("Lese Daten ... ")

#Plot erstellen
plt.ion()
fig = plt.figure()
ax = fig.add_subplot(111, projection='polar')
ax.set_ylim(0, 400)
ax.set_xlim(0, 145*np.pi/180)

angle = 0

beam, = ax.plot([0,0], [0,400], color = "g", lw=2)

while True:
    try:
        line = ser.readline().decode("utf-8", errors="ignore").strip()

        if line and "," in line:
            parts  = line.split(",")  #creates a list of Data read from the serial port (angle and distance)
            angle_rad = np.deg2rad(int(parts[0]))  #angle in radiant
            distance = float(parts[1]) #distance in cm

            beam.set_data([angle_rad, angle_rad], [0, distance])
            plt.pause(0.0001)
    except ValueError:
        continue

    except KeyboardInterrupt:
        print("\nProgramm beendet")



