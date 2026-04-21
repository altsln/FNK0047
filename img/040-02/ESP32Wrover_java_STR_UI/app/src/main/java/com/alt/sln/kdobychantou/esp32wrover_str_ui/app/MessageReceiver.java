package com.alt.sln.kdobychantou.esp32wrover_str_ui.app;


import android.os.Handler;
import android.os.Looper;
import android.util.Log;

import java.io.BufferedReader;
import java.io.DataInputStream;
import java.io.InputStreamReader;
import java.net.Socket;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;

public class MessageReceiver {

    private static String TAG = MessageReceiver .class.toString();
    //private boolean isRunning = false;

    // Interface to send data back to your Activity
    public interface OnStrMsgReceivedListener {
        void onMsgReceived(String message);
        void onError(String message);
    }

    public void startListening(String ip, int port, OnStrMsgReceivedListener listener) {
        //isRunning = true;

        // Start a background thread (Replaces CoroutineScope)
        new Thread(() -> {
            try (Socket socket = new Socket(ip, port);
                 BufferedReader reader = new BufferedReader(new InputStreamReader(socket.getInputStream()))) {

                String line;
                while ((line = reader.readLine()) != null) {
                    final String message = line;

                    Log.d(TAG, "data= " + message);     //log data
                    // Switch to Main Thread to update UI (Replaces withContext(Dispatchers.Main))
                    new Handler(Looper.getMainLooper()).post(() -> {
                        if (listener != null) listener.onMsgReceived(message);
                    });
                }

            } catch (Exception e) {
                new Handler(Looper.getMainLooper()).post(() -> {
                    if (listener != null) listener.onError(e.getMessage());
                });
            }
        }).start();
    }

    public void stop() {
//        isRunning = false;
    }
}