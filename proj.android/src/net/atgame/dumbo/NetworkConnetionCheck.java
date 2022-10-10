package net.atgame.dumbo;

import android.app.Activity;
import android.content.Context;
import android.net.ConnectivityManager;
import android.net.NetworkInfo;

public class NetworkConnetionCheck {

	private static Activity hiHighActivity = null;
	
	public static void setHiHighActivity(Activity hiHighActivity) {
		
		NetworkConnetionCheck.hiHighActivity = hiHighActivity;
	}

	public NetworkConnetionCheck(){
		
	}
	
	
	public static int getConnetivityStatus(Context ctx){
    	ConnectivityManager cm = (ConnectivityManager)ctx.getSystemService(Context.CONNECTIVITY_SERVICE);
    	
    	NetworkInfo net = cm.getActiveNetworkInfo();
    	
    	if (null != net) {
			if (net.getType() == ConnectivityManager.TYPE_WIFI) {
				return ConnectivityManager.TYPE_WIFI;
			}
			if (net.getType() == ConnectivityManager.TYPE_MOBILE) {
				return ConnectivityManager.TYPE_MOBILE;
			}
		}
    	
    	return 0;
    }
    
    public static boolean isNetworkConnection(){
    	int status = getConnetivityStatus(hiHighActivity.getApplicationContext());
    	return (status > 0) ? true : false;
    }
    
}
