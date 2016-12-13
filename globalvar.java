/**
 * Created by Thomas on 11/17/2016.
 */
public class globalvar {
    private static globalvar instance;
    private static String latlongdata;
    private globalvar() {
    }
    public static globalvar getInstance() {
        if(instance == null){
            instance = new globalvar();
        }
        return instance;
    }

    public void setlatlongdata(String datain){
        this.latlongdata = datain;
    }

    public String getlatlongdata(){
        return this.latlongdata;
    }
}
