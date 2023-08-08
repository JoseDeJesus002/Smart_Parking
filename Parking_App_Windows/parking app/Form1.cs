using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace parking_app
{
    public partial class Form1 : Form
    {
        System.IO.Ports.SerialPort Arduino;
        bool IsClosed = false;

        public Form1()
        {
            InitializeComponent();

            Arduino = new System.IO.Ports.SerialPort();
            Arduino.PortName = "COM5";
            Arduino.BaudRate = 115200;
            Arduino.ReadTimeout = 500;
            Arduino.Open();
        }
        private void Form1_Load(object sender, EventArgs e)
        {
            Thread Hilo = new Thread (EscucharSerial);
            Hilo.Start ();
        }
        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            IsClosed = true;
            if (Arduino.IsOpen)
            {
                Arduino.Close();
            }
        }
        private void button1_Click(object sender, EventArgs e)
        {
            //Arduino.Write("E");
        }

        private void button2_Click(object sender, EventArgs e)
        {
            //Arduino.Write("O");
        }
        private void EscucharSerial()
        {
            while(!IsClosed)
            {
                try
                {
                    string Cadena = Arduino.ReadLine();
                    text1.Invoke(new MethodInvoker(delegate
                    {
                        text1.Text = Cadena;
                    }));
                }
                catch 
                {
                }
            }
        }
    }
}
