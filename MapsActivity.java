package edu.UMaine.bluetoothdemo;

import android.support.v4.app.FragmentActivity;
import android.os.Bundle;
import android.util.Log;
import android.widget.Toast;

import com.google.android.gms.maps.CameraUpdateFactory;
import com.google.android.gms.maps.GoogleMap;
import com.google.android.gms.maps.OnMapReadyCallback;
import com.google.android.gms.maps.SupportMapFragment;
import com.google.android.gms.maps.model.LatLng;
import com.google.android.gms.maps.model.MarkerOptions;

public class MapsActivity extends FragmentActivity implements OnMapReadyCallback {
    globalvar g = globalvar.getInstance();  //Gets the Global variables stored in globalvar instance
    private GoogleMap mMap;
    private static final String TAG = "Data";
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_maps);
        Log.i(TAG, "hsssl");
        // Obtain the SupportMapFragment and get notified when the map is ready to be used.
        SupportMapFragment mapFragment = (SupportMapFragment) getSupportFragmentManager()
                .findFragmentById(R.id.map);
        mapFragment.getMapAsync(this);
    }


    /**
     * Manipulates the map once available.
     * This callback is triggered when the map is ready to be used.
     * This is where we can add markers or lines, add listeners or move the camera. In this case,
     * we just add a marker near Sydney, Australia.
     * If Google Play services is not installed on the device, the user will be prompted to install
     * it inside the SupportMapFragment. This method will only be triggered once the user has
     * installed Google Play services and returned to the app.
     */
    @Override
    public void onMapReady(GoogleMap googleMap) {
        mMap = googleMap;
        String data = g.getlatlongdata().trim();    //Removes carriage returns and newline characters
        Toast.makeText(MapsActivity.this, data, Toast.LENGTH_SHORT).show();
        String delims = "[,]";        //Information is separated by commas for parsing
        String[] latlongdata = data.split(delims);
        String latitude = latlongdata[0];
        String NS = latlongdata[1];
        String longitude = latlongdata[2];
        String EW = latlongdata[3];
        /*
         *Converts from Degrees/minutes form to coordinate form for lat/lon values 
         */
        float med = Float.parseFloat(latitude.substring(2))/60.0f;  //Divides minutes form by 60
        med +=  Float.parseFloat(latitude.substring(0, 2));         //Adds degrees part
        if(NS.startsWith("S")) {                //Checks for N or S and multiplies by -1 accordingly
            med = -med;
        }
        float med2 = Float.parseFloat(longitude.substring(3))/60.0f;
        med2 +=  Float.parseFloat(longitude.substring(0, 3));
        if(EW.startsWith("W")) {                //Checks for E or W and multiplies by -1 accordingly
            med2 = -med2;
        }
        String lat = String.valueOf(med);
        // Add a marker in location and move the camera
        LatLng sydney = new LatLng(med, med2);
        mMap.addMarker(new MarkerOptions().position(sydney).title(data));
        mMap.moveCamera(CameraUpdateFactory.newLatLng(sydney));
    }
}
