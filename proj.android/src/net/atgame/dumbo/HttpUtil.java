package net.atgame.dumbo;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.OutputStreamWriter;
import java.net.HttpURLConnection;
import java.net.URL;

import javax.net.ssl.HostnameVerifier;
import javax.net.ssl.HttpsURLConnection;
import javax.net.ssl.SSLContext;
import javax.net.ssl.SSLSession;
import javax.net.ssl.TrustManager;
import javax.net.ssl.X509TrustManager;

import android.content.Context;
import android.net.ConnectivityManager;
import android.net.NetworkInfo;
import android.util.Log;
/*
 작성자 : 도플광어
 설명 : 안드로이드 용  html 다운로더 모듈 (https 도 지원함)
 */
public class HttpUtil {

	public static String connectServer(String addr, String jsonParameter, int time) {
		StringBuilder html = new StringBuilder(); 
		try {
			URL url = new URL(addr);
			//HttpURLConnection conn = (HttpURLConnection)url.openConnection();
			
			HttpURLConnection conn = null; 
            
            if (url.getProtocol().toLowerCase().equals("https")) { 
                //trustAllHosts(); 
                HttpsURLConnection https = (HttpsURLConnection) url.openConnection(); 
                https.setHostnameVerifier(DO_NOT_VERIFY); 
                conn = https; 
                
                
                
            } else { 
            	conn = (HttpURLConnection) url.openConnection(); 
            } 
			
			if (conn != null) {
				
				conn.setConnectTimeout(time);
				conn.setRequestMethod("POST");
				conn.setDoInput(true);
				conn.setDoOutput(true);
				conn.setUseCaches(false);
				conn.setRequestProperty("Content-Type","application/json");  
				
				
				OutputStream os = conn.getOutputStream();
				BufferedWriter writer = new BufferedWriter(
				        new OutputStreamWriter(os, "UTF-8"));
				writer.write(jsonParameter);
				writer.flush();
				writer.close();
				os.close();

				conn.connect();
				
				int resultcode = conn.getResponseCode();
				Log.d("hihig", "connect Server response code : " + resultcode);
				if (conn.getResponseCode() == HttpURLConnection.HTTP_OK) {
					BufferedReader br = new BufferedReader(
							new InputStreamReader(conn.getInputStream()));
					for (;;) {
						String line = br.readLine();
						if (line == null) break;
						html.append(line + '\n'); 
					}
					br.close();
				}
				conn.disconnect();
			}
		} 
		catch (Exception ex) {
			Log.i("error",ex.getMessage());
			
			return ex.getMessage();
			//System.out.println(ex.getMessage());
			}
		return html.toString();
	}
    
    public static void trustAllHosts() { 
        // Create a trust manager that does not validate certificate chains 
        TrustManager[] trustAllCerts = new TrustManager[] { new X509TrustManager() { 
                public java.security.cert.X509Certificate[] getAcceptedIssuers() { 
                        return new java.security.cert.X509Certificate[] {}; 
                } 
 
                @Override 
                public void checkClientTrusted( 
                        java.security.cert.X509Certificate[] chain, 
                        String authType) 
                        throws java.security.cert.CertificateException { 
                    // TODO Auto-generated method stub 
                     
                } 
 
                @Override 
                public void checkServerTrusted( 
                        java.security.cert.X509Certificate[] chain, 
                        String authType) 
                        throws java.security.cert.CertificateException { 
                    // TODO Auto-generated method stub 
                     
                } 
        } }; 
 
        // Install the all-trusting trust manager 
        try { 
                SSLContext sc = SSLContext.getInstance("TLS"); 
                sc.init(null, trustAllCerts, new java.security.SecureRandom()); 
                HttpsURLConnection 
                                .setDefaultSSLSocketFactory(sc.getSocketFactory()); 
        } catch (Exception e) { 
                e.printStackTrace(); 
        } 
    } 
     
    final static HostnameVerifier DO_NOT_VERIFY = new HostnameVerifier() { 
        
		@Override
		public boolean verify(String arg0, SSLSession arg1) {
			// TODO Auto-generated method stub
			return true;
		} 
    }; 
	
    
}

