using System;
using System.IO;
using Solid.Arduino;
using Solid.Arduino.Firmata;

namespace Demo
{
    class Program
    {
        static void Main(string[] args)
        {
            ISerialConnection connection = GetConnection();

            if (connection != null)
                using (var session = new ArduinoSession(connection))
                    PerformBasicTest(session);

            Console.WriteLine("Press a key");
            Console.ReadKey(true);
        }

        private static ISerialConnection GetConnection()
        {
            Console.WriteLine("Searching Arduino connection...");
            ISerialConnection connection = EnhancedSerialConnection.Find();

            if (connection == null)
                Console.WriteLine("No connection found. Make shure your Arduino board is attached to a USB port.");
            else
                Console.WriteLine($"Connected to port {connection.PortName} at {connection.BaudRate} baud.");

            return connection;
        }

        private static void PerformBasicTest(IFirmataProtocol session)
        {
            var firmware = session.GetFirmware();
            Console.WriteLine($"Firmware: {firmware.Name} version {firmware.MajorVersion}.{firmware.MinorVersion}");
            var protocolVersion = session.GetProtocolVersion();
            Console.WriteLine($"Firmata protocol version {protocolVersion.Major}.{protocolVersion.Minor}");

            session.SetDigitalPinMode(13, PinMode.DigitalOutput);
            session.SetDigitalPin(13, true);
            Console.WriteLine("Command sent: LUZ13 on (pin 13)");
            Console.WriteLine("Press a key");
            Console.ReadKey(true);
            session.SetDigitalPin(13, false);
            Console.WriteLine("Command sent: LUZ13 off");
        }

        private static void LeerArchivo(){
            
        }
    
    }
}