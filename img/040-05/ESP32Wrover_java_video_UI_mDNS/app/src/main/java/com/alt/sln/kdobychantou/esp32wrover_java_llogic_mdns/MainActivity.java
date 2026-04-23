package com.alt.sln.kdobychantou.esp32wrover_java_llogic_mdns;

import android.os.Bundle;

import androidx.activity.EdgeToEdge;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.graphics.Insets;
import androidx.core.view.ViewCompat;
import androidx.core.view.WindowInsetsCompat;

import android.graphics.Bitmap;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.view.WindowManager;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.TextView;
import android.widget.Toast;

import com.alt.sln.kdobychantou.esp32wrover_java_llogic_mdns.app.NetworkSettings;
import com.alt.sln.kdobychantou.esp32wrover_java_llogic_mdns.app.VideoReceiver;
import com.alt.sln.kdobychantou.esp32wrover_java_llogic_mdns.app.mdns.DiscoveryManager;


public class MainActivity extends AppCompatActivity {

    private static String TAG = MainActivity .class.toString();
    private ImageView cameraFrameView;
    private TextView sizeText;
    private Button btnConnect;
    private VideoReceiver receiver;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        EdgeToEdge.enable(this);
        setContentView(R.layout.activity_main);
        ViewCompat.setOnApplyWindowInsetsListener(findViewById(R.id.main), (v, insets) -> {
            Insets systemBars = insets.getInsets(WindowInsetsCompat.Type.systemBars());
            v.setPadding(systemBars.left, systemBars.top, systemBars.right, systemBars.bottom);
            return insets;
        });

        //keep screen active for the video.
        getWindow().addFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);

        btnConnect = findViewById(R.id.btn_connect);
        sizeText = findViewById(R.id.tv_img_size);
        cameraFrameView = findViewById(R.id.camera_frame_view);

        receiver = new VideoReceiver();
        // Set the listener
        VideoReceiver.OnVideoReceivedListener videoListener = new VideoReceiver.OnVideoReceivedListener() {
            @Override
            public void onImgReceived(int ingSize, Bitmap bitmap) {
                //sizeText.setText("img Size: " + ingSize);
                // This must happen on the Main Thread
                cameraFrameView.setImageBitmap(bitmap);
            }

            @Override
            public void onStatusUpdate(String fps) {
                //Log.d(TAG, fps);
                sizeText.setText(fps);
            }

            @Override
            public void onError(String message) {
                Log.e(TAG, "NETWORK - Error: " + message);
            }
        };


/*
        receiver.startVideoListening(NetworkSettings.IP_ADDR,
                NetworkSettings.PORT_NUMBER,

        );
*/

        DiscoveryManager discoveryManager =
                new DiscoveryManager(this, new DiscoveryManager.OnDeviceFoundListener() {
            @Override
            public void onDeviceFound(String ip, int port) {
                // Now you have the dynamic IP! Start the video
                Log.d(TAG, "ipAdr= " + ip);
                runOnUiThread(() -> {
                    Toast.makeText(MainActivity.this, "Found ESP32 at " + ip, Toast.LENGTH_SHORT).show();
                    receiver.startVideoListening(ip, port, videoListener);
                });
            }

            @Override
            public void onError(String message) {
                Log.e("Discovery", message);
            }
        });



        btnConnect.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                // Your callback logic here
                Toast.makeText(MainActivity.this, "Button Clicked!", Toast.LENGTH_SHORT).show();

// Call this when the user clicks a "Scan" or "Connect" button
                Log.d(TAG, "Start discovery");
                discoveryManager.startDiscovery(getApplicationContext());

            }
        });

    }


    @Override
    protected void onDestroy() {
        super.onDestroy();
        receiver.stop();
    }
}

