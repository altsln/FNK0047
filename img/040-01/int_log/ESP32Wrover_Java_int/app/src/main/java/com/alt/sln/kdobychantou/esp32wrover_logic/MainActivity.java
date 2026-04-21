package com.alt.sln.kdobychantou.esp32wrover_logic;

import android.os.Bundle;

import androidx.activity.EdgeToEdge;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.graphics.Insets;
import androidx.core.view.ViewCompat;
import androidx.core.view.WindowInsetsCompat;

import com.alt.sln.kdobychantou.esp32wrover_logic.app.CounterReceiver;
import com.alt.sln.kdobychantou.esp32wrover_logic.app.NetworkSettings;

public class MainActivity extends AppCompatActivity {

    private CounterReceiver receiver;
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

        receiver = new CounterReceiver();
        receiver.startListening(NetworkSettings.IP_ADDR, NetworkSettings.PORT_NUMBER);

    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        receiver.stop();
    }
}