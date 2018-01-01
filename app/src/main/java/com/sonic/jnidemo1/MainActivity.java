package com.sonic.jnidemo1;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        TextView tv = findViewById(R.id.tv);
        int[] a = new int[]{-4, -85, 30, 25, -54, 4, 65, 32, 2, 11, 25};
        JniUtil jni = new JniUtil();
        tv.setText(jni.getNewStr("hello"));
        Log.e("sum", "=" + jni.getSum(5, 6));
        jni.bubbleSort(a); //由于用到c的指针拿到了数组元素的地址，所以排序后数组本身也发生了变化，可以不用返回值了
        for (int i = 0; i < a.length; i++) {
            Log.e("paixu:",a[i] + "");
        }
    }
}
