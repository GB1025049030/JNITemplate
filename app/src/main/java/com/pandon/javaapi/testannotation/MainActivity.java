package com.pandon.javaapi.testannotation;

import android.annotation.SuppressLint;
import android.os.Bundle;
import android.os.Environment;

import androidx.appcompat.app.AppCompatActivity;

import com.pandon.jnilib.NativeLib;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        try {
            File file = new File(getExternalFilesDir(Environment.DIRECTORY_DOCUMENTS), "DemoFile.jpg");
            @SuppressLint("ResourceType") InputStream is = getResources().openRawResource(R.drawable.ic_launcher_foreground);
            OutputStream os = new FileOutputStream(file);
            byte[] data = new byte[is.available()];
            is.read(data);
            os.write(data);
            is.close();
            os.close();
        } catch (IOException e) {
            e.printStackTrace();
        }

        NativeLib.nativeInit();
    }
}