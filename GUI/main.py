from kivy.app import App
from kivy.uix.label import Label
from kivy.uix.button import Button
from kivy.properties import ObjectProperty
from kivy.uix.scrollview import ScrollView
from kivy.uix.boxlayout import BoxLayout
from kivy.uix.spinner import Spinner
from kivy.clock import Clock
from kivy_garden.graph import Graph, LinePlot

from serial.tools.list_ports import comports

import numpy as np
import serial
import time
import csv


class ColLabel(Label):
    pass

class Home (BoxLayout):
    
    com=ObjectProperty()
    conn_bt=ObjectProperty()

    st_bt=ObjectProperty()
    pr_bt=ObjectProperty()
    up_bt=ObjectProperty()

    device = False          #flag for when device is plugged in

    tog = False             #flag used to toggle text

    def ToggleText(self, *args):
        if self.tog == False:
            self.msg.text = self.msg.text + "_"
            self.tog = True
        else:
            self.msg.text = self.msg.text.replace("_","")
            self.tog = False

    def update (self, *args):                               #check if device is connected and abilitate GUI 
        ports = [port.device for port in comports()]
        if not ports:
            self.com.values = []
            self.com.text="Ports"
            self.conn_bt.disabled = True                    #disabilitate connection button if device isn't plugged in
            self.conn_bt.text = "Connect"
            if self.device == True:                         #if device is unplugged while working
                self.device = False
                self.msg.text = self.msg.text + "\n" + "[" + time.strftime('%H:%M:%S') + "] " + "Device not connected"      
                self.col.cl=(1,0,0,1)
        else:
            self.com.values = ports
            if self.com.text != "Ports":
                self.conn_bt.disabled = False

        if self.conn_bt.text == "Disconnect":
            self.st_bt.disabled = self.pr_bt.disabled = self.up_bt.disabled = False
        else:        
            self.st_bt.disabled = self.pr_bt.disabled = self.up_bt.disabled = True
            self.up_bt.text = "Change Settings"
            self.fsr.disabled = self.sf.disabled = self.esav.disabled = self.tf.disabled = True
            self.changing = False

        if self.up_bt.text == "Update":
            self.st_bt.disabled = self.pr_bt.disabled = True

    msg=ObjectProperty()

    col=ObjectProperty()

    global ser

    def Connect(self):                               #connect to serial port
        if self.conn_bt.text == "Connect":
            port_name = self.com.text
            self.ser = serial.Serial(port = port_name, baudrate = 19200)
            if self.ser.is_open:
                uart = 'h'
                uart = bytes(uart, 'utf-8')
                self.ser.write(uart)
                self.ser.flushInput()
                psoc = self.ser.readline()
                psoc = psoc.decode(errors='ignore')                             #mandatory, remember errors=ignore to avoid crash
                if psoc == "Accelerometer Hello $$$\n":                         #custom message received from PSoC
                    self.device = True
                    self.conn_bt.text = "Disconnect"
                    self.msg.text = self.msg.text + "\n" + "[" + time.strftime('%H:%M:%S') + "] " + "Connected to " + self.com.text
  
                    self.fsr.text = self.ser.readline().decode().replace('\n','')         #retrieve settings from psoc
                    self.sf.text = self.ser.readline().decode().replace('\n','')
                    self.tf.text = self.ser.readline().decode().replace('\n','')
                    self.esav.text = self.ser.readline().decode().replace('\n','')

                    if self.esav.text == 'OFF':
                        self.st_bt.text = 'Start Device'
                    else:
                        self.st_bt.text = 'Stop Device'

                    self.col.cl=(0,1,0,1)
                else:
                    self.msg.text = self.msg.text + "\n" + "[" + time.strftime('%H:%M:%S') + "] " + "Connection failed, retry "
                    self.ser.close()
            else:
                self.msg.text = self.msg.text + "\n" + "[" + time.strftime('%H:%M:%S') + "] " + "Connection failed, retry "
        else:
            self.device = False
            self.conn_bt.text = "Connect"
            self.msg.text = self.msg.text + "\n" + "[" + time.strftime('%H:%M:%S') + "] " + "Device disconnected"
            self.ser.close()
            self.x_data.remove_plot(self.plot_x)        #clear graphs
            self.y_data.remove_plot(self.plot_y)
            self.z_data.remove_plot(self.plot_z)
            self.t_data.remove_plot(self.plot_t)
            self.x_data.size_hint_x = 2
            self.y_data.size_hint_x = 2
            self.z_data.size_hint_x = 2
            self.t_data.size_hint_x = 2
            
            self.col.cl=(1,0,0,1)

    def Work(self):                                     #manage data acquisition and saving
        if self.st_bt.text == 'Start Device':
            uart = 'b'
            uart = bytes(uart, 'utf-8')
            self.ser.write(uart)
            self.st_bt.text = 'Stop Device'         
            self.esav.text = 'ON'
            self.msg.text = self.msg.text + "\n" + "[" + time.strftime('%H:%M:%S') + "] " + "Data acquisition & Saving to EEPROM started"
        else:
            uart = 's'
            uart = bytes(uart, 'utf-8')
            self.ser.write(uart)
            self.st_bt.text = 'Start Device'           
            self.esav.text = 'OFF'
            self.msg.text = self.msg.text + "\n" + "[" + time.strftime('%H:%M:%S') + "] " + "Data acquisition & Saving to EEPROM stopped"

    x_data=ObjectProperty(None)
    y_data=ObjectProperty(None)
    z_data=ObjectProperty(None)
    t_data=ObjectProperty(None)
    temp_label=ObjectProperty(None)

    plot_x=LinePlot(line_width=2, color=[1, 1, 1, 1])           #plots initialization needed
    plot_x.points = [(x, x) for x in range(5)]

    plot_y=LinePlot(line_width=2, color=[1, 1, 1, 1])
    plot_y.points = [(x, x) for x in range(5)]

    plot_z=LinePlot(line_width=2, color=[1, 1, 1, 1])
    plot_z.points = [(x, x) for x in range(5)]

    plot_t=LinePlot(line_width=2, color=[1, 1, 1, 1])
    plot_t.points = [(x, x) for x in range(5)]

    def AdjustGraph(self, grafico, abs_max, ticks):
        grafico.ymin = -abs_max-1
        grafico.ymax = abs_max+1
        grafico.y_ticks_major = ticks

    def Print(self):                                            #print data      
        acc_x = []    
        acc_y = []
        acc_z = []
        temp = []
        uart = 'v'
        uart = bytes(uart, 'utf-8')
        self.ser.write(uart)

        if self.tf.text == "Celsius":
                self.t_data.ymin = -40
                self.t_data.ymax = 40
                self.temp_label.text = "Temperature [Celsius]"
        else:
            self.t_data.ymin = -4
            self.t_data.ymax = 76
            self.temp_label.text = "Temperature [Fahrenheit]"

        FSR = int(self.fsr.text.replace('+''-','').replace('g',''))

        self.AdjustGraph(self.x_data,FSR,FSR//2)
        self.AdjustGraph(self.y_data,FSR,FSR//2)
        self.AdjustGraph(self.z_data,FSR,FSR//2)

        if FSR==2:                                
            sensitivity = 4/1000
        elif FSR==4:
            sensitivity = 8/1000
        elif FSR==8:
            sensitivity = 16/1000       
        else:
            sensitivity = 48/1000

        search_header = True
        stop = 0
        while search_header == True:                                #look for header
            header = int.from_bytes(self.ser.read(1), 'big')
            stop = stop + 1
            if header == 0xA0:
                reading = True
                search_header=False      
            if stop == 100:                                         #stop after 100 tries
                reading = False
                search_header = False
        
        no_data = 0
        data = []
        end_read = 0
        if reading == True:           
            while reading == True:            
                flag=self.ser.read(1) 
                tail = int.from_bytes(flag, 'big', signed=False)
                if tail == 0xC0:                                    #look for tail
                    end_read = end_read + 1                  
                    if end_read == 2:                               #only if 2 consecutive tail bytes are read 
                        reading = False
                    else:
                        data.append(tail)
                elif tail == 0x00:
                    no_data = no_data + 1
                    data.append(tail)
                    end_read = 0
                else:                   
                    no_data = 0
                    end_read = 0
                    data.append(tail)

        if (len(data) - no_data)>5:
            for i in range((len(data) - no_data)//6):                               #range = number of packages
                pack = bytearray(data[i*6:i*6+6])                                   #unpack 1 package of 6 bytes at a time
                z = np.uint16(pack[0] | ((pack[1] & 0x03)<<8))
                if (z&0x200):
                    z=z|0xFC00
                z=np.int16(z)
                
                y = np.uint16(((pack[1] & 0xFC)>>2) | ((pack[2] & 0x0f)<<6))
                if (y&0x200):
                    y=y|0xFC00
                y=np.int16(y)

                x = np.uint16(((pack[2] & 0xF0)>>4) | ((pack[3] & 0x3f)<<4))
                if (x&0x200):
                    x=x|0xFC00
                x=np.int16(x)

                acc_z.append(z)                                  
                acc_y.append(y)     
                acc_x.append(x)
                temp.append(np.int16(pack[4] | (pack[5]<<8))) 
                
            acc_x_w = csv.writer(open('acc_x.csv', 'w'))                            #saving in .csv files
            acc_x_w.writerow(['X AXIS ACCELERATION'])
            acc_y_w = csv.writer(open('acc_y.csv', 'w')) 
            acc_y_w.writerow(['Y AXIS ACCELERATION']) 
            acc_z_w = csv.writer(open('acc_z.csv', 'w'))
            acc_z_w.writerow(['Z AXIS ACCELERATION'])   
            temp_w = csv.writer(open('temp.csv', 'w')) 
            if self.tf.text == "Celsius":
                    temp_w.writerow(['TEMPERATURE IN °C'])
            else:
                temp_w.writerow(['TEMPERATURE IN °F'])      
            
            for i in range(len(acc_x)):                                                     #all data arrays have the same length
                acc_x_w.writerow([str((acc_x[i])*sensitivity*9.8) + ' m/s^2'])              #in .csv files acc saved in [m/s^2]
                acc_y_w.writerow([str((acc_y[i])*sensitivity*9.8) + ' m/s^2'])
                acc_z_w.writerow([str((acc_z[i])*sensitivity*9.8) + ' m/s^2'])
                if self.tf.text == "Celsius":
                    temp_w.writerow([str((temp[i]*7.62*0.00001*90)-40) +' °C'])
                    temp[i] = (temp[i]*7.62*0.00001*90)-40
                else:
                    temp_w.writerow([str((temp[i]*7.62*0.00001*90)-8) +' °F']) 
                    temp[i] = (temp[i]*7.62*0.00001*90)-8

            self.plot_x = self.PrintData(self.x_data, acc_x, self.plot_x,sensitivity)       #accs plotted in [g]
            self.plot_y = self.PrintData(self.y_data, acc_y, self.plot_y,sensitivity)
            self.plot_z = self.PrintData(self.z_data, acc_z, self.plot_z, sensitivity)
            if self.tf.text == 'Celsius':
                self.plot_t = self.PrintData(self.t_data, temp, self.plot_t,1)
            else:
                self.plot_t = self.PrintData(self.t_data, temp, self.plot_t, 1)     #°F = °C + 32

            if self.esav.text == "ON":                       #when data gets printed device gets turned OFF
                self.esav.text = "OFF"
            
            if self.st_bt.text == 'Stop Device':             #same as above
                self.st_bt.text = 'Start Device'

            self.msg.text = self.msg.text + "\n" + "[" + time.strftime('%H:%M:%S') + "] " + "Data printed & stored, device stopped"  
        else:
            self.msg.text = self.msg.text + "\n" + "[" + time.strftime('%H:%M:%S') + "] " + "No data available"  
            if self.esav.text == "ON":                                                                              #when data gets printed device gets turned OFF
                self.esav.text = "OFF"
            
            if self.st_bt.text == 'Stop Device':                                                                    #same as above
                self.st_bt.text = 'Start Device'

    def PrintData(self, data, obj, grafico, sens):
        data.remove_plot(grafico)
        grafico = LinePlot(line_width=2, color=[1, 1, 1, 1])
        grafico.points = [(x, float(obj[x])*sens) for x in range(len(obj))]
        data.add_plot(grafico)
        data.xmax=len(obj)
        data.size_hint_x = 1 + (39*len(obj)/10752)          #max lenght data = 10752, graph size adjusted
        if self.sf.text == '1Hz':
            data.x_ticks_major = 1
        elif self.sf.text == '10Hz':
            data.x_ticks_major = 10
        elif self.sf.text == '25Hz': 
            data.x_ticks_major = 25
        else:
            data.x_ticks_major = 50
        
        return grafico

    fsr=ObjectProperty()
    sf=ObjectProperty()
    esav=ObjectProperty()
    tf=ObjectProperty()

    changing = False

    def ChangeSettings(self):                                   #change settings
        if self.changing == False:
            self.changing = True
            self.up_bt.text = "Update"
            self.msg.text = self.msg.text + "\n" + "[" + time.strftime('%H:%M:%S') + "] " + "Select new settings"
            self.fsr.disabled = self.sf.disabled = self.esav.disabled = self.tf.disabled = False                    #allow settings customization

        else:
            uart = 'c'
            uart = bytes(uart, 'utf-8')
            self.ser.write(uart)
            
            FSR = self.fsr.text
            SF = self.sf.text
            TF = self.tf.text
            SAVE = self.esav.text

            if FSR=='+-2g':
                FSR=0x00
            elif FSR=='+-4g':
                FSR=0x01
            elif FSR=='+-8g':
                FSR=0x02
            else:
                FSR=0x03

            if SF=='1Hz':
                SF=0x00
            elif SF=='10Hz':
                SF=0x04
            elif SF=='25Hz':
                SF=0x08
            else:
                SF=0x0C

            if TF=='Celsius':
                TF=0x00
            else:
                TF=0x10

            if SAVE=='ON':
                SAVE=0x20
                self.st_bt.text = 'Stop Device'
            else:
                SAVE=0x00
                self.st_bt.text = 'Start Device'

            conf = FSR | SF | TF | SAVE | 0x00          #create custom byte to send to PSoC to change config. registers
            conf = bytes([conf])
            time.sleep(.1)
            self.ser.write(conf)

            self.changing = False
            self.up_bt.text = "Change Settings"
            self.msg.text = self.msg.text + "\n" + "[" + time.strftime('%H:%M:%S') + "] " + "Settings updated"
            self.fsr.disabled = self.sf.disabled = self.esav.disabled = self.tf.disabled = True
    
    def Esav_Button(self):
        if self.esav.text == 'OFF':
            self.esav.text = 'ON'
        else:
            self.esav.text = 'OFF'
    
    def Tempconf_Button(self):
        if self.tf.text == 'Fahrenheit':
            self.tf.text = 'Celsius'
        else:
            self.tf.text = 'Fahrenheit'


class GUIApp (App):
    def build(self):
        home = Home()
        Clock.schedule_interval(home.update, 0.1)           #checks ports every 0.1s
        Clock.schedule_interval(home.ToggleText, 0.4)
        return home

if __name__ == '__main__':
    app = GUIApp()
    app.run()
