package net.atgame.dumbo;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.util.Arrays;
import java.util.Collection;
import java.util.List;

import org.json.JSONException;
import org.json.JSONObject;

import android.app.Activity;
import android.app.Dialog;
import android.content.Context;
import android.content.ContextWrapper;
import android.content.Intent;
import android.content.SharedPreferences;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Color;
import android.graphics.drawable.ColorDrawable;
import android.net.Uri;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.Window;
import android.view.WindowManager;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ImageView;

import com.facebook.FacebookException;
import com.facebook.FacebookOperationCanceledException;
import com.facebook.FacebookRequestError;
import com.facebook.HttpMethod;
import com.facebook.Request;
import com.facebook.Response;
import com.facebook.Session;
import com.facebook.SessionState;
import com.facebook.UiLifecycleHelper;
import com.facebook.android.Facebook;
import com.facebook.model.GraphObject;
import com.facebook.model.GraphUser;
import com.facebook.widget.WebDialog;

public class FacebookConnectPlugin{

	private static final List<String> PERMISSIONS = Arrays.asList(
			"public_profile",
			"email",
			"user_friends",
			"publish_actions"
			);

	private static final String TAG = "FacebookPlugin";
	private static FacebookConnectPlugin fbConnectInstance;
	private UiLifecycleHelper uiHelper;
	private Session.StatusCallback statusCallback = new SessionStatusCallback();
	private Activity fbConnectActivity;
	private static int callIndex;
	private static Facebook fb;
	private SharedPreferences sp;
	private static Context ctx;
	
	private static boolean IsLogined = false;

	public FacebookConnectPlugin(Activity activity) {
		this.fbConnectActivity = activity;
		fbConnectInstance = this;
		uiHelper = new UiLifecycleHelper(activity, statusCallback);
		
		
	}


	public void onCreate(Bundle savedInstanceState) {
		// TODO Auto-generated method stub
		uiHelper.onCreate(savedInstanceState);
	}

	public static boolean IsLoggedIn(){

		return IsLogined;
	}
	public static void login(int cbIndex, String scope) {

		callIndex = cbIndex;
		fbConnectInstance.login_();
	}

	public static void logout(int cbIndex, String scope) {
		callIndex = cbIndex;
		fbConnectInstance.logout_();
	}

	public static void getFriends(int cbIndex, String scope){
		
		callIndex = cbIndex;
		fbConnectInstance.getFriends_();
	}

	public static void photoFeedShared(int cbIndex, String scope){
		callIndex = cbIndex;
		
		fbConnectInstance.fbSharePopup();
	}
	
	private void fbSharePopup(){
		this.fbConnectActivity.runOnUiThread(new Runnable() {
			
			@Override
			public void run() {
				// TODO Auto-generated method stub
				final Dialog dialog = new Dialog(fbConnectActivity);

				//setting custom layout to dialog
				dialog.requestWindowFeature(Window.FEATURE_NO_TITLE);
				dialog.getWindow().setBackgroundDrawable(new ColorDrawable(Color.TRANSPARENT));
				dialog.setContentView(R.layout.facebook_share_popup_layout);
				
				//adding text dynamically
				final EditText editText = (EditText) dialog.findViewById(R.id.txtName);
				editText.setText("http://dumbo.atgame.net/ text here.");

				ContextWrapper c = new ContextWrapper(fbConnectActivity);
				
				File imgFile = new  File(c.getFilesDir().getPath(), "/screenshot.jpg");
				ImageView image;
			    if(imgFile.exists())
			    {
			    	image = (ImageView)dialog.findViewById(R.id.image);
			    	image.setImageURI(Uri.fromFile(imgFile));
			    }


				//adding button click event
				Button dismissButton = (Button) dialog.findViewById(R.id.btnDone);
				Button cancelButton = (Button)dialog.findViewById(R.id.btnCancel);
				
				dismissButton.setOnClickListener(new OnClickListener() {
					
					@Override
					public void onClick(View v) {
						// TODO Auto-generated method stub
						dialog.dismiss();
						Log.d("dddddddddddddddddddddd", "dismissButton Click");
						fbConnectInstance.photoFeedShared_(editText.getText().toString());
					}
				});

				cancelButton.setOnClickListener(new OnClickListener() {
					
					@Override
					public void onClick(View v) {
						// TODO Auto-generated method stub
						Log.d("dddddddddddddddddddddd", "cancelButton Click");
						
						dialog.dismiss();
						
						FacebookConnectPlugin.nativeCallback(7,"test");
					}
				});
				
				dialog.show();
				editText.requestFocus();
				dialog.getWindow().setSoftInputMode(WindowManager.LayoutParams.SOFT_INPUT_STATE_VISIBLE);
//				InputMethodManager imm = (InputMethodManager) fbConnectActivity.getSystemService(Context.INPUT_METHOD_SERVICE);
//	            imm.toggleSoftInput(InputMethodManager.SHOW_FORCED, 0);
				
			}
		});
		
	}

