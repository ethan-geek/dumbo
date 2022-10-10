package net.atgame.dumbo;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;

public class NetworkChangeReceiver extends BroadcastReceiver {

	@Override
	public void onReceive(Context context, Intent intent) {
		// TODO Auto-generated method stub
		int status = NetworkConnetionCheck.getConnetivityStatus(context);
		
		nativeNetworkChangeCallback(status);
	}
	public static native void nativeNetworkChangeCallback(int statusCode);
	
	
}
