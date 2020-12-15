from kivy.app import App
from kivy.uix.widget import Widget
from kivy.uix.label import Label
from kivy.uix.button import Button
from kivy.properties import ObjectProperty
from kivy.uix.scrollview import ScrollView
from kivy.uix.textinput import TextInput
from kivy.uix.boxlayout import BoxLayout
from kivy.uix.spinner import Spinner
from kivy.properties import ListProperty
from kivy.properties import StringProperty
from kivy.clock import Clock

import serial
from serial.tools.list_ports import comports

from kivy_garden.graph import Graph, LinePlot

import time

import csv


class Home (BoxLayout):
    
    com=ObjectProperty()
    conn_bt=ObjectProperty()

    st_bt=ObjectProperty()
    pr_bt=ObjectProperty()
    up_bt=ObjectProperty()

    device = False

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
                    #+ self.readline() to retrieve config. settings
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

    def Work(self):                             #manage data acquisition and saving
        if self.st_bt.text == "Start":
            self.st_bt.text = "Stop"
            self.msg.text = self.msg.text + "\n" + "[" + time.strftime('%H:%M:%S') + "] " + "Data acquisition & Saving to EEPROM started"
        else:
            self.st_bt.text = "Start"
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
        self.msg.text = self.msg.text + "\n" + "[" + time.strftime('%H:%M:%S') + "] " + "Printing data"
        acc_x = []    
        acc_y = []
        acc_z = []
        temp = []
        uart = 'v'
        uart = bytes(uart, 'utf-8')
        self.ser.write(uart)

        size = int.from_bytes(self.ser.read(1), 'big')            #get size of data array

        data = self.ser.read(size)                                #get data array
        #self.ser.close()
        #self.ser.open()
        for i in range(len(data)//6):                                       #range = number of packages
            pack = data[i*6:i*6+6]                                          #reads 1 package of 6 bytes at a time
            acc_x.append(pack[0] | ((pack[1] & 0x03)<<8))                   #first 2 bytes for x acc (10 bits)           
            acc_y.append(((pack[1] & 0xFC)>>2) | ((pack[2] & 0x0f)<<6))     
            acc_z.append(((pack[2] & 0xFC)>>2) | ((pack[3] & 0x0f)<<6))
            temp.append(pack[4] | pack[5]<<8) 

        acc_x_w =csv.writer(open('acc_x.csv', 'w'), delimiter=',') 
        acc_y_w =csv.writer(open('acc_y.csv', 'w'), delimiter=',')  
        acc_z_w =csv.writer(open('acc_z.csv', 'w'), delimiter=',')   
        temp_w =csv.writer(open('temp.csv', 'w'), delimiter=',')       
        
        for i in range(len(acc_x)):
            acc_x_w.writerow([float(acc_x[i])/100])
            acc_y_w.writerow([float(acc_y[i])/100])
            acc_z_w.writerow([float(acc_z[i])/100])
            if self.tf.text == "Celsius":
                temp_w.writerow([float(temp[i])/100])
            else:
                temp_w.writerow([(float(temp[i])/100)+32])

        FSR = self.fsr.text

        if FSR=='+-2g':                                 #adjust graph scale on FSR
            self.x_data.ymin=-2
            self.x_data.ymax=2
            self.x_data.y_ticks_major= 1
            self.z_data.ymin=-2
            self.z_data.ymax=2
            self.z_data.y_ticks_major= 1
            self.y_data.ymin=-2
            self.y_data.ymax=2
            self.y_data.y_ticks_major= 1
        elif FSR=='+-4g':
            self.z_data.ymin=-4
            self.z_data.ymax=4
            self.z_data.y_ticks_major= 2
            self.x_data.ymin=-4
            self.x_data.ymax=4
            self.x_data.y_ticks_major= 2
            self.y_data.ymin=-4
            self.y_data.ymax=4
            self.y_data.y_ticks_major= 2
        elif FSR=='+-8g':
            self.x_data.ymin=-8
            self.x_data.ymax=8
            self.x_data.y_ticks_major= 2
            self.z_data.ymin=-8
            self.z_data.ymax=8
            self.z_data.y_ticks_major= 2
            self.y_data.ymin=-8
            self.y_data.ymax=8
            self.y_data.y_ticks_major= 2              
        else:
            self.x_data.ymin=-16
            self.x_data.ymax=16
            self.x_data.y_ticks_major= 4
            self.y_data.ymin=-16
            self.y_data.ymax=16
            self.y_data.y_ticks_major= 4
            self.z_data.ymin=-16
            self.z_data.ymax=16
            self.z_data.y_ticks_major= 4

        self.x_data.remove_plot(self.plot_x)
        self.first = True                                                           #plot data
        self.plot_x = LinePlot(line_width=2, color=[1, 1, 1, 1])
        self.plot_x.points = [(x, float(acc_x[x])/100) for x in range(len(acc_x))]
        self.x_data.add_plot(self.plot_x)
        self.x_data.xmax=len(acc_x)     

        self.y_data.remove_plot(self.plot_y)
        self.plot_y = LinePlot(line_width=2, color=[1, 1, 1, 1])
        self.plot_y.points = [(x, float(acc_y[x])/100) for x in range(len(acc_y))]
        self.y_data.add_plot(self.plot_y)
        self.y_data.xmax=len(acc_y)

        self.z_data.remove_plot(self.plot_z)
        self.plot_z = LinePlot(line_width=2, color=[1, 1, 1, 1])
        self.plot_z.points = [(x, float(acc_z[x])/100) for x in range(len(acc_z))]
        self.z_data.add_plot(self.plot_z)
        self.z_data.xmax=len(acc_z)       

        if self.tf.text == 'Celsius':
            self.t_data.remove_plot(self.plot_t)
            self.plot_t = LinePlot(line_width=2, color=[1, 1, 1, 1])
            self.plot_t.points = [(x, float(temp[x])/100) for x in range(len(temp))]
            self.t_data.add_plot(self.plot_t)
            self.t_data.xmax=len(temp)
        else:
            self.t_data.remove_plot(self.plot_t)
            self.plot_t = LinePlot(line_width=2, color=[1, 1, 1, 1])
            self.plot_t.points = [(x, (float(temp[x])/100)+32) for x in range(len(temp))]
            self.t_data.add_plot(self.plot_t)
            self.t_data.xmax=len(temp)
    
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

            if SAVE=='Enable':
                SAVE='1'
            else:
                SAVE='0'

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


class GUIApp (App):
    def build(self):
        home = Home()
        Clock.schedule_interval(home.update, 0.1)  #check ports every 0.1s
        return home

if __name__ == '__main__':
    app = GUIApp()
    app.run()
