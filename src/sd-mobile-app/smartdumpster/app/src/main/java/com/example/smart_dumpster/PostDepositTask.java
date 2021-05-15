package com.example.smart_dumpster;

import android.os.AsyncTask;
import android.util.Log;

import com.example.smart_dumpster.utils.C;

import org.json.JSONException;

import java.io.BufferedOutputStream;
import java.io.IOException;
import java.io.OutputStream;
import java.net.HttpURLConnection;
import java.net.MalformedURLException;
import java.net.URL;

public class PostDepositTask extends AsyncTask<String, Integer, String> {
    @Override
    protected String doInBackground(String... strings) {
        String response = "";
        URL url = null;
        HttpURLConnection urlConnection = null;
        try {
            url = new URL(C.SERVER_URL_POST);
        } catch (MalformedURLException e) {
            e.printStackTrace();
        }
        try {
            urlConnection = (HttpURLConnection) url.openConnection();
            urlConnection.setDoOutput(true);
            urlConnection.setChunkedStreamingMode(0);
            urlConnection.setRequestProperty( "Content-Type", "application/json");

            OutputStream out = new BufferedOutputStream(urlConnection.getOutputStream());
            C.Utils.writeStream(out);

            response = urlConnection.getResponseMessage();
        } catch (IOException | JSONException e) {
            e.printStackTrace();
        } finally {
            urlConnection.disconnect();
        }

        Log.d(C.APP_LOG_TAG, "RESPONSE: " + response);
        return response;
    }
}
