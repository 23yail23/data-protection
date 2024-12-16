
using System;
using System.Security.Cryptography;
using System.Text;

class Program
{
    static void Main(string[] args)
    {
        // Prompt the user to enter the hash to crack
        Console.Write("Enter the MD5 hash to crack: ");
        string targetHash = Console.ReadLine();

        // Brute-force loop from 00000 to 99999
        for (int i = 0; i <= 99999; i++)
        {
            // Format the number as a 5-digit string (e.g., 00001)
            string pin = i.ToString("D5");

            // Calculate the MD5 hash
            string hash = GetMd5Hash(pin);

            // Check for a match
            if (hash == targetHash)
            {
                Console.WriteLine($"PIN code found: {pin}");
                break;
            }
        }
    }

    // Method to calculate the MD5 hash
    static string GetMd5Hash(string input)
    {
        using (MD5 md5 = MD5.Create())
        {
            byte[] inputBytes = Encoding.ASCII.GetBytes(input);
            byte[] hashBytes = md5.ComputeHash(inputBytes);

            // Convert the byte array to a hexadecimal string
            StringBuilder sb = new StringBuilder();
            foreach (byte b in hashBytes)
            {
                sb.Append(b.ToString("x2"));
            }
            return sb.ToString();
        }
    }
}
