package com.alt.sln.kdobychantou.esp32wrover_logic_ui.app;

import android.os.Handler;
import android.os.Looper;
import java.io.DataInputStream;
import java.net.Socket;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;

public class CounterReceiver {

    private boolean isRunning = false;

    // Interface to send data back to your Activity
    public interface OnCounterReceivedListener {
        void onCounterReceived(int count);
        void onError(String message);
    }

    public void startListening(String ip, int port, OnCounterReceivedListener listener) {
        isRunning = true;

        // Start a background thread (Replaces CoroutineScope)
        new Thread(() -> {
            try (Socket socket = new Socket(ip, port);
                 DataInputStream inputStream = new DataInputStream(socket.getInputStream())) {

                while (isRunning) {
                    // ESP32/C++ typically sends Little-Endian
                    byte[] bytes = new byte[4];
                    inputStream.readFully(bytes);
                    int counter = ByteBuffer.wrap(bytes)
                            .order(ByteOrder.LITTLE_ENDIAN)
                            .getInt();

                    // Switch to Main Thread to update UI (Replaces withContext(Dispatchers.Main))
                    new Handler(Looper.getMainLooper()).post(() -> {
                        if (listener != null) listener.onCounterReceived(counter);
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
        isRunning = false;
    }
}