package net.atgame.dumbo;

import java.nio.channels.AlreadyConnectedException;
import java.util.ArrayList;
import java.util.List;

import org.json.JSONException;
import org.json.JSONObject;

import android.app.Activity;
import android.app.PendingIntent;
import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;
import android.content.ServiceConnection;
import android.os.Bundle;
import android.os.IBinder;
import android.os.RemoteException;
import android.util.Log;
import android.widget.Toast;

import com.android.vending.billing.IInAppBillingService;
import com.example.android.trivialdrivesample.util.IabHelper;
import com.example.android.trivialdrivesample.util.IabResult;
import com.example.android.trivialdrivesample.util.Inventory;
import com.example.android.trivialdrivesample.util.Purchase;

public class DumboInApp {
	IInAppBillingService mService = null;
	IabHelper mHelper = null;
	Activity activity = null;
	
	ServiceConnection mServiceConn = new ServiceConnection() {
		
		@Override
		public void onServiceDisconnected(ComponentName name) {
			mService = null;
		}
		
		@Override
		public void onServiceConnected(ComponentName name, IBinder service) {
			mService = IInAppBillingService.Stub.asInterface(service);
		}
	};

	public DumboInApp(Activity activity) {

		this.activity = activity;
		String base64EncodedPublicKey = "MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEAr++nz9xrnpv6qW2T06oe5gC5TKy3ipbzXzrcQ5PzuoirD12N0sHC2oi3ZWJ1k2SNW1xKbievGxyci6MK55k8HvYAXMy6YZUUnUBRBELnW5o5YLuFMzZXWoHZsA9s7kZ8uEtYUDeRFoNXBMJOtAVF87YHl0aJ7FTVgSQBXc5P+Eo6ulpPte2uMYyCG6b+i6F5GlUsU/QcNeLxd1RAAQE5uP2WSF5D6wf1f9iz5+ygtaRyNI7YtTxSZpRtlMQfUbznV+BmZpKG4w40qRkchjZn5BOhNqxM5PGZ/TUP4CUR9i/xSyNgnpBSv1xXPLlvbT05rhAbGk2zn3l+nV4wodHqywIDAQAB";  //(구글에서 발급받은 바이너리키를 입력해줍니다)
		InAppInit_U(base64EncodedPublicKey, true);
	}

	public void InAppInit_U(String strPublicKey, boolean bDebug) {
		Log.d("dumbo inapp log", "Creating IAB helper." + bDebug);
		mHelper = new IabHelper(activity, strPublicKey);

		if (bDebug == true) {
			mHelper.enableDebugLogging(true, "IAB");
		}

		mHelper.startSetup(new IabHelper.OnIabSetupFinishedListener() {

			@Override
			public void onIabSetupFinished(IabResult result) {
				// TODO Auto-generated method stub
				Log.d("dumbo inapp log", "IAB Init " + result.isSuccess() + result.getMessage());

				if (result.isSuccess()) {
					Log.d("dumbo inapp log", "Querying inventory.");

					mHelper.queryInventoryAsync(mGotInventoryListener);
				}				
			}
		});
	}

	IabHelper.QueryInventoryFinishedListener mGotInventoryListener = new IabHelper.QueryInventoryFinishedListener() {
		public void onQueryInventoryFinished(IabResult result,
				Inventory inventory) {
			if (result.isFailure()) {
				Log.d("dumbo inapp log", "Failed to query inventory: " + result);
				SendConsumeResult(null, result);
				return;
			}

			List<String> inappList = inventory.getAllOwnedSkus(IabHelper.ITEM_TYPE_INAPP);

			for (String inappSku : inappList) {
				Purchase purchase = inventory.getPurchase(inappSku);
				Log.d("dumbo inapp log", "Consumeing ... " + inappSku);
				mHelper.consumeAsync(purchase, mConsumeFinishedListener);
			}

			Log.d("dumbo inapp log", "Query inventory was successful.");
		}
	};
	String itemId = null;
	public void InAppBuyItem_U(final String strItemId) {
		activity.runOnUiThread(new Runnable() {
			
			@Override
			public void run() {
				// TODO Auto-generated method stub

				/*
				 * TODO: for security, generate your payload here for
				 * verification. See the comments on verifyDeveloperPayload()
				 * for more info. Since this is a SAMPLE, we just use an empty
				 * string, but on a production app you should carefully generate
				 * this.
				 */
				String payload = "net.atgame.dumbo.inapp"; 
				itemId = strItemId;
				mHelper.launchPurchaseFlow(activity, strItemId,
						1001, mPurchaseFinishedListener, payload);

				Log.d("dumbo inapp log", "InAppBuyItem_U " + strItemId);
			}
		});
	}

