package com.example.smart_dumpster;

import android.os.AsyncTask;

import com.example.smart_dumpster.utils.C;

import java.io.BufferedInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.net.HttpURLConnection;
import java.net.MalformedURLException;
import java.net.URL;

public class GetTokenTask extends AsyncTask<String, Integer, String> {

    public interface GetMyTaskListener {
        void onGetMyTaskComplete(String response);
    }

    private GetMyTaskListener listener;


    public GetTokenTask(GetMyTaskListener listener) {
        this.listener = listener;
    }

    protected String doInBackground(String... urls) {
        String token = "";
        URL url = null;
        HttpURLConnection urlConnection = null;
        try {
            url = new URL(C.SERVER_URL_GET);
        } catch (MalformedURLException e) {
            e.printStackTrace();
        }
        try {
            urlConnection = (HttpURLConnection) url.openConnection();
            InputStream in = new BufferedInputStream(urlConnection.getInputStream());
            token = C.Utils.readStream(in);
        } catch (IOException e) {
            e.printStackTrace();
        } finally {
            if (urlConnection != null) urlConnection.disconnect();
        }
        return token.trim();
    }

    protected void onProgressUpdate(Integer... progress) {
    }

    protected void onPostExecute(String result) {
        listener.onGetMyTaskComplete(result);
    }
}
