using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace laba_3_geter
{
    interface IElectricSource
    {
        float GetVoltage();
        float GetMaxPower();
    }

    interface IElectricAppliance
    {
        string GetName();
        float GetPower();
    }

    interface IElectricWire
    {
        List<IElectricAppliance> ConnectedAppliances { get; set; }
    }

    class SolarBattery : IElectricSource
    {
        private float voltage;
        private float maxPower;

        public SolarBattery(float voltage, float maxPower)
        {
            this.voltage = voltage;
            this.maxPower = maxPower;
        }

        public float GetVoltage()
        {
            return voltage;
        }

        public float GetMaxPower()
        {
            return maxPower;
        }
    }

    class DieselGenerator : IElectricSource
    {
        private float voltage;
        private float maxPower;

        public DieselGenerator(float voltage, float maxPower)
        {
            this.voltage = voltage;
            this.maxPower = maxPower;
        }

        public float GetVoltage()
        {
            return voltage;
        }

        public float GetMaxPower()
        {
            return maxPower;
        }
    }

    class NuclearPowerPlant : IElectricSource
    {
        private float voltage;
        private float maxPower;

        public NuclearPowerPlant(float voltage, float maxPower)
        {
            this.voltage = voltage;
            this.maxPower = maxPower;
        }

        public float GetVoltage()
        {
            return voltage;
        }

        public float GetMaxPower()
        {
            return maxPower;
        }
    }

    class Kettle : IElectricAppliance
    {
        private string name;
        private float power;

        public Kettle(string name, float power)
        {
            this.name = name;
            this.power = power;
        }

        public string GetName()
        {
            return name;
        }

        public float GetPower()
        {
            return power;
        }
    }

    class Lathe : IElectricAppliance
    {
        private string name;
        private float power;

        public Lathe(string name, float power)
        {
            this.name = name;
            this.power = power;
        }

        public string GetName()
        {
            return name;
        }

        public float GetPower()
        {
            return power;
        }
    }

    class Refrigerator : IElectricAppliance
    {
        private string name;
        private float power;

        public Refrigerator(string name, float power)
        {
            this.name = name;
            this.power = power;
        }

        public string GetName()
        {
            return name;
        }

        public float GetPower()
        {
            return power;
        }
    }

    // Класс электрического удлинителя
    class ElectricPowerStrip : IElectricWire
    {
        public List<IElectricAppliance> ConnectedAppliances { get; set; }

        public ElectricPowerStrip()
        {
            ConnectedAppliances = new List<IElectricAppliance>();
        }
        public void ADD(IElectricAppliance obj) 
        {
            ConnectedAppliances.Add(obj);
        }
    }

    class HighLine : IElectricWire
    {
        public List<IElectricAppliance> ConnectedAppliances { get; set; }

        public HighLine()
        {
            ConnectedAppliances = new List<IElectricAppliance>();
        }
    }

    class StepDownTransformer : IElectricWire, IElectricSource, IElectricAppliance
    {
        private float voltage;
        private float maxPower;

        public List<IElectricAppliance> ConnectedAppliances { get; set; }

        public StepDownTransformer(float voltage, float maxPower)
        {
            this.voltage = voltage;
            this.maxPower = maxPower;
            ConnectedAppliances = new List<IElectricAppliance>();
        }

        public float GetVoltage()
        {
            return voltage;
        }

        public float GetMaxPower()
        {
            return maxPower;
        }

        public string GetName()
        {
            return "Step Down Transformer";
        }

        public float GetPower()
        {
            float totalPower = 0;
            foreach (IElectricAppliance appliance in ConnectedAppliances)
            {
                totalPower += appliance.GetPower();
            }
            return totalPower;
        }
    }
    class Electrik
    {
        private double totalPower = 0;
        public List<IElectricAppliance> ConnectedAppliances1 { get; set; }

        public double GetTotalMaxPower()
        {
            totalPower = 0;
            foreach (IElectricAppliance x in ConnectedAppliances1)
            {
                totalPower += x.GetPower();
            }
            return totalPower;
        }
        public void Check()
        {
            double max_power = GetTotalMaxPower();
            if (max_power > 480)
                Console.WriteLine("УМЭР");
            else if (max_power == 0)
                Console.WriteLine("НЕ РАБОТАЕТ");
            else if (max_power <= 480 && max_power != 0)
                Console.WriteLine("ВСЕ ГУД");
            



        }
        public Electrik()
        {
            ConnectedAppliances1 = new List<IElectricAppliance>();
        }
    }

}
