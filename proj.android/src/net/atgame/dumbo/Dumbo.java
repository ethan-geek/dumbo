/****************************************************************************
Copyright (c) 2010-2011 cocos2d-x.org

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
 ****************************************************************************/
package net.atgame.dumbo;

import java.io.IOException;
import java.util.ArrayList;
import java.util.List;




import org.cocos2dx.lib.Cocos2dxActivity;
import org.cocos2dx.lib.Cocos2dxGLSurfaceView;


import com.google.android.gms.ads.AdListener;
import com.google.android.gms.ads.AdRequest;
import com.google.android.gms.ads.AdSize;
import com.google.android.gms.ads.AdView;
import com.google.android.gms.ads.InterstitialAd;

import android.content.Context;
import android.content.Intent;
import android.content.res.AssetManager;
import android.content.res.Resources;
import android.os.Build;
import android.os.Bundle;
import android.os.Vibrator;
import android.util.Log;
import android.view.Gravity;
import android.view.View;
import android.view.WindowManager;

public class Dumbo extends Cocos2dxActivity{
	private static Dumbo high = null;

	private static InterstitialAd interstitial;
	private static AdView adView;
	private static boolean isAdViewAdded = false;

	protected FacebookConnectPlugin facebookConnectPlugin = null;
	protected NetworkConnetionCheck connetionCheck = null;
	
	public native void eraseLog();
	public native static void resultInApp(String itemId);
	
	static DumboInApp inApp;
	
