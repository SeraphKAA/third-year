using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;

namespace laba_5_geter
{
    interface IInterface1 
    {
        void Print_name();
        int Count_plus_1();
    }

    interface IInterface2 
    {
        void Print_name(string str_in);
        string Anything();
    }

    public class MyClass : IInterface1, IInterface2
    {
        public string Name;
        private int Count;
        internal static bool Check;
        protected double What_is;

        public void Print_name()
        {
            Console.WriteLine($"Это класс - MyClass");
        }

        public void Print_name(string str_in)
        {
            Console.WriteLine($"Это класс - MyClass и еще это - {str_in}");
        }

        public int Count_plus_1()
        {
            Count++;
            return Count;
        }

        internal string Anything(string str_in) 
        {
            return str_in + " " + str_in;
        }

        public string Anything() 
        {
            string a = "Anything is ";
            a += this.Name;
            return a;
        }


        public static void Meth_for_Cl(string ClassName) 
        {
            Type type = typeof(MyClass);
            if (type != null)
            {
                string filename = $"P{ClassName}_Content.txt";
                using (StreamWriter writer = new StreamWriter(filename))
                {
                    writer.WriteLine($"Содержимое класса {ClassName}: \n");

                    FieldInfo[] fields = type.GetFields(BindingFlags.Public | BindingFlags.NonPublic | BindingFlags.Instance | BindingFlags.Static);
                    foreach (FieldInfo field in fields)
                    {
                        writer.WriteLine($"Field: {field.Name} ({field.FieldType})");
                    }
                    writer.WriteLine();

                    MethodInfo[] methods = type.GetMethods(BindingFlags.Public | BindingFlags.NonPublic | BindingFlags.Instance | BindingFlags.Static);
                    foreach (MethodInfo method in methods)
                    {
                        writer.WriteLine($"Method: {method.ReturnType} {method.Name} ({GetParametersString(method.GetParameters())})");
                    }
                    writer.WriteLine();

                }
                Console.WriteLine($"Содержимое класса {ClassName} сохранено в файл {filename}");
            }
            else 
            {
                Console.WriteLine($"Класс {ClassName} не был найден");
            }
        }


        public static void SaveClassToCsFile(string ClassName)
        {
            Type type = typeof(MyClass);
            if (type != null)
            {
                string filename = $"P{ClassName}_Content.cs";
                using (StreamWriter writer = new StreamWriter(filename, false, Encoding.UTF8))
                {
                    writer.WriteLine($"using System;");

                    writer.WriteLine($"\n{ClassName} test = new();");
                    writer.WriteLine($"\nConsole.WriteLine(typeof({ClassName}));\nConsole.WriteLine(12312344);\n\n" +
                        $"public class {ClassName}");
                    writer.WriteLine("{");

                    FieldInfo[] fields = type.GetFields(BindingFlags.Public | BindingFlags.NonPublic | BindingFlags.Instance | BindingFlags.Static);
                    foreach (FieldInfo field in fields)
                    {
                        writer.WriteLine($"     {GetAccessModifier(field)} {field.FieldType} {field.Name};");
                    }
                    writer.WriteLine();

                    MethodInfo[] methods = type.GetMethods(BindingFlags.Public | BindingFlags.NonPublic | BindingFlags.Instance | BindingFlags.Static);
                    foreach (MethodInfo method in methods)
                    {
                        if (method.Name == ClassName)
                            writer.Write($"     {GetAccessModifier(method)} {method.ReturnType} {ClassName + "2"}(");
                        else
                        {
                            if (method.ReturnType.Name == "Boolean")
                                writer.Write($"     {GetAccessModifier(method)} {"bool"} {method.Name}(");
                            else if (method.ReturnType.Name == "Int32")
                                writer.Write($"     {GetAccessModifier(method)} {"int"} {method.Name}(");
                            else if (method.ReturnType.Name == "Type")
                                writer.Write($"     {GetAccessModifier(method)} {method.ReturnType} {method.Name}(");
                            else
                                writer.Write($"     {GetAccessModifier(method)} {method.ReturnType.Name.ToLower()} {method.Name}(");
                        }
                        ParameterInfo[] parameters = method.GetParameters();
                        for (int i = 0; i < parameters.Length; i++)
                        {
                            writer.Write($"{parameters[i].ParameterType} {parameters[i].Name}");
                            if (i < parameters.Length - 1)
                            {
                                writer.Write(", ");
                            }
                        }
                        writer.WriteLine(")");

                        if (method.ReturnType.Name == "Void")
                            writer.WriteLine("     { } ");
                        else if (method.ReturnType.Name == "String")
                            writer.WriteLine("     { return Convert.ToString(0); }");
                        else if (method.ReturnType.Name == "Boolean")
                            writer.WriteLine("     { return true; }");
                        else if (method.ReturnType.Name == "Type")
                        {
                            writer.Write("     { return typeof(");
                            writer.Write($"{ClassName});");
                            writer.WriteLine(" }");
                        }
                        else
                            writer.WriteLine("     { return 0; }");
                    }
                    writer.WriteLine("}");

                    Console.WriteLine($"Содержимое класса {ClassName} сохранено в файл {filename}");
                }
            }
            else
            {
                Console.WriteLine($"Класс {ClassName} не был найден");
            }
        }

        private static string GetParametersString(ParameterInfo[] parameters)
        {
            string result = string.Join(", ", parameters.Select(p => $"{p.ParameterType} {p.Name}"));
            return result;
        }


        private static string GetAccessModifier(MemberInfo member)
        {
            if (member is FieldInfo field)
            {
                if (field.IsPublic)
                    return "public";

                else if (field.IsPrivate)
                    return "private";

                else if (field.IsFamily)
                    return "protected";

                else if (field.IsAssembly)
                    return "internal";

                else if (field.IsFamilyOrAssembly)
                    return "protected internal";

                else
                    return "internal";
            }
            else if (member is MethodInfo method)
            {
                if (method.IsPublic)
                    return "public";

                else if (method.IsPrivate)
                    return "private";

                else if (method.IsFamily)
                    return "protected";

                else if (method.IsAssembly)
                    return "internal";

                else if (method.IsFamilyOrAssembly)
                    return "protected internal";

                else
                    return "internal";
            }
            return "internal";
        }


        public MyClass(string Name) 
        {
            Count = 0;
            Check = true;
            What_is = 0.1;
            this.Name = Name;
        }

        /*static void Main(string[] args)
        {
            MyClass myclass = new MyClass("Count_plus_1");

            MyClass.Meth_for_Cl($"{myclass.Name}");
            MyClass.SaveClassToCsFile($"{myclass.Name}");
        }*/
    }

}
