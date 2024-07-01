/*
Реализовать системы электрических источников и приборов, соединенных между собой через шнуры. В интерфейсах должны
быть предусмотрена возможность получения информации о напряжении и максимальной мощности, которую под
Прибор должен иметь наименование, потребляемую мощность, а источник и провод – списки подключенных  , приборов.

Интерфейсы:
    IElectricSource(источник тока)
    IElectricAppliance(электрический
    прибор)
    IElectricWire(электрический шнур)
Классы:
    SolarBattery(солнечная батарея)
    DieselGenerator(дизельный генератор)
    NuclearPowerPlant(атомная
    электростанция)
    Kettle(чайник)
    Lathe(токарный станок)
    Refrigerator(холодильник)
    ElectricPowerStrip(электрический
    удлинитель)
    HighLine(высоковольтная линия)
    StepDownTransformer(понижающий
    трансформатор, должен реализовывать
    интерфейсы и потребителя и источника тока)
*/


using laba_3_geter;


void Main()
{
    SolarBattery solarBattery = new SolarBattery(12, 500);
    DieselGenerator dieselGenerator = new DieselGenerator(220, 1000);
    NuclearPowerPlant nuclearPowerPlant = new NuclearPowerPlant(1000, 5000000);

    Kettle kettle = new Kettle("Electric Kettle", 1500);
    Lathe lathe = new Lathe("Metal Lathe", 1000);
    Refrigerator refrigerator = new Refrigerator("Refrigerator", 0);

    ElectricPowerStrip powerStrip = new ElectricPowerStrip();
    HighLine highLine = new HighLine();
    StepDownTransformer stepDownTransformer = new StepDownTransformer(12, 2000);

    powerStrip.ADD(kettle);
    powerStrip.ConnectedAppliances.Add(refrigerator);

    highLine.ConnectedAppliances.Add(lathe);

/*
    Console.WriteLine("Solar Battery Information:");
    Console.WriteLine($"Voltage: {solarBattery.GetVoltage()}V");
    Console.WriteLine($"Max Power: {solarBattery.GetMaxPower()}W");

    Console.WriteLine("\nDiesel Generator Information:");
    Console.WriteLine($"Voltage: {dieselGenerator.GetVoltage()}V");
    Console.WriteLine($"Max Power: {dieselGenerator.GetMaxPower()}W");

    Console.WriteLine("\nNuclear Power Plant Information:");
    Console.WriteLine($"Voltage: {nuclearPowerPlant.GetVoltage()}V");
    Console.WriteLine($"Max Power: {nuclearPowerPlant.GetMaxPower()}W");

    Console.WriteLine("\nKettle Information:");
    Console.WriteLine($"Name: {kettle.GetName()}");
    Console.WriteLine($"Power: {kettle.GetPower()}W");

    Console.WriteLine("\nLathe Information:");
    Console.WriteLine($"Name: {lathe.GetName()}");
    Console.WriteLine($"Power: {lathe.GetPower()}W");*/

    Console.WriteLine("\nRefrigerator Information:");
    Console.WriteLine($"Name: {refrigerator.GetName()}");
    Console.WriteLine($"Power: {refrigerator.GetPower()}W");

/*    Console.WriteLine("\nPower Strip Information:");
    Console.WriteLine("Connected Appliances:");
    foreach (IElectricAppliance appliance in powerStrip.ConnectedAppliances)
    {
        Console.WriteLine($"[+] Name: {appliance.GetName()} Power: {appliance.GetPower()}W");
    }

    Console.WriteLine("\nHigh Line Information:");
    Console.WriteLine("Connected Appliances:");
    foreach (IElectricAppliance appliance in highLine.ConnectedAppliances)
    {
        Console.WriteLine($"Name: {appliance.GetName()} Power: {appliance.GetPower()}W");
    }*/

    /*Console.WriteLine("\nStep Down Transformer Information:");
    Console.WriteLine($"Voltage: {stepDownTransformer.GetVoltage()}V");
    Console.WriteLine($"Max Power: {stepDownTransformer.GetMaxPower()}W");
    Console.WriteLine($"Name: {stepDownTransformer.GetName()}");
    Console.WriteLine($"Total Power: {stepDownTransformer.GetPower()}W");*/

    Electrik electrik = new();
    electrik.ConnectedAppliances1.Add(refrigerator);

    electrik.Check();

}

Main();


//интерфейс батареек имет разную вместимость, функция сколько продержится общую делить на перед