	IabHelper.OnIabPurchaseFinishedListener mPurchaseFinishedListener = new IabHelper.OnIabPurchaseFinishedListener() {
		public void onIabPurchaseFinished(IabResult result, Purchase purchase) {
			Log.d("dumbo inapp log", "Purchase finished: " + result + ", purchase: "
					+ purchase);  
			//결제 완료 되었을때 각종 결제 정보들을 볼 수 있습니다. 이정보들을 서버에 저장해 놓아야 결제 취소시 변경된 정보를 관리 할 수 있을것 같습니다~

			if (purchase != null) {
				if (!verifyDeveloperPayload(purchase)) {
					Log.d("dumbo inapp log",
							"Error purchasing. Authenticity verification failed.");
				}
				mHelper.consumeAsync(purchase, mConsumeFinishedListener);
				
				Dumbo.resultInApp(itemId);
				itemId = null;
			} else {
				Log.d("dumbo inapp log", Integer.toString(result.getResponse()));
			}
		}
	};

	boolean verifyDeveloperPayload(Purchase p) {
		// server
		return true;
	}

	// Called when consumption is complete
	IabHelper.OnConsumeFinishedListener mConsumeFinishedListener = new IabHelper.OnConsumeFinishedListener() {
		public void onConsumeFinished(Purchase purchase, IabResult result) {
			Log.d("dumbo inapp log", "Consumption finished. Purchase: " + purchase
					+ ", result: " + result);
			SendConsumeResult(purchase, result);
		}
	};

