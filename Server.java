import java.io.BufferedInputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.OutputStream;
import java.net.ServerSocket;
import java.net.Socket;

public class Server {

	public final static int port = 55555;  // you may change this
	public final static String file = "sample.txt";  // you may change this
	
	public static void server1() throws IOException{
		FileInputStream fis = null;
		BufferedInputStream bis = null;
		OutputStream os = null;
		ServerSocket servsock = null;
		Socket sock = null;
		try {
			servsock = new ServerSocket(port);
			while (true) {
				System.out.println("Waiting...");
				try {
					sock = servsock.accept();
	
					// send file
					File myFile = new File (file);
					byte [] mybytearray  = new byte [(int)myFile.length()];
					fis = new FileInputStream(myFile);
					
					bis = new BufferedInputStream(fis);
					bis.read(mybytearray,0,mybytearray.length);
					
					os = sock.getOutputStream();
					os.write(mybytearray,0,mybytearray.length);
					os.flush();
				}
				finally {
					if (bis != null) bis.close();
					if (os != null) os.close();
					if (sock!=null) sock.close();
				}
			}
		}
		finally {
			if (servsock != null) servsock.close();
		}
	}
}
