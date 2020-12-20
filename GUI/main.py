from kivy.app import App
from kivy.uix.label import Label
from kivy.uix.button import Button
from kivy.properties import ObjectProperty
from kivy.uix.scrollview import ScrollView
from kivy.uix.boxlayout import BoxLayout
from kivy.uix.spinner import Spinner
from kivy.properties import ListProperty
from kivy.clock import Clock
from kivy.uix.togglebutton import ToggleButton

import serial
from serial.tools.list_ports import comports

from kivy_garden.graph import Graph, LinePlot

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

    device = False

    tog = False
    def ToggleText(self, *args):
        if self.tog == False:
            self.msg.text = self.msg.text + "_"
            self.tog = True
        else:
            self.msg.text = self.msg.text.replace("_","")
            self.tog = False

    def update (self, *args):                           #check if device is connected and abilitate GUI
        
        ports = [port.device for port in comports()]
        if not ports:
            self.com.values = []
            self.com.text="Ports"
            self.conn_bt.disabled = True
            self.conn_bt.text = "Connect"
            if self.device == True:
                self.device = False
                self.msg.text = self.msg.text + "\n" + "[" + time.strftime('%H:%M:%S') + "] " + "Device not connected"
                self.col.cl=(1,0,0,1)
        else:
            self.com.values = ports
            if self.com.text != "Ports":
                self.conn_bt.disabled = False

        if self.conn_bt.text == "Disconnect":
            self.st_bt.disabled=False
            self.pr_bt.disabled=False
            self.up_bt.disabled=False          
        else:        
            self.st_bt.disabled=True
            self.pr_bt.disabled=True
            self.up_bt.disabled=True
            self.up_bt.text="Change Settings"
            self.fsr.disabled = True
            self.sf.disabled = True
            self.esav.disabled = True
            self.tf.disabled = True
            self.changing = False

        if self.up_bt.text == "Update":
            self.st_bt.disabled= True
            self.pr_bt.disabled= True

    msg=ObjectProperty()

    col=ObjectProperty()

    global ser

    def Connect(self):                               #connect to serial port
        if self.conn_bt.text == "Connect":
            port_name = self.com.text
            self.ser = serial.Serial(port = port_name, baudrate = 38400)
            if self.ser.is_open:
                uart = 'h'
                uart = bytes(uart, 'utf-8')
                self.ser.write(uart)
                self.ser.flushInput()
                psoc = self.ser.readline()
                psoc = psoc.decode(errors='ignore')            #mandatory, remember errors=ignore to avoid crash
                if psoc == "Accelerometer Hello $$$\n": 
                    self.device = True
                    self.conn_bt.text = "Disconnect"
                    self.msg.text = self.msg.text + "\n" + "[" + time.strftime('%H:%M:%S') + "] " + "Connected to " + self.com.text
  
                    self.fsr.text = self.ser.readline().decode().replace('\n','')         #retrieve settings from psoc
                    self.sf.text = self.ser.readline().decode().replace('\n','')
                    self.tf.text = self.ser.readline().decode().replace('\n','')
                    self.esav.text = self.ser.readline().decode().replace('\n','')

                    if self.sf.text == 'OFF':
                        self.st_bt.text = 'Start'
                    else:
                        self.st_bt.text = 'Stop'

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
            self.x_data.remove_plot(self.plot_x)
            self.y_data.remove_plot(self.plot_y)
            self.z_data.remove_plot(self.plot_z)
            self.t_data.remove_plot(self.plot_t)
            self.x_data.size_hint_x = 2
            self.y_data.size_hint_x = 2
            self.z_data.size_hint_x = 2
            self.t_data.size_hint_x = 2
            self.col.cl=(1,0,0,1)

    def Work(self):                             #manage data acquisition and saving
        if self.st_bt.text == "Start":
            self.st_bt.text = "Stop"
            self.esav.text = "ON"
            uart = 'b'
            uart = bytes(uart, 'utf-8')
            self.ser.write(uart)
            self.msg.text = self.msg.text + "\n" + "[" + time.strftime('%H:%M:%S') + "] " + "Data acquisition & Saving to EEPROM started"
        else:
            self.st_bt.text = "Start"
            self.esav.text = "0FF"
            uart = 's'
            uart = bytes(uart, 'utf-8')
            self.ser.write(uart)
            self.msg.text = self.msg.text + "\n" + "[" + time.strftime('%H:%M:%S') + "] " + "Data acquisition & Saving to EEPROM stopped"

    x_data=ObjectProperty(None)
    y_data=ObjectProperty(None)
    z_data=ObjectProperty(None)
    t_data=ObjectProperty(None)

    plot_x=LinePlot(line_width=2, color=[1, 1, 1, 1])           #plots initialization needed
    plot_x.points = [(x, x) for x in range(5)]

    plot_y=LinePlot(line_width=2, color=[1, 1, 1, 1])
    plot_y.points = [(x, x) for x in range(5)]

    plot_z=LinePlot(line_width=2, color=[1, 1, 1, 1])
    plot_z.points = [(x, x) for x in range(5)]

    plot_t=LinePlot(line_width=2, color=[1, 1, 1, 1])
    plot_t.points = [(x, x) for x in range(5)]

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
        else:
            self.t_data.ymin = -4
            self.t_data.ymax = 76

        FSR = self.fsr.text

        if FSR=='+-2g':                                 #adjust graph scale and self.sensitivity on FSR
            sensitivity = 4/1000
            self.x_data.ymin=-2-1
            self.x_data.ymax=2+1
            self.x_data.y_ticks_major= 1
            self.z_data.ymin=-2-1
            self.z_data.ymax=2+1
            self.z_data.y_ticks_major= 1
            self.y_data.ymin=-2-1
            self.y_data.ymax=2+1
            self.y_data.y_ticks_major= 1
        elif FSR=='+-4g':
            sensitivity = 8/1000
            self.z_data.ymin=-4-1
            self.z_data.ymax=4+1
            self.z_data.y_ticks_major= 2
            self.x_data.ymin=-4-1
            self.x_data.ymax=4+1
            self.x_data.y_ticks_major= 2
            self.y_data.ymin=-4-1
            self.y_data.ymax=4+1
            self.y_data.y_ticks_major= 2
        elif FSR=='+-8g':
            sensitivity = 16/1000
            self.x_data.ymin=-8-1
            self.x_data.ymax=8+1
            self.x_data.y_ticks_major= 2
            self.z_data.ymin=-8-1
            self.z_data.ymax=8+1
            self.z_data.y_ticks_major= 2
            self.y_data.ymin=-8-1
            self.y_data.ymax=8+1
            self.y_data.y_ticks_major= 2              
        else:
            sensitivity = 48/1000
            self.x_data.ymin=-16-1
            self.x_data.ymax=16+1
            self.x_data.y_ticks_major= 4
            self.y_data.ymin=-16-1
            self.y_data.ymax=16+1
            self.y_data.y_ticks_major= 4
            self.z_data.ymin=-16-1
            self.z_data.ymax=16+1
            self.z_data.y_ticks_major= 4

        search_header = True

        while search_header == True:
            header = int.from_bytes(self.ser.read(1), 'big')
            if header == 0xA0:
                search_header=False      
                    
        reading = True
        data = []
        while reading == True:            
            flag=self.ser.read(1) 
            tail = int.from_bytes(flag, 'big')
            if tail == 0xC0:
                reading = False
            else:
                data.append(tail)
        if len(data)>5:
            for i in range(len(data)//6):                                           #range = number of packages
                pack = bytearray(data[i*6:i*6+6])                                   #reads 1 package of 6 bytes at a time
                acc_x.append(pack[0] | ((pack[1] & 0x03)<<8))                       #first 2 bytes for x acc (10 bits)           
                acc_y.append(((pack[1] & 0xFC)>>2) | ((pack[2] & 0x0f)<<6))     
                acc_z.append(((pack[2] & 0xFC)>>2) | ((pack[3] & 0x0f)<<6))
                temp.append(pack[4] | (pack[5]<<8)) 

            acc_x_w = csv.writer(open('acc_x.csv', 'w')) 
            acc_y_w = csv.writer(open('acc_y.csv', 'w'))  
            acc_z_w = csv.writer(open('acc_z.csv', 'w'))   
            temp_w = csv.writer(open('temp.csv', 'w'))       
            
            for i in range(len(acc_x)):                                             #all data arrays have the same length
                acc_x_w.writerow([(acc_x[i]-512)*sensitivity*9.8])              #in .csv files acc saved in [m/s^2]
                acc_y_w.writerow([(acc_y[i]-512)*sensitivity*9.8])
                acc_z_w.writerow([(acc_z[i]-512)*sensitivity*9.8])
                if self.tf.text == "Celsius":
                    temp_w.writerow([temp[i]-32768])
                else:
                    temp_w.writerow([temp[i]-32768+32]) 

            self.plot_x = self.PrintData(self.x_data, acc_x, self.plot_x,512,sensitivity)       #accs plotted in [g]

            self.plot_y = self.PrintData(self.y_data, acc_y, self.plot_y,512,sensitivity)
    
            self.plot_z = self.PrintData(self.z_data, acc_z, self.plot_z,512, sensitivity)

            if self.tf.text == 'Celsius':
                self.plot_t = self.PrintData(self.t_data, temp, self.plot_t, 32768,1)
            else:
                self.plot_t = self.PrintData(self.t_data, temp, self.plot_t, 32736, 1)     #°F = °C + 32

            if self.esav.text == "ON":
                self.esav.text = "OFF"
            
            if self.st_bt.text == "Stop":
                self.st_bt.text = "Start"
            self.msg.text = self.msg.text + "\n" + "[" + time.strftime('%H:%M:%S') + "] " + "Data printed & stored"    
        else:
            self.msg.text = self.msg.text + "\n" + "[" + time.strftime('%H:%M:%S') + "] " + "No data available"  

    def PrintData(self, data, obj, grafico, scaling, sens):
        data.remove_plot(grafico)
        grafico = LinePlot(line_width=2, color=[1, 1, 1, 1])
        grafico.points = [(x, float(obj[x]-scaling)*sens) for x in range(len(obj))]
        data.add_plot(grafico)
        data.xmax=len(obj)
        data.size_hint_x=len(obj)//25
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
            self.fsr.disabled = False
            self.sf.disabled = False
            self.esav.disabled = False
            self.tf.disabled = False

        else:
            uart = 'c'
            uart = bytes(uart, 'utf-8')
            self.ser.write(uart)

            FSR = self.fsr.text
            SF = self.sf.text
            TF = self.tf.text
            SAVE = self.esav.text

            if FSR=='+-2g':
                FSR='00'
            elif FSR=='+-4g':
                FSR='01'
            elif FSR=='+-8g':
                FSR='10'
            else:
                FSR='11'
        
            if SF=='1Hz':
                SF='00'
            elif SF=='10Hz':
                SF='01'
            elif SF=='25Hz':
                SF='10'
            else:
                SF='11'

            if TF=='Celsius':
                TF='0'
            else:
                TF='1'

            if SAVE=='ON':
                SAVE='1'
                self.st_bt.text = "Stop"
            else:
                SAVE='0'
                self.st_bt.text = "Start"

            conf=int('00'+ SAVE + TF + SF + FSR, 2)
            conf= conf.to_bytes(1, 'big')
            self.ser.write(conf)
            self.ser.close()
            self.ser.open()

            self.changing = False
            self.up_bt.text = "Change settings"
            self.msg.text = self.msg.text + "\n" + "[" + time.strftime('%H:%M:%S') + "] " + "Settings updated"
            self.fsr.disabled = True
            self.sf.disabled = True
            self.esav.disabled = True
            self.tf.disabled = True
    
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
        Clock.schedule_interval(home.update, 0.1)  #check ports every 0.1s
        Clock.schedule_interval(home.ToggleText, 0.4)
        return home

if __name__ == '__main__':
    app = GUIApp()
    app.run()