	protected void SendConsumeResult(Purchase purchase, IabResult result) {
		JSONObject jsonObj = new JSONObject();

		try {
			jsonObj.put("Result", result.getResponse());
			if (purchase != null) {
				jsonObj.put("OrderId", purchase.getOrderId());
				jsonObj.put("Sku", purchase.getSku());
				jsonObj.put("purchaseData", purchase.getOriginalJson());
				jsonObj.put("signature", purchase.getSignature());

				Log.d("dumbo inapp log", "OrderId"  + purchase.getOrderId());
				Log.d("dumbo inapp log", "Sku"  + purchase.getSku());
				Log.d("dumbo inapp log", "purchaseData"  + purchase.getOriginalJson());
				Log.d("dumbo inapp log", "signature"  + purchase.getSignature());
			}
		} catch (JSONException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

	public void clear() {
		if(mServiceConn != null) {
			activity.unbindService(mServiceConn);			
		}
	}
	
	//
	//	public void init() {
	//		// TODO Auto-generated method stub
	//		activity.bindService(new Intent("com.android.vending.billing.InAppBillingService.BIND"), mServiceConn, Context.BIND_AUTO_CREATE);
	//
	//		String base64EncodedPublicKey = "MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEAr++nz9xrnpv6qW2T06oe5gC5TKy3ipbzXzrcQ5PzuoirD12N0sHC2oi3ZWJ1k2SNW1xKbievGxyci6MK55k8HvYAXMy6YZUUnUBRBELnW5o5YLuFMzZXWoHZsA9s7kZ8uEtYUDeRFoNXBMJOtAVF87YHl0aJ7FTVgSQBXc5P+Eo6ulpPte2uMYyCG6b+i6F5GlUsU/QcNeLxd1RAAQE5uP2WSF5D6wf1f9iz5+ygtaRyNI7YtTxSZpRtlMQfUbznV+BmZpKG4w40qRkchjZn5BOhNqxM5PGZ/TUP4CUR9i/xSyNgnpBSv1xXPLlvbT05rhAbGk2zn3l+nV4wodHqywIDAQAB";  //(구글에서 발급받은 바이너리키를 입력해줍니다)
	//
	//		mHelper = new IabHelper(activity, base64EncodedPublicKey);
	//		mHelper.enableDebugLogging(true);
	//		mHelper.startSetup(new IabHelper.OnIabSetupFinishedListener() {
	//			public void onIabSetupFinished(IabResult result) {
	//				if (!result.isSuccess()) {
	//					// 구매오류처리 ( 토스트하나 띄우고 결제팝업 종료시키면 되겠습니다 )
	//					Toast.makeText(activity, "inapp init error", 3).show();
	//				}
	//
	//				AlreardyPurchaseItems();    
	//				// AlreadyPurchaseItems(); 메서드는 구매목록을 초기화하는 메서드입니다. 
	//				// v3으로 넘어오면서 구매기록이 모두 남게 되는데 재구매 가능한 상품( 게임에서는 코인같은아이템은 ) 구매후 삭제해주어야 합니다.  //
	//				// 이 메서드는 상품 구매전 혹은 후에 반드시 호출해야합니다. ( 재구매가 불가능한 1회성 아이템의경우 호출하면 안됩니다 )
	//				
	//			}
	//		});
	//	}
	//
	//	void AlreardyPurchaseItems() {
	//		try {
	//			Bundle ownedItems = mService.getPurchases(3, activity.getPackageName(), "inapp", null);
	//			int response = ownedItems.getInt("RESPONSE_CODE");
	//			if (response == 0) {
	//				ArrayList<String> purchaseDataList = ownedItems
	//						.getStringArrayList("INAPP_PURCHASE_DATA_LIST");
	//				String[] tokens = new String[purchaseDataList.size()];
	//				for (int i = 0; i < purchaseDataList.size(); ++i) {
	//					String purchaseData = (String) purchaseDataList.get(i);
	//					JSONObject jo = new JSONObject(purchaseData);
	//					tokens[i] = jo.getString("purchaseToken");
	//					// 여기서 tokens를 모두 컨슘 해주기
	//					mService.consumePurchase(3, activity.getPackageName(), tokens[i]);
	//				}
	//			}
	//			// 토큰을 모두 컨슘했으니 구매 메서드 처리
	//		} catch (Exception e) {
	//			e.printStackTrace();
	//		}
	//	}

	//	IabHelper.OnIabPurchaseFinishedListener mPurchaseFinishedListener  = new IabHelper.OnIabPurchaseFinishedListener() {
	//		public void onIabPurchaseFinished(IabResult result, Purchase purchase) {
	//			// 여기서 아이템 추가 해주시면 됩니다.
	//			// 만약 서버로 영수증 체크후에 아이템 추가한다면, 서버로 purchase.getOriginalJson() , purchase.getSignature() 2개 보내시면 됩니다.			
	//			if(itemId != null) {
	//				Toast.makeText(activity, "inapp success", 3).show();
	//				AlreardyPurchaseItems();
	//				HiHigh.resultInApp(itemId);
	//				itemId = null;
	//			}
	//		}
	//	};
	//
	//	public void Buy(String id_item) {
	//		// Var.ind_item = index;
	//		itemId = id_item;
	//		try {
	//			AlreardyPurchaseItems();
	//			Bundle buyIntentBundle = mService.getBuyIntent(3, activity.getPackageName(), id_item, "inapp", "net.atgame.dumbo");
	//			PendingIntent pendingIntent = buyIntentBundle.getParcelable("BUY_INTENT");
	//			if (pendingIntent != null) {
	//				//startIntentSenderForResult(pendingIntent.getIntentSender(), 1001, new Intent(), Integer.valueOf(0), Integer.valueOf(0), Integer.valueOf(0));
	//				mHelper.launchPurchaseFlow(activity, activity.getPackageName(), 1001,  mPurchaseFinishedListener);
	//				// 위에 두줄 결제호출이 2가지가 있는데 위에것을 사용하면 결과가 onActivityResult 메서드로 가고, 밑에것을 사용하면 OnIabPurchaseFinishedListener 메서드로 갑니다.  (참고하세요!)
	//				
	//			} else {
	//				// 결제가 막혔다면
	//				Toast.makeText(activity, "error inapp _  buy", 3).show();
	//				AlreardyPurchaseItems();
	//			}
	//		} catch (Exception e) {
	//			e.printStackTrace();
	//			Toast.makeText(activity, "exception _ buy", 3).show();
	//		}
	//	}
	//	
	//	
	
}