	protected void onCreate(Bundle savedInstanceState){
		super.onCreate(savedInstanceState);	
		
		getWindow().addFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);
		getWindow().addFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN);
				
		high = this;

		facebookConnectPlugin = new FacebookConnectPlugin(this);
		facebookConnectPlugin.onCreate(savedInstanceState);
		
		
		NetworkConnetionCheck.setHiHighActivity(this);
		startInapp();
	}

	public Cocos2dxGLSurfaceView onCreateView() {
		Cocos2dxGLSurfaceView glSurfaceView = new Cocos2dxGLSurfaceView(this);
		// HiHigh should create stencil buffer
		glSurfaceView.setEGLConfigChooser(5, 6, 5, 0, 16, 8);

		return glSurfaceView;
	}

	public static void androidVibrate(long time) {
		Vibrator v = (Vibrator) high.getSystemService(Context.VIBRATOR_SERVICE);
		v.vibrate(time);
	}

	public static String[] getDeviceInfo() {
		
		String sdkVersion = Build.VERSION.RELEASE;
		String model = Build.MODEL;
		
		String [] str = {model ,sdkVersion};
		
		return str;
	}
	
	public static void androidShowAd() {
		high.runOnUiThread(new Runnable() {

			@Override
			public void run() {
				// TODO Auto-generated method stub
				interstitial = new InterstitialAd(high);
				interstitial.setAdUnitId("ca-app-pub-9009330876805600/1525344575");


				interstitial.setAdListener(new AdListener() {
					@Override
					public void onAdLoaded() {
						interstitial.show();
					}

					@Override
					public void onAdFailedToLoad(int errorCode) {
						Log.d("ad error", "ad error : " + errorCode);
					}
				});

				// Create ad request.
				AdRequest adRequest = new AdRequest.Builder().build();

				interstitial.loadAd(adRequest);
			}

		});
	}
	
	public static void androidInitBanner() {
		
		high.runOnUiThread(new Runnable() {

			@Override
			public void run() {
				// TODO Auto-generated method stub
				adView = new AdView(high);
				
				adView.setAdSize(AdSize.SMART_BANNER);
				adView.setAdUnitId("ca-app-pub-2616510431071196/1544701460");
					
				adView.setAdListener(new AdListener() {
					@Override
					public void onAdLoaded() {
						//high.addContentView(adView, null);
						if(isAdViewAdded) return;
						Log.d("huni", "ssibjot like world");
						
						WindowManager wm = (WindowManager) high.getSystemService ("window");
						
						WindowManager.LayoutParams mLayoutParams = new WindowManager.LayoutParams ();
						mLayoutParams.type = WindowManager.LayoutParams.TYPE_APPLICATION_PANEL;
						mLayoutParams.width = WindowManager.LayoutParams.MATCH_PARENT;
						mLayoutParams.height = WindowManager.LayoutParams.WRAP_CONTENT;
						mLayoutParams.flags |= WindowManager.LayoutParams.FLAG_NOT_FOCUSABLE;
						mLayoutParams.gravity = Gravity.BOTTOM;
						
						wm.addView (Dumbo.adView, mLayoutParams);
						
						Dumbo.adView.setVisibility(View.GONE);
						isAdViewAdded = true;
					}

					@Override
					public void onAdFailedToLoad(int errorCode) {
						Log.d("ad error", "ad error : " + errorCode);
					}
				});
				
				AdRequest adRequest = new AdRequest.Builder().addTestDevice("E6C7074A7E5FED7DC70A0BF2EA31276E").addTestDevice("1A116AD7EB19AA22A00558C97D7BBE13").build();
				adView.loadAd(adRequest);	
				
			}

		});
	}
	
	public static void androidShowBanner() {
		
		
		
		high.runOnUiThread(new Runnable() {

			@Override
			public void run() {
				if(isAdViewAdded == false) return;
				Dumbo.adView.setVisibility(View.VISIBLE);
				
			}

		});

	}
	
	public static void androidRemoveBanner() {
		
		high.runOnUiThread(new Runnable() {

			@Override
			public void run() {
				if(isAdViewAdded == false) return;
				Dumbo.adView.setVisibility(View.GONE);
				
			}

		});
		
	}
	
	
	public static void callFacebook() {
		
		Log.d("huni", "callFacebook");
	}

	public static String callServer(String addr, String jsonParameter, int time) {
		return HttpUtil.connectServer(addr, jsonParameter, time);
	}
	


	public static String[] getFileList(String filePath, String pattern) {


		Resources res = high.getResources(); //if you are in an activity
		AssetManager am = res.getAssets();
		String fileList[] = null;
		List<String> retFileList = null;
		try {
			fileList = am.list(filePath);
			Log.d("cococo", "--------------  " + filePath + " asdfasdf" + fileList.length + "");
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
			return null;
		}

		if (fileList != null)
		{   
			retFileList = new ArrayList<String>();


			for ( int i = 0;i<fileList.length;i++)
			{
			
				retFileList.add(fileList[i]);
			
			}
		}

		Log.d("cococo", "--------------  " + retFileList.size());

		am.close();
		if(retFileList != null) {
			return (String[])retFileList.toArray();	
		}
		return null;
	}

	static {
		System.loadLibrary("cocos2dcpp");
	}

	@Override
	protected void onResume() {
		// TODO Auto-generated method stub
		super.onResume();
		facebookConnectPlugin.onResume();
	}

	@Override
	protected void onPause() {
		// TODO Auto-generated method stub
		super.onPause();
		//eraseLog();
		facebookConnectPlugin.onPause();
	}

	@Override
	protected void onDestroy() {
		// TODO Auto-generated method stub
		super.onDestroy();
		
		//eraseLog();
		facebookConnectPlugin.onDestory();
		
		inApp.clear();
	}

	@Override
	protected void onSaveInstanceState(Bundle outState) {
		// TODO Auto-generated method stub
		super.onSaveInstanceState(outState);
		facebookConnectPlugin.onSaveInstanceState(outState);
	}     
	
	@Override
	public void onActivityResult(int requestCode, int resultCode, Intent data) {
		
		
		// inapp activity result 
		if (requestCode == 1001) {
			Log.d("myLog", "onActivityResult(" + requestCode + "," + resultCode
					+ "," + data);
			// Pass on the activity result to the helper for handling
			if (!inApp.mHelper.handleActivityResult(requestCode, resultCode, data)) {
				// not handled, so handle it ourselves (here's where you'd
				// perform any handling of activity results not related to
				// in-app
				// billing...
				super.onActivityResult(requestCode, resultCode, data);
			} else {
				Log.d("myLog", "onActivityResult handled by IABUtil.");
			}	
			return;
		}
		
		
		// facebook activity result
		super.onActivityResult(requestCode, resultCode, data);
		facebookConnectPlugin.onActivityResult(requestCode, resultCode, data);
		
	}
	
	public static void endInapp () {
		inApp.clear();
		inApp = null;
	}

	public static void startInapp () {
      inApp = new DumboInApp(high);
	}

	public static void callInApp(String item) {
		inApp.InAppBuyItem_U(item);
	}
	
}
