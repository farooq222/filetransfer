import java.io.BufferedOutputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.net.Socket;

public class Client {

	public final static int port = 55555;      // port
	public final static String ip = "127.0.0.1";  // localhost
	public final static String
	File_Recieved = "r-sample.txt";  // file received will be saved in this file

	public final static int FILE_SIZE = 6022386; // max file that can be transfered
	static int file_read=0;
	static int current = 0;
	static FileOutputStream fos = null;
	static BufferedOutputStream bos = null;
	static Socket sock = null;

	public static void client1() throws IOException{
		try {
			sock = new Socket(ip, port);
			System.out.println("Transfering File...");

			// receive file
			byte [] mybytearray = new byte [FILE_SIZE];
			InputStream is = sock.getInputStream();
			fos = new FileOutputStream(File_Recieved);
			bos = new BufferedOutputStream(fos);
			file_read = is.read(mybytearray,0,mybytearray.length);
			current = file_read;

			do
			{
				file_read = is.read(mybytearray, current, (mybytearray.length-current));
				if(file_read >= 0) current += file_read;
			} 
			
			while(file_read > -1);
			bos.write(mybytearray, 0 ,current );
			bos.flush();
			System.out.println("File " + File_Recieved  + " Recieved.");
		}
		finally {
			if (fos != null) fos.close();
			if (bos != null) bos.close();
			if (sock != null) sock.close();
		}
	}

}
