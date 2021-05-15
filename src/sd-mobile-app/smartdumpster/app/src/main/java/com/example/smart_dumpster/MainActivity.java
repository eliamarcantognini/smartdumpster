package com.example.smart_dumpster;

import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.TextView;
import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;

import com.example.smart_dumpster.R.layout;
import com.example.smart_dumpster.utils.C;
import com.example.smart_dumpster.utils.C.bluetooth;

import java.util.UUID;

import unibo.btlib.BluetoothChannel;
import unibo.btlib.BluetoothUtils;
import unibo.btlib.ConnectToBluetoothServerTask;
import unibo.btlib.ConnectionTask;
import unibo.btlib.RealBluetoothChannel;
import unibo.btlib.exceptions.BluetoothDeviceNotFound;

import static com.example.smart_dumpster.R.*;

public class MainActivity extends AppCompatActivity implements GetTokenTask.GetMyTaskListener {

    private BluetoothChannel btChannel;
    private GetTokenTask getTask;
    private PostDepositTask postTask;
    private String token;

    @Override
    protected void onCreate(final Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(layout.activity_main);
        getTask = new GetTokenTask(this);
        postTask = new PostDepositTask();
        this.token = "";
        getTask.execute();

        final BluetoothAdapter btAdapter = BluetoothAdapter.getDefaultAdapter();

        if (btAdapter != null && !btAdapter.isEnabled()) {
            startActivityForResult(new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE), bluetooth.ENABLE_BT_REQUEST);
        }
        initUI();
    }

    @Override
    public void onGetMyTaskComplete(String response) {
        this.token = response;
    }

    @Override
    protected void onStop() {
        super.onStop();
        btChannel.close();
    }

    @Override
    protected void onActivityResult(final int requestCode, final int resultCode, @Nullable final Intent data) {
        if(requestCode == C.bluetooth.ENABLE_BT_REQUEST && resultCode == RESULT_OK){
            Log.d(C.APP_LOG_TAG, "Bluetooth enabled!");
        }
        if(requestCode == C.bluetooth.ENABLE_BT_REQUEST && resultCode == RESULT_CANCELED){
            Log.d(C.APP_LOG_TAG, "Bluetooth not enabled!");
        }
    }

    private void initUI() {
        ((TextView) findViewById(id.availableTxt)).setText(C.NOT_CONNECTED);
        findViewById(id.btnA).setEnabled(false);
        findViewById(id.btnB).setEnabled(false);
        findViewById(id.btnC).setEnabled(false);
        findViewById(id.moreTimeBtn).setEnabled(false);
        findViewById(id.checkBtn).setOnClickListener(v -> checkDumpsterStatus());
        findViewById(id.connectBtn).setOnClickListener((v) -> {
            try {
                connectToBTServer();
            } catch (BluetoothDeviceNotFound bluetoothDeviceNotFound) {
                bluetoothDeviceNotFound.printStackTrace();
            }
        });

        findViewById(id.btnA).setOnClickListener((v) -> {
            if (isDumpsterAvailable()) {
                String message = C.A;
                btChannel.sendMessage(message);
                startDeposit();
            } else {
                notAvailable();
            }
        });
        findViewById(id.btnB).setOnClickListener((v) -> {
            if (isDumpsterAvailable()) {
                String message = C.B;
                btChannel.sendMessage(message);
                startDeposit();
            } else {
                notAvailable();
            }
        });
        findViewById(id.btnC).setOnClickListener((v) -> {
            if (isDumpsterAvailable()) {
                String message = C.C;
                btChannel.sendMessage(message);
                startDeposit();
            } else {
                notAvailable();
            }
        });
        findViewById(id.moreTimeBtn).setOnClickListener((v) -> {
            if (isDumpsterAvailable()) {
                String message = C.MORE_TIME;
                btChannel.sendMessage(message);
            }
        });
    }

    private void connectToBTServer() throws BluetoothDeviceNotFound {
        final BluetoothDevice serverDevice = BluetoothUtils.getPairedDeviceByName(C.bluetooth.BT_DEVICE_ACTING_AS_SERVER_NAME);
        final UUID uuid = BluetoothUtils.getEmbeddedDeviceDefaultUuid();

        if (isDumpsterAvailable()) {
            available();
            new ConnectToBluetoothServerTask(serverDevice, uuid, new ConnectionTask.EventListener() {
                @Override
                public void onConnectionActive(final BluetoothChannel channel) {
                    enableDepositButtons();
                    ((TextView) findViewById(id.availableTxt)).setText(C.CONNECTED + " to " + serverDevice.getName());
                    btChannel = channel;
                    btChannel.registerListener(new RealBluetoothChannel.Listener() {
                        @Override
                        public void onMessageReceived(String receivedMessage) {
                            if (receivedMessage.trim().equals(C.END_DEPOSIT)) {
                                ((TextView) findViewById(id.timeTxt)).setText(C.NO_TIME);
                                resetButtons();
                                postDepositOnServer();
                            } else {
                                ((TextView) findViewById(id.timeTxt)).setText(receivedMessage.trim() + C.SECOND);
                            }
                        }
                        @Override
                        public void onMessageSent(String sentMessage) {}
                    });
                }

                @Override
                public void onConnectionCanceled() {
                    initUI();
                }
            }).execute();
        } else {
            ((TextView) findViewById(id.token)).setText(C.NOT_AVAILABLE);
        }

    }

    private void renewToken() {
        getTask = new GetTokenTask(this);
        getTask.execute();
    }

    private void resetButtons() {
        if (isDumpsterAvailable()) {
            available();
            enableDepositButtons();
        } else {
            notAvailable();
        }
    }

    private void notAvailable() {
        findViewById(id.btnA).setEnabled(false);
        findViewById(id.btnB).setEnabled(false);
        findViewById(id.btnC).setEnabled(false);
        findViewById(id.moreTimeBtn).setEnabled(false);
        findViewById(id.connectBtn).setEnabled(false);
        ((TextView) findViewById(id.timeTxt)).setText(C.NO_TIME);
        findViewById(id.checkBtn).setVisibility(View.VISIBLE);
        ((TextView) findViewById(id.token)).setText(C.NOT_AVAILABLE);
    }

    private void available() {
        ((TextView) findViewById(id.token)).setText(C.AVAILABLE);
        findViewById(id.checkBtn).setVisibility(View.INVISIBLE);
    }

    private void enableDepositButtons() {
        findViewById(id.btnA).setEnabled(true);
        findViewById(id.btnB).setEnabled(true);
        findViewById(id.btnC).setEnabled(true);
        findViewById(id.moreTimeBtn).setEnabled(false);
        findViewById(id.connectBtn).setEnabled(false);
    }

    private void startDeposit() {
        findViewById(id.btnA).setEnabled(false);
        findViewById(id.btnB).setEnabled(false);
        findViewById(id.btnC).setEnabled(false);
        findViewById(id.moreTimeBtn).setEnabled(true);
    }

    private boolean isDumpsterAvailable() {
        renewToken();
        return token.equals("\"\"") ? false : true;
    }

    private void checkDumpsterStatus() {
        if (isDumpsterAvailable()) {
            available();
            enableDepositButtons();
        }
    }

    private void postDepositOnServer() {
        postTask.execute();
        postTask = new PostDepositTask();
    }


}
