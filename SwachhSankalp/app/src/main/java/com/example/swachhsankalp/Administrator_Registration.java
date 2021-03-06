package com.example.swachhsankalp;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.text.TextUtils;
import android.util.Log;
import android.view.View;
import android.widget.EditText;
import android.widget.ProgressBar;
import android.widget.Toast;

import com.google.android.gms.tasks.OnCompleteListener;
import com.google.android.gms.tasks.Task;
import com.google.firebase.auth.AuthResult;
import com.google.firebase.auth.FirebaseAuth;

public class Administrator_Registration extends AppCompatActivity {

    private EditText inputEmail, inputPassword, inputUsername;
    private ProgressBar progressBar;

    private FirebaseAuth mAuth;

    private String userId;
    private String email;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_administrator__registration);

        //Get Firebase instances
        mAuth = FirebaseAuth.getInstance();

        // if already logged in go sign in screen
        if (mAuth.getCurrentUser() != null) {
            startActivity(new Intent(this, Administrator_Homepage.class));
            finish();
        }

        inputEmail =  findViewById(R.id.email);
        inputPassword =  findViewById(R.id.password);
        inputUsername =  findViewById(R.id.username);
        progressBar =  findViewById(R.id.progressBar);
    }

    @Override
    protected void onResume() {
        super.onResume();
        progressBar.setVisibility(View.GONE);
    }

    public void onRegisterClicked(View view) {
        String emailInput = inputEmail.getText().toString().trim();
        String password = inputPassword.getText().toString().trim();
        final String username = inputUsername.getText().toString().trim();

        if (TextUtils.isEmpty(username)) {
            Toast.makeText(getApplicationContext(), "Enter username!", Toast.LENGTH_SHORT).show();
            return;
        }

        if (TextUtils.isEmpty(emailInput)) {
            Toast.makeText(getApplicationContext(), "Enter email address!", Toast.LENGTH_SHORT).show();
            return;
        }

        if (TextUtils.isEmpty(password)) {
            Toast.makeText(getApplicationContext(), "Enter password!", Toast.LENGTH_SHORT).show();
            return;
        }

        if (password.length() < 6) {
            Toast.makeText(getApplicationContext(), "Password too short, enter minimum 6 characters!", Toast.LENGTH_SHORT).show();
            return;
        }

        progressBar.setVisibility(View.VISIBLE);
        //create user
        mAuth.createUserWithEmailAndPassword(emailInput, password)
                .addOnCompleteListener(Administrator_Registration.this, new OnCompleteListener<AuthResult>() {
                    @Override
                    public void onComplete(@NonNull Task<AuthResult> task) {
                        Toast.makeText(Administrator_Registration.this, "createUserWithEmail:onComplete:" + task.isSuccessful(), Toast.LENGTH_SHORT).show();
                        progressBar.setVisibility(View.GONE);
                        // If sign in fails, display a message to the user. If sign in succeeds
                        // the auth state listener will be notified and logic to handle the
                        // signed in user can be handled in the listener.
                        if (!task.isSuccessful()) {
                            Toast.makeText(Administrator_Registration.this, "Authentication failed." + task.getException(),
                                    Toast.LENGTH_LONG).show();
                            Log.e("MyTag", task.getException().toString());
                        } else {

                            startActivity(new Intent(Administrator_Registration.this, Administrator_Homepage.class));
                            finish();
                        }
                    }
                });
    }

    public void onLoginClicked(View view) {
        startActivity(new Intent(this, Administrator_Login.class));
    }
}
