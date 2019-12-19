package com.myvirtualstack;

import androidx.appcompat.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.Button;
import android.view.View;
import android.content.Intent;
import android.widget.EditText;

public class SignUp extends AppCompatActivity {
    private Button signupBtn;
    private Button returnBtn;
    private EditText user;
    private EditText pass;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_sign_up);

        user = findViewById(R.id.newUser);
        user.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View v)
            {
                user.setText("");
            }
        });

        // Collecting button references
        signupBtn = findViewById(R.id.signBtn2);
        returnBtn = findViewById(R.id.signupRtrnBtn);

        // Action Listeners
        signupBtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                // Collecting EditText references
                Intent intentTrain = new Intent(SignUp.this, CardCreation.class);
                Bundle bundleTrain = new Bundle();

                bundleTrain.putString("USER", user.getText().toString());
                pass = findViewById(R.id.newPass);
                bundleTrain.putString("PASS", pass.getText().toString());

                intentTrain.putExtras(bundleTrain);
                startActivity(intentTrain);
                finish();
            }
        });
        returnBtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                finish();
            }
        });
    }
}
