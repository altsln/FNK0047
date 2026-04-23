package com.alt.sln.kdobychantou.esp32wrover_java_llogic_mdns.app;


import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.Handler;
import android.os.Looper;
import android.util.Log;

import java.io.DataInputStream;
import java.net.Socket;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;


public class VideoReceiver {

    private static String TAG = VideoReceiver .class.toString();
    private volatile boolean isRunning = false; // Use volatile for thread safety
    private int frameCount = 0;
    private long lastTime = System.currentTimeMillis();

    private Bitmap reusableBitmap = null;
    private BitmapFactory.Options options = new BitmapFactory.Options();

    // Interface to send data back to your Activity
    public interface OnVideoReceivedListener {
        void onImgReceived(int ingSize, Bitmap bitmap);
        void onStatusUpdate(String fps);
        void onError(String message);
    }

    public void startVideoListening(String ip, int port, OnVideoReceivedListener listener) {
        isRunning = true;

        // Start a background thread (Replaces CoroutineScope)
        new Thread(() -> {
            try (Socket socket = new Socket(ip, port);
                 DataInputStream dis = new DataInputStream(socket.getInputStream())) {
                Log.d(TAG, "Connected to ESP32 Image Server");

                while (isRunning) {

                    // 1. Read Image Size (4 bytes, Little Endian)
                    byte[] sizeBuffer = new byte[4];
                    dis.readFully(sizeBuffer);
                    int imgSize = ByteBuffer.wrap(sizeBuffer).order(ByteOrder.LITTLE_ENDIAN).getInt();

                    // Sanity check: JPEG frames for ESP32 are usually < 100KB.
                    // This prevents crashes if we get a garbage number.
                    if ((imgSize > 0) && (imgSize < 1000000)) {
                        // 2. Read the actual Image Bytes
                        byte[] imgBytes = new byte[imgSize];
                        dis.readFully(imgBytes);
//                        Log.d(TAG, "image size: " + imgSize);

                        // Setup reuse options
                        if (reusableBitmap != null) {
                            options.inBitmap = reusableBitmap;
                        }
                        options.inMutable = true;
                        options.inSampleSize = 1; // 1:1 scale

                        // 3. Convert to Bitmap and send to UI
                        Bitmap decodedBitmap;
                        try {
                            //This will decode INTO the reusableBitmap if possible
                            decodedBitmap = BitmapFactory.decodeByteArray(imgBytes, 0, imgBytes.length, options);
                            if (decodedBitmap != null) {
                                reusableBitmap = decodedBitmap; // Keep track for the next frame

                                handleFPS(listener);
                                new Handler(Looper.getMainLooper()).post(() -> {
                                    listener.onImgReceived(imgSize, decodedBitmap);
                                });
                            }
                        } catch (IllegalArgumentException e) {
                            // This happens if the new image size changed (e.g., QVGA to VGA)
                            // Clear it so the next frame creates a fresh bitmap
                            reusableBitmap = null;
                            Log.e(TAG, "Bitmap size changed, resetting pool");
                            new Handler(Looper.getMainLooper()).post(() -> {
                                if (listener != null) listener.onError(e.getMessage());
                            });
                        }
                    }
                }

            } catch (Exception e) {
                if (isRunning) { // Only report error if we didn't stop it ourselves
                    new Handler(Looper.getMainLooper()).post(() -> {
                        if (listener != null) listener.onError(e.getMessage());
                    });
                }
            }
        }).start();
    }

    private void handleFPS(OnVideoReceivedListener listener) {
        //
        frameCount++;
        long currentTime = System.currentTimeMillis();
        if ((currentTime - lastTime) >= 1000) { // Every 1 second
            double fps = (frameCount * 1000.0) / (currentTime - lastTime);
            Log.d("FPS_MONITOR", String.format("Current FPS: %.2f", fps));
            // Optional: Pass this back to UI to show on screen
            new Handler(Looper.getMainLooper()).post(() -> {
                if (null != listener) {listener.onStatusUpdate("FPS: " + (int)fps);}
            });

            frameCount = 0;
            lastTime = currentTime;
        }
    }

    public void stop() {
        isRunning = false;
        // The socket will close automatically when the try-with-resources block exits
    }
}
