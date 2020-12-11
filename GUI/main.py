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

import time


class Home (BoxLayout):
    
    com=ObjectProperty()
    conn_bt=ObjectProperty()

    st_bt=ObjectProperty()
    pr_bt=ObjectProperty()
    up_bt=ObjectProperty()

    def update (self, *args):                           #check if device is connected and abilitate GUI
        ports = [port.device for port in comports()]
        if not ports:
            self.com.values = []
            self.com.text="Ports"
            self.conn_bt.disabled = True
            self.conn_bt.text = "Connect"
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

    msg=ObjectProperty()

    def Connect(self):                               #connect to serial port
        if self.conn_bt.text == "Connect":
            self.conn_bt.text = "Disconnect"
            self.msg.text = self.msg.text + "\n" + "[" + time.strftime('%H:%M:%S') + "] " + "Connected to "+self.com.text
        else:
            self.conn_bt.text = "Connect"
            self.msg.text = self.msg.text + "\n" + "[" + time.strftime('%H:%M:%S') + "] " + "Device disconnected"

    def Work(self):                             #manage data acquisition and saving
        if self.st_bt.text == "Start":
            self.st_bt.text = "Stop"
            self.msg.text = self.msg.text + "\n" + "[" + time.strftime('%H:%M:%S') + "] " + "Data acquisition & Saving to EEPROM started"
        else:
            self.st_bt.text = "Start"
            self.msg.text = self.msg.text + "\n" + "[" + time.strftime('%H:%M:%S') + "] " + "Data acquisition & Saving to EEPROM stopped"

    def Print(self):                                            #print data
        self.msg.text = self.msg.text + "\n" + "[" + time.strftime('%H:%M:%S') + "] " + "Printing data"

    def ChangeSettings(self):                                   #change settings
        self.msg.text = self.msg.text + "\n" + "[" + time.strftime('%H:%M:%S') + "] " + "Settings changed"

    fsr=ObjectProperty()
    sf= ObjectProperty()
    tf=ObjectProperty()
    save=ObjectProperty()

class GUIApp (App):
    def build(self):
        home = Home()
        Clock.schedule_interval(home.update, 0.5)  #check ports every 0.5s
        return home

if __name__ == '__main__':
    app = GUIApp()
    app.run()
