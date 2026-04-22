package com.alt.sln.kdobychantou.esp32wrover_logic_vid;

import android.graphics.Bitmap;
import android.os.Bundle;
import android.util.Log;
import android.widget.ImageView;
import android.widget.TextView;

import androidx.activity.EdgeToEdge;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.graphics.Insets;
import androidx.core.view.ViewCompat;
import androidx.core.view.WindowInsetsCompat;

import com.alt.sln.kdobychantou.esp32wrover_logic_vid.app.NetworkSettings;
import com.alt.sln.kdobychantou.esp32wrover_logic_vid.app.VideoReceiver;

public class MainActivity extends AppCompatActivity {

    private static String TAG = MainActivity .class.toString();
    private ImageView cameraFrameView;
    private TextView sizeText;
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

        sizeText = findViewById(R.id.tv_img_size);
        cameraFrameView = findViewById(R.id.camera_frame_view);

        receiver = new VideoReceiver();
        // Start the listener

        receiver.startVideoListening(NetworkSettings.IP_ADDR,
                NetworkSettings.PORT_NUMBER,
                new VideoReceiver.OnVideoReceivedListener() {
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
                });

    }


    @Override
    protected void onDestroy() {
        super.onDestroy();
        receiver.stop();
    }
}

