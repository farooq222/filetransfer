import java.io.IOException;

public class Unit_test {

	public static void main(String[] args) throws IOException {
		Server ser = new Server();
		Client cli = new Client();
		
		ser.server1();
		cli.client1();
	  	
	  	
	}

}
