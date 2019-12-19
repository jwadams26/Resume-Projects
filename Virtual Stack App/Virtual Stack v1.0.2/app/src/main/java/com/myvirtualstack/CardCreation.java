package com.myvirtualstack;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;

public class CardCreation extends AppCompatActivity {
    private Button createButton;

    private String user;
    private String pass;
    private String myName;
    private String myOccupation;
    private String myAddress;
    private String myPhone;
    private String myEmail;
    private EditText MyName;
    private EditText MyOccupation;
    private EditText MyAddress;
    private EditText MyPhone;
    private EditText MyEmail;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_card_creation);

        // Connecting Buttons
        MyName = findViewById(R.id.myName);
        MyName.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View v)
            {
                MyName.setText("");
            }
        });
        MyOccupation = findViewById(R.id.myCompany);
        MyOccupation.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View v)
            {
                MyOccupation.getText().clear();
            }
        });
        MyAddress = findViewById(R.id.myAddress);
        MyAddress.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View v)
            {
                MyAddress.getText().clear();
            }
        });
        MyPhone = findViewById(R.id.myPersPhone);
        MyPhone.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View v)
            {
                MyPhone.getText().clear();
            }
        });
        MyEmail = findViewById(R.id.myEmail);
        MyEmail.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View v)
            {
                MyEmail.setText("");
            }
        });
        createButton = findViewById(R.id.createBtn);

        // Action Listeners
        createButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                // COLLECTING INFO FROM LAST PAGE
                Bundle bundleTrain = getIntent().getExtras();

                user = bundleTrain.getString("USER");
                pass = bundleTrain.getString("PASS");

                // Connecting EditText
                myName = MyName.getText().toString();
                myOccupation = MyOccupation.getText().toString();
                myAddress = MyAddress.getText().toString();
                myPhone = MyPhone.getText().toString();
                myEmail = MyEmail.getText().toString();

                // API MAGIC GOES HERE
                new Thread(new Runnable(){
                    @Override
                    public void run() {
                        try {
                            API example = new API();
                            // makes the body of the http request but it's in string
                            String json = example.formBody(myName, myAddress, myPhone, myEmail, myOccupation);
                            String response = example.signup(user, pass, json);
                            System.out.println(response);
                        }
                        catch (Exception ex) {
                            ex.printStackTrace();
                        }
                    }
                }).start();

                // SETTING UP INTENT
                Intent intentTrain = new Intent(CardCreation.this, LandingPage.class);
                Bundle extra = new Bundle();

                extra.putString("NAME", myName);
                extra.putString("OCCUPATION", myOccupation);
                extra.putString("ADDRESS", myAddress);
                extra.putString("NUMBER", myPhone);
                extra.putString("EMAIL", myEmail);

                intentTrain.putExtras(extra);

                startActivity(intentTrain);
                finish();
            }
        });
    }
}