	public static void inviteFriends(int cbIndex, String scope){
		callIndex = cbIndex;
		fbConnectInstance.inviteFriends_();
	}

	public static String getStatus(int cbIndex) {

		callIndex = cbIndex;

		return fbConnectInstance.getStatus_();
	}

	public void login_() {

		Session session = Session.getActiveSession();

		if (!session.isOpened() && !session.isClosed()) {
			Session.OpenRequest request = new Session.OpenRequest(this.fbConnectActivity);
			request.setPermissions(PERMISSIONS).setCallback(statusCallback);
			session.openForPublish(request);
			//			session.openForRead(request);
		} else {
			Session.openActiveSession(this.fbConnectActivity, true, statusCallback);
		}
	}

	private void createSession(){

	}
	public void logout_() {
		Session session = Session.getActiveSession();
		if (!session.isClosed()) {
			session.closeAndClearTokenInformation();
			nativeCallback(callIndex,"LOGOUT_SUCESS");
		}
	}

	public void getFriends_() {
		// TODO Auto-generated method stub
		Session session = Session.getActiveSession();

		if (!session.isOpened()) {
			Log.d("GET_FRIENDS SESSION NULL", "GET_FRIENDS SESSION NULL");
			return;
		}


//		String fqlQuery = 
//				"SELECT uid, name " +
//						" FROM user " + 
//						" WHERE uid IN " + 
//						"(SELECT uid2 FROM friend WHERE uid1=me())";


//		Log.d("Facebook FQL = ", fqlQuery);
		Bundle params = new Bundle();
//		params.putString("q", fqlQuery);
		
		params.putInt("limit", 500);
		params.putInt("offset", 0);
		Request request = new Request(session, "/me/friends", params, HttpMethod.GET, new Request.Callback() {

			@Override
			public void onCompleted(Response response) {
				// TODO Auto-generated method stub
				Log.i(TAG, "Result: " + response.toString());
				try{

					if (null != response.getError()) {
						String message = handleAPICallError(response.getError());
						nativeErrorCallback(callIndex, message);
					}else{
						GraphObject graphObject = response.getGraphObject();

						if(graphObject != null) {
							JSONObject jsonObject = graphObject.getInnerJSONObject();

							Log.d("data", jsonObject.toString(0));
							Log.d("FacebookConnectPlugin onCompleted", "graphObject == null");
							nativeCallback(callIndex,jsonObject.toString());
						}	
					}
				}catch(JSONException e){
					e.printStackTrace();
				}
			}
		});

		Request.executeBatchAsync(request); 

	}

	public void photoFeedShared_(final String message){

		this.fbConnectActivity.runOnUiThread(new Runnable() {

			@Override
			public void run() {
				// TODO Auto-generated method stub

				ContextWrapper c = new ContextWrapper(fbConnectActivity);
				Log.d("photoFeedShared_", c.getFilesDir().getPath());

				File f = new File(c.getFilesDir().getPath(), "/screenshot.jpg");
				Bitmap image = null;
				try {
					image = BitmapFactory.decodeStream(new FileInputStream(f));
				} catch (FileNotFoundException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}

				Request request = Request.newUploadPhotoRequest(Session.getActiveSession(), image, new Request.Callback() {
					@Override
					public void onCompleted(Response response) {
						if (null != response.getError()) {
							String message = handleAPICallError(response.getError());
							nativeErrorCallback(callIndex, message);
						}else{
							String photoId = response.getGraphObject().cast(GraphObjectWithId.class).getId();
							nativeCallback(callIndex,photoId);
						}

					}
				});

				Bundle params = request.getParameters();
				params.putString("message",message );
				request.executeAsync();
			}
		});
	}

	public void inviteFriends_() {
		// TODO Auto-generated method stub

		this.fbConnectActivity.runOnUiThread(new Runnable(){

			@Override
			public void run() {
				Bundle params = new Bundle();
				params.putString("message", "I just smashed " + 10000000 + " friends! Can you beat it?");
				showDialogWithoutNotificationBar("apprequests", params);

			}
		});
	}


	private void showDialogWithoutNotificationBar(String action, Bundle params) {
		// TODO Auto-generated method stub
		WebDialog dialog = new WebDialog.Builder(fbConnectActivity, Session.getActiveSession(), action, params).
				setOnCompleteListener(new WebDialog.OnCompleteListener() {
					@Override
					public void onComplete(Bundle values, FacebookException error) {
						if (error != null) {
							String message = "Please retry";
							
							if (error instanceof FacebookOperationCanceledException) {
								message = "Request cancelled";
							} else {
								message = "Network Error";
								if (error.getMessage() != null) {
									nativeErrorCallback(callIndex, message);	
								}
								
							}
							
						}else{
							nativeCallback(callIndex,"sent");
						}
					}
				}).build();

		Window dialog_window = dialog.getWindow();
		dialog_window.setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN,
				WindowManager.LayoutParams.FLAG_FULLSCREEN);

		dialog.show();
	}

	public String getStatus_() {

		Session session = Session.getActiveSession();

		if (session.getState().equals(SessionState.CREATED))
		{
			return "CREATED";
		}
		else if (session.getState().equals(SessionState.CREATED_TOKEN_LOADED))
		{
			return "CREATED_TOKEN_LOADED";
		}
		else if (session.getState().equals(SessionState.OPENING))
		{
			return "OPENING";
		}
		else if (session.getState().equals(SessionState.OPENED))
		{
			return "OPENED";
		}
		else if (session.getState().equals(SessionState.OPENED_TOKEN_UPDATED))
		{
			return "OPENED_TOKEN_UPDATED";
		}
		else if (session.getState().equals(SessionState.CLOSED_LOGIN_FAILED))
		{
			return "CLOSED_LOGIN_FAILED";
		}
		else if (session.getState().equals(SessionState.CLOSED))
		{
			return "CLOSED";
		}

		return "";
	}

	public void onResume() {
		// For scenarios where the main activity is launched and user
		// session is not null, the session state change notification
		// may not be triggered. Trigger it if it's open/closed.
		Session session = Session.getActiveSession();
		if (session != null && (session.isOpened() || session.isClosed())) {
			onSessionStateChange(session, session.getState(), null,"");
		}
		uiHelper.onResume();
	}

	public void onPause() {
		uiHelper.onPause();
	}

	public void onActivityResult(int requestCode, int resultCode, Intent data) {
		uiHelper.onActivityResult(requestCode, resultCode, data);
		Session.getActiveSession().onActivityResult(fbConnectActivity, requestCode, resultCode, data);
	}

	public void onSaveInstanceState(Bundle outState) {
		uiHelper.onSaveInstanceState(outState);
		Session session = Session.getActiveSession();
		Session.saveSession(session, outState);
	}


	public void onDestory() {
		uiHelper.onDestroy();
	}

	private void onSessionStateChange(Session session, SessionState state,
			Exception exception,final String param) {

		if (state.isOpened()) {
			IsLogined = true;

			Log.i(TAG, "Logged in...");
			if (callIndex == 0 || callIndex == 5) {
				Request.newMeRequest(session, new Request.GraphUserCallback() {

					// callback after Graph API response with user object
					@Override
					public void onCompleted(GraphUser user, Response response) {

						if (null != response.getError()) {
							String message = handleAPICallError(response.getError());
							nativeErrorCallback(callIndex, message);
						}else{
							if (user != null) {
								GraphObject responseGraphObject = response.getGraphObject();
								//Create the JSON object
								JSONObject json = responseGraphObject.getInnerJSONObject();

								nativeCallback(callIndex,json.toString());

							}

						}
					}
				}).executeAsync();
			}

		} else if (state.isClosed()) {
			Log.i(TAG, "Logged out...");
			IsLogined = false;
		}else if(state == SessionState.CLOSED_LOGIN_FAILED){
			
		}
	}

	public static void postCallback(int index, String params){
		nativeCallback(index,params);
	}

	public static native void nativeCallback(int cbIndex, String params);
	public static native void nativeErrorCallback(int cbIndex, String params);
	private class SessionStatusCallback implements Session.StatusCallback
	{
		@Override
		public void call(Session session, SessionState state,
				Exception exception) {
			// Respond to session state changes, ex: updating the view

			String param = "";
			Log.d("ACCESS_TOKEN", session.getAccessToken());
			Log.d("SESSION_STATE", state.name());

			onSessionStateChange(session, state, exception,param);


		}
	}	

	private boolean isSubsetOf(Collection<String> subset, Collection<String> superset) {
		for (String string : subset) {
			if (!superset.contains(string)) {
				return false;
			}
		}
		return true;
	}

	private interface GraphObjectWithId extends GraphObject {
		String getId();
	}

	private String handleAPICallError(FacebookRequestError error){

		String returnMessage = "";

		if (error.shouldNotifyUser()) {
			returnMessage = "Something went wrong. Please make sure you're connected to the internet and try again.";
		}else{
			switch (error.getCategory()) {
			case AUTHENTICATION_RETRY:
				break;
			case AUTHENTICATION_REOPEN_SESSION:
				break;
			case PERMISSION:
				returnMessage = "Please allow us to post on your behalf.";
				break;
			case SERVER:
			case THROTTLING:
				returnMessage = "The server is busy, please retry later.";
				break;
			case BAD_REQUEST:
				break;
			case OTHER:
			case CLIENT:
				break;
			default:
				returnMessage = "Please retry";
				break;
			}
		}


		return returnMessage;
	}
}
