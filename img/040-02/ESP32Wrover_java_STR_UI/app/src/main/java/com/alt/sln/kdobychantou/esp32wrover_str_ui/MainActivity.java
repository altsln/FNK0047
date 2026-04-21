package com.alt.sln.kdobychantou.esp32wrover_str_ui;

import android.os.Bundle;

import android.util.Log;
import android.widget.TextView;

import androidx.activity.EdgeToEdge;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.graphics.Insets;
import androidx.core.view.ViewCompat;
import androidx.core.view.WindowInsetsCompat;

import com.alt.sln.kdobychantou.esp32wrover_str_ui.app.MessageReceiver;
import com.alt.sln.kdobychantou.esp32wrover_str_ui.app.NetworkSettings;

public class MainActivity extends AppCompatActivity {

    private TextView msgText;
    private MessageReceiver receiver;

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
        msgText = findViewById(R.id.tv_msg);
        receiver = new MessageReceiver();
        // Start the listener
        receiver.startListening(NetworkSettings.IP_ADDR,
                NetworkSettings.PORT_NUMBER,
                new MessageReceiver.OnStrMsgReceivedListener() {
                    @Override
                    public void onMsgReceived(String message) {
                        msgText.setText("Msg: " + message);
                    }

                    @Override
                    public void onError(String message) {
                        Log.e("NETWORK", "Error: " + message);
                    }
                });
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        receiver.stop();
    }

}