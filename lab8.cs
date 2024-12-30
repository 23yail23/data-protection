
using System;
using System.IO;
using System.Security.Cryptography;
using System.Text;

class AESExample
{
    public static (string CipherText, byte[] IV) Encrypt(string plainText, string key)
    {
        using (Aes aesAlg = Aes.Create())
        {
            aesAlg.Key = GenerateKey(key);
            aesAlg.GenerateIV(); // Генеруємо випадковий IV

            using (ICryptoTransform encryptor = aesAlg.CreateEncryptor(aesAlg.Key, aesAlg.IV))
            {
                using (MemoryStream msEncrypt = new MemoryStream())
                {
                    using (CryptoStream csEncrypt = new CryptoStream(msEncrypt, encryptor, CryptoStreamMode.Write))
                    {
                        using (StreamWriter swEncrypt = new StreamWriter(csEncrypt))
                        {
                            swEncrypt.Write(plainText);
                        }
                    }
                    return (Convert.ToBase64String(msEncrypt.ToArray()), aesAlg.IV);
                }
            }
        }
    }

    public static string Decrypt(string cipherText, string key, byte[] iv)
    {
        using (Aes aesAlg = Aes.Create())
        {
            aesAlg.Key = GenerateKey(key);
            aesAlg.IV = iv;

            using (ICryptoTransform decryptor = aesAlg.CreateDecryptor(aesAlg.Key, aesAlg.IV))
            {
                using (MemoryStream msDecrypt = new MemoryStream(Convert.FromBase64String(cipherText)))
                {
                    using (CryptoStream csDecrypt = new CryptoStream(msDecrypt, decryptor, CryptoStreamMode.Read))
                    {
                        using (StreamReader srDecrypt = new StreamReader(csDecrypt))
                        {
                            return srDecrypt.ReadToEnd();
                        }
                    }
                }
            }
        }
    }

    private static byte[] GenerateKey(string key)
    {
        using (var sha256 = SHA256.Create())
        {
            return sha256.ComputeHash(Encoding.UTF8.GetBytes(key));
        }
    }

    static void Main()
    {
        string key = "mysecurepassword"; // Надійний ключ

        Console.Write("Enter a message to encrypt: ");
        string originalMessage = Console.ReadLine();

        var (encryptedMessage, iv) = Encrypt(originalMessage, key);
        Console.WriteLine("Encrypted message: " + encryptedMessage);

        string decryptedMessage = Decrypt(encryptedMessage, key, iv);
        Console.WriteLine("Decrypted message: " + decryptedMessage);
    }
}
