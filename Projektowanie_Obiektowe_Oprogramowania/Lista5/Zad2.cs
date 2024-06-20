using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Zad2
{
    public class CaesarStream : Stream
    {
        private Stream _stream;
        private int cae_offset;
        const char first_char = ' ';
        const char last_char = '~';
        public CaesarStream(Stream stream, int offset)
        {
            _stream = stream;
            this.cae_offset = offset;
        }
        public override int Read(byte[] buffer, int offset, int count)
        {
            var readStream = this._stream.Read(buffer, offset, count);

            for (int i = 0; i < buffer.Length; i++)
            {
                char c = (char)buffer[i];
                if (c >= first_char && c <= last_char)
                {
                    int len = (last_char - first_char + 1);
                    buffer[i] = (byte)((buffer[i] + len + this.cae_offset - first_char) % len + first_char);
                }
            }

            return readStream;
        }

        public int Read(byte[] buffer)
        {
            return Read(buffer, 0, buffer.Length);
        }
        public override void Write(byte[] buffer, int offset, int count)
        {
            var newBuff = new byte[buffer.Length];

            for (int i = 0; i < buffer.Length; i++)
            {
                char c = (char)buffer[i];
                if (c >= first_char && c <= last_char)
                    newBuff[i] = (byte)((buffer[i] + this.cae_offset - first_char) % (last_char - first_char + 1) + first_char);
                else
                    newBuff[i] = buffer[i];
            }
            _stream.Write(newBuff, offset, count);
        }

        public void Write(byte[] buffer)
        {
            Write(buffer, 0, buffer.Length);
        }
        public override bool CanRead => _stream.CanRead;
        public override bool CanSeek => _stream.CanSeek;
        public override bool CanWrite => _stream.CanWrite;
        public override long Length => _stream.Length;
        public override long Position { get => _stream.Position; set => _stream.Position = value; }
        public override void Flush() { _stream.Flush(); }
        public override long Seek(long offset, SeekOrigin origin) { return _stream.Seek(offset, origin); }
        public override void SetLength(long value) { _stream.SetLength(value); }
    }
    internal class Program
    {
        static void Main(string[] args)
        {
            FileStream fileToWrite = File.Create("file.txt");
            CaesarStream caeToWrite = new CaesarStream(fileToWrite, 5);
            // 5 to przesunięcie
            caeToWrite.Write(Encoding.ASCII.GetBytes("Hello World"));
            fileToWrite.Close();
            FileStream fileToRead = File.Open("file.txt", FileMode.Open);
            CaesarStream caeToRead = new CaesarStream(fileToRead, -5);
            // -5 znosi 5
            var bytes = new byte[1024];
            caeToRead.Read(bytes);
            Console.WriteLine(Encoding.ASCII.GetString(bytes));
            Console.ReadLine();
        }
    }
}
