using System;
using Solid.Arduino.Firmata;
using System.IO.Ports;
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

            session.SetDigitalPinMode(10, PinMode.DigitalOutput);
            session.SetDigitalPin(10, true);
            Console.WriteLine("Press a key");
            Console.ReadKey(true);
            session.SetDigitalPin(10, false);
        }
    }
}