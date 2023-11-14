using System.Threading;
using Solid.Arduino.Firmata;
using Solid.Arduino;


namespace codigoFinalIntento1
{
    class Program
    {
        static byte xFinalCarrera = 26;
        static byte yFinalCarrera = 27;
        static byte ServoPin = 28;
        static byte[] motorX = { 2, 3, 4, 5 };
        static byte[] motorY = { 22, 23, 24, 25 };


        static void Main(string[] args)
        {
            ISerialConnection connection = GetConnection();

            if (connection != null)
            {
                using var session = new ArduinoSession(connection);
                // Establece los pines que se usaran como entrada o salida
                LeerCoordenadas(session);
                //IniciarPines(session);
                //moverMotores(session, 2000, motorX);
            }
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

        private static object IniciarPines(IFirmataProtocol session)
        {
            // Pines Final de carreras
            session.SetDigitalPinMode(xFinalCarrera, PinMode.DigitalInput);
            session.SetDigitalPinMode(yFinalCarrera, PinMode.DigitalInput);

            // Pin Servomotor
            session.SetDigitalPinMode(ServoPin, PinMode.ServoControl);

            //Pines motor X
            for (byte i = 0; i < motorX.Length; i++)
            {
                session.SetDigitalPinMode(motorX[i], PinMode.DigitalOutput);
                Console.WriteLine($"Pin numero: {i} en modo OUTPUT");
            }

            //Pines motor Y
            for (byte i = 0; i < motorY.Length; i++)
            {
                session.SetDigitalPinMode(motorY[i], PinMode.DigitalOutput);
                Console.WriteLine($"Pin numero: {i} en modo OUTPUT");
            }
            return session;
        }

        private static void LeerCoordenadas(IFirmataProtocol session)
        {
            String line;
            String[] valoresTexto;
            try
            {
                StreamReader sr = new StreamReader("coordenadas_V2.txt");
                line = sr.ReadLine();
                while (line != null)
                {
                    line = sr.ReadLine();
                    if (line != null) {

                        valoresTexto = line.Split('/');
                        if (valoresTexto[0] == "0") {
                            session.SetDigitalPin(ServoPin, 30);
                        }
                    }
                }
                sr.Close();
            }
            catch (Exception e)
            {
                Console.WriteLine("Exception: " + e.Message);
            }
            finally
            {
                Console.WriteLine("Executing finally block.");
            }
        }

        private static void moverMotores(IFirmataProtocol session, int numDePasos, byte[] pines)
        {
            byte[,] paso =
            {
                { 1, 0, 0, 0},
                { 0, 1, 0, 0 },
                { 0, 0, 1, 0 },
                { 0, 0, 0, 1 }
            };
            byte demoraEntrePasos = 5;
            int pasosRealizados = 0;
            do
            {
                for (int i = 0; i < 4; i++)
                {
                    session.SetDigitalPin(pines[0], TraducirByteABool(paso[i, 0]));
                    pasosRealizados++;
                    Thread.Sleep(demoraEntrePasos);
                    if (pasosRealizados >= numDePasos) { break; }
                    session.SetDigitalPin(pines[1], TraducirByteABool(paso[i, 1]));
                    pasosRealizados++;
                    Thread.Sleep(demoraEntrePasos);
                    if (pasosRealizados >= numDePasos) { break; }
                    session.SetDigitalPin(pines[2], TraducirByteABool(paso[i, 2]));
                    pasosRealizados++;
                    Thread.Sleep(demoraEntrePasos);
                    if (pasosRealizados >= numDePasos) { break; }
                    session.SetDigitalPin(pines[3], TraducirByteABool(paso[i, 3]));
                    pasosRealizados++;
                    Thread.Sleep(demoraEntrePasos);
                    if (pasosRealizados >= numDePasos) { break; }
                    Thread.Sleep(demoraEntrePasos);
                    Console.WriteLine("Vuelta");
                }
            } while (pasosRealizados < numDePasos);
            Console.WriteLine($"Pasos realizados: {pasosRealizados}");
            Console.WriteLine($"Num de pasos: {numDePasos}");
        }

        private static bool TraducirByteABool(byte estado)
        {
            bool respuesta = false;
            if(estado == 0) { respuesta = false; }
            if(estado == 1) { respuesta = true; }
            return respuesta;
        }
    }
}