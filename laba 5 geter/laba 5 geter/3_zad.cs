using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace laba_5_geter
{
    using System;
    using System.Linq;
    using System.Reflection;

    class CommandLineParser
    {
        public T Parse<T>(string[] args) where T : new()
        {
            T result = new T();

            foreach (var arg in args)
            {
                if (arg.StartsWith("-"))
                {
                    string[] parts = arg.Substring(1).Split('=');
                    string paramName = parts[0];
                    string paramValue = parts.Length > 1 ? parts[1] : null;

                    var property = typeof(T).GetProperties()
                        .FirstOrDefault(p => p.GetCustomAttribute<CommandLineAttribute>()?.CommandSwitch == paramName);

                    if (property != null)
                    {
                        object value;

                        if (property.PropertyType == typeof(bool))
                            value = bool.Parse(paramValue ?? "true");
                        else if (property.PropertyType == typeof(int))
                            value = int.Parse(paramValue ?? "0");
                        else
                            value = paramValue;

                        property.SetValue(result, value);
                    }
                }
            }

            return result;
        }
    }

    [AttributeUsage(AttributeTargets.Field | AttributeTargets.Property)]
    class CommandLineAttribute : Attribute
    {
        public string CommandSwitch { get; set; }

        public CommandLineAttribute(string commandSwitch)
        {
            CommandSwitch = commandSwitch;
        }
    }

    class Program
    {
        [CommandLine("name")]
        public string Name { get; set; }

        [CommandLine("age")]
        public int Age { get; set; }

        [CommandLine("is_active")]
        public bool IsActive { get; set; }

        static void Main(string[] args)
        {
            string arg = Console.ReadLine();
            string[] argg = arg.Split(" ");
            foreach (string a in argg) Console.WriteLine(a);
            CommandLineParser parser = new CommandLineParser();
            Program program = parser.Parse<Program>(argg);
            Console.WriteLine("Name: " + program.Name);
            Console.WriteLine("Age: " + program.Age);
            Console.WriteLine("IsActive: " + program.IsActive);

            Console.ReadLine();
        }
    }
}
