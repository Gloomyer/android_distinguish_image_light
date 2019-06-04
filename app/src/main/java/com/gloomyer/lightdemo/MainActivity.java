package com.gloomyer.lightdemo;

import android.Manifest;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.Environment;
import android.support.v4.app.ActivityCompat;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.ImageView;

import java.io.File;

public class MainActivity extends AppCompatActivity {

    private static final String TAG = "MainActivity";

    static {
        System.loadLibrary("libimg");
    }

    private ImageView iv;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        ActivityCompat.requestPermissions(this, new String[]{Manifest.permission.READ_EXTERNAL_STORAGE}, 123);
        iv = findViewById(R.id.iv);
    }


    public native int getLight(Bitmap bitmap);

    public boolean isLight(Bitmap bitmap) {
        return getLight(bitmap) > 128;
    }

    public void load(View view) {
//        Bitmap bitmap = BitmapFactory.decodeResource(getResources(), R.drawable.demo);
        Bitmap bitmap = BitmapFactory.decodeFile(new File(Environment.getExternalStorageDirectory(), "black.jpeg").getAbsolutePath());
        if (bitmap == null) {
            Log.e(TAG, "bitmap  == null");
            return;
        }
        Log.e(TAG, "is light:" + isLight(bitmap));
        iv.setImageBitmap(bitmap);
    }
}
