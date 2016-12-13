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
    globalvar g = globalvar.getInstance();
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
        //Toast.makeText(MapsActivity.this, g.getlatlongdata(), Toast.LENGTH_SHORT).show();
        String data = g.getlatlongdata().trim();
        Toast.makeText(MapsActivity.this, data, Toast.LENGTH_SHORT).show();
        String delims = "[,]";
        String[] latlongdata = data.split(delims);
        String latitude = latlongdata[0];
        String NS = latlongdata[1];
        String longitude = latlongdata[2];
        String EW = latlongdata[3];
        float med = Float.parseFloat(latitude.substring(2))/60.0f;
        med +=  Float.parseFloat(latitude.substring(0, 2));
        if(NS.startsWith("S")) {
            med = -med;
        }
        float med2 = Float.parseFloat(longitude.substring(3))/60.0f;
        med2 +=  Float.parseFloat(longitude.substring(0, 3));
        if(EW.startsWith("W")) {
            med2 = -med2;
        }
        String lat = String.valueOf(med);
       // Toast.makeText(MapsActivity.this, lat, Toast.LENGTH_SHORT).show();
        // Add a marker in Sydney and move the camera
        LatLng sydney = new LatLng(med, med2);
        mMap.addMarker(new MarkerOptions().position(sydney).title(data));
        mMap.moveCamera(CameraUpdateFactory.newLatLng(sydney));
    }
}
