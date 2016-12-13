/**
 * Created by Thomas on 11/17/2016.
 * This class is used in order to store variables and access them
 * across activities in the Android lifecycle
 */
public class globalvar {
    private static globalvar instance;
    private static String latlongdata;
    private globalvar() {
    }
    public static globalvar getInstance() {   //Creates an instance of the globalvar class
        if(instance == null){
            instance = new globalvar();
        }
        return instance;
    }

    public void setlatlongdata(String datain){  //Sets the string holding lat/lon information
        this.latlongdata = datain;
    }

    public String getlatlongdata(){             //Gets the string holding lat/lon information
        return this.latlongdata;
    }
}
