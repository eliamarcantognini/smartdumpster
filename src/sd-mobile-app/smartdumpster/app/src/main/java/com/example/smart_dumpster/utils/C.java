package com.example.smart_dumpster.utils;

import android.util.Log;

import org.json.JSONException;
import org.json.JSONObject;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.util.Random;

public class C {

    public static final String APP_LOG_TAG = "BT_SD";
    public static final String END_DEPOSIT = "n";
    public static final String A = "A";
    public static final String B = "B";
    public static final String C = "C";
    public static final String MORE_TIME = "t";
    public static final String SECOND = "s";
    public static final String NOT_CONNECTED = "Bluetooth not connected";
    public static final String CONNECTED = "Bluetooth Connected";
    public static final String NO_TIME = "--";
    public static final String SERVER_URL_GET = "http://192.168.1.15:3000/api/v1/token";
    public static final String SERVER_URL_POST = "http://192.168.1.15:3000/api/v1/deposits";
    public static final String AVAILABLE = "SD Available";
    public static final String NOT_AVAILABLE = "SD Not Available";

    public class bluetooth {
        public static final int ENABLE_BT_REQUEST = 1;
        public static final String BT_DEVICE_ACTING_AS_SERVER_NAME = "mrc";
    }

    public static class Utils {
        public static String readStream(InputStream is) {

            BufferedReader reader = new BufferedReader(new InputStreamReader(is));
            StringBuilder sb = new StringBuilder();

            String line = null;
            try {
                while ((line = reader.readLine()) != null) {
                    sb.append(line + "\n");
                }
            } catch (IOException e) {
                Log.e(APP_LOG_TAG, "IOException", e);
            } finally {
                try {
                    is.close();
                } catch (IOException e) {
                    Log.e(APP_LOG_TAG, "IOException", e);
                }
            }
            return sb.toString();
        }

        public static void writeStream(OutputStream out) throws IOException, JSONException {
            JSONObject quantity = new JSONObject().put("quantity", String.valueOf(getRandomQuantity()));
            String output = quantity.toString();
            out.write(output.getBytes());
            out.flush();
        }

        public static int getRandomQuantity() {
            return new Random().nextInt(10) + 1;
        }
    }

}
