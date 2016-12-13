package edu.UMaine.bluetoothdemo;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.Set;
import java.util.UUID;

import android.app.Activity;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothClass;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;
import android.content.Intent;
import android.os.Bundle;
import android.os.Handler;
import android.view.Menu;
import android.view.View;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ListView;
import android.widget.TextView;
import android.widget.Toast;

public class MainActivity extends Activity {

	globalvar l = globalvar.getInstance();
	private static final int REQUEST_ENABLE_BT = 3;
	private static final String TAG = "BluetoothDemo";
	private ArrayAdapter<String> mArrayAdapter;
	private BluetoothAdapter mBluetoothAdapter;
	private BluetoothSocket mSocket; 
	private BluetoothDevice mDevice;
	private OutputStream mOutputStream;
	private InputStream mInputStream;
	 
	private byte [] readBuffer = new byte[1024];
	private byte delimiter = 13;   // New line
	private volatile boolean stopWorker = false;
	private int readBufferPosition = 0;

	private TextView tv;
	private EditText message;
	private Button send;
	
	void Find_Bluetooth(){
		// Set up the Bluetooth
		mBluetoothAdapter = BluetoothAdapter.getDefaultAdapter();
		if (mBluetoothAdapter == null) {
		  Toast.makeText(MainActivity.this, "getDefaultAdapter returns NULL", Toast.LENGTH_LONG).show();
		}

		if (!mBluetoothAdapter.isEnabled()) {
		    // use built-in Intent to enable Bluetooth if Bluetooth is disabled
		    Intent enableBtIntent = new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE);
		    startActivityForResult(enableBtIntent, REQUEST_ENABLE_BT);
		} else{
			//Toast.makeText(MainActivity.this, "Bluetooth is enabled", 2000).show();
		}
		
		mArrayAdapter  = new ArrayAdapter<String>(this, android.R.layout.simple_list_item_1);

        try {
	        // Find the Bluetooth device
			Set<BluetoothDevice> pairedDevices = mBluetoothAdapter.getBondedDevices();
	
			// If there are paired devices
			if (pairedDevices.size() > 0) {
			    // Loop through paired devices
				for (BluetoothDevice device : pairedDevices) {
					//Log.v(TAG, "Paired  Devices: " + device.getName() + " " + device.getAddress());
				    String deviceBTMajor= getBTMajorDeviceClass(device.getBluetoothClass().getMajorDeviceClass());
			        // Add the name and address to an array adapter to show in a ListView        
			        mArrayAdapter.add(device.getName() + "\n" + device.getAddress() + "\n" + deviceBTMajor);
			        Toast.makeText(MainActivity.this, device.getName() + " " + device.getAddress(), Toast.LENGTH_SHORT).show();
			        
			        if(device.getAddress().equals("20:13:09:29:33:11")) { //Need to change this to match the name of your device
			              mDevice = device;			
			              Toast.makeText(MainActivity.this, "Found the target bluetooth device!", Toast.LENGTH_LONG).show();
			        }
			    }
			} else {
				Toast.makeText(MainActivity.this, "No bonded devices!", Toast.LENGTH_LONG).show();
			}
        } catch (Exception  e) {
            // TODO Auto-generated catch block
        	Toast.makeText(MainActivity.this, "Got Exception in finding devices", Toast.LENGTH_LONG).show();
            // Log.e(TAG, e.toString(), e.fillInStackTrace());
        }
	}
	
	void Connect_Bluetooth(){
		// Connect the device
		UUID myUUID = UUID.fromString("00001101-0000-1000-8000-00805F9B34FB");
		
		try {
			mSocket = mDevice.createRfcommSocketToServiceRecord(myUUID);
			mSocket.connect();
			mBluetoothAdapter.cancelDiscovery();     // Cancel, discovery slows connection
			mOutputStream = mSocket.getOutputStream();
			mInputStream = mSocket.getInputStream();
		} catch (IOException  e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
	
	void Close_Bluetooth() throws IOException
	{
	    stopWorker = true;
	    mOutputStream.close();
	    mInputStream.close();
	    mSocket.close();
	    tv.setText("Bluetooth Closed");
	}
	
	void Bluetooth_Begin_Listen_For_Data() {
		final Handler handler = new Handler();

		Thread workerThread = new Thread (new Runnable() {
			public void run() {
				while(!Thread.currentThread().isInterrupted() && !stopWorker) {
					try{
						int bytesAvailable = mInputStream.available();
						if(bytesAvailable > 0) {
							byte[] packetBytes = new byte[bytesAvailable];
							mInputStream.read(packetBytes);
							send.setOnClickListener(new View.OnClickListener() {
								@Override
								public void onClick(View v) {
									Intent startnewactivity = new Intent(getApplicationContext(), MapsActivity.class);
									startActivity(startnewactivity);
								}
							});
							for(int i = 0; i <bytesAvailable; i++) {
								byte b = packetBytes[i];
								if(b == delimiter) {
									byte[] encodedBytes = new byte[readBufferPosition];
									System.arraycopy(readBuffer, 0, encodedBytes, 0, encodedBytes.length);
									final String data = new String(encodedBytes, "US-ASCII");
									readBufferPosition = 0;
									handler.post(new Runnable() {
										public void run() {
											tv.setText(data);
											l.setlatlongdata(data);
										}
									});

								} else {
									readBuffer[readBufferPosition++] = b;
								}
							}
						}
					} catch (IOException ex) {
						stopWorker = true;
					}
				}
			}
		});
		workerThread.start();
	}
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		final ListView listview = (ListView) findViewById(R.id.new_devices);
		tv = (TextView) findViewById(R.id.textView1);
		message = (EditText) findViewById(R.id.sendtext);
		send = (Button) findViewById(R.id.send);

		Find_Bluetooth();
		Connect_Bluetooth();
		
        listview.setAdapter(mArrayAdapter);
        
        Bluetooth_Begin_Listen_For_Data();		
	}
	
	@Override
    protected void onStart() {
		// TODO Auto-generated method stub
        super.onStart();
        

	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.main, menu);
		return true;
	}
	

	private String getBTMajorDeviceClass(int major){
		  switch(major){ 
		  case BluetoothClass.Device.Major.AUDIO_VIDEO:
		   return "AUDIO_VIDEO";
		  case BluetoothClass.Device.Major.COMPUTER:
		   return "COMPUTER";
		  case BluetoothClass.Device.Major.HEALTH:
		   return "HEALTH";
		  case BluetoothClass.Device.Major.IMAGING:
		   return "IMAGING"; 
		  case BluetoothClass.Device.Major.MISC:
		   return "MISC";
		  case BluetoothClass.Device.Major.NETWORKING:
		   return "NETWORKING"; 
		  case BluetoothClass.Device.Major.PERIPHERAL:
		   return "PERIPHERAL";
		  case BluetoothClass.Device.Major.PHONE:
		   return "PHONE";
		  case BluetoothClass.Device.Major.TOY:
		   return "TOY";
		  case BluetoothClass.Device.Major.UNCATEGORIZED:
		   return "UNCATEGORIZED";
		  case BluetoothClass.Device.Major.WEARABLE:
		   return "AUDIO_VIDEO";
		  default: return "unknown!";
		  }
   }
}
