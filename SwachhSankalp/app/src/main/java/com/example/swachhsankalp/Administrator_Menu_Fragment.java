package com.example.swachhsankalp;

import android.content.Context;
import android.content.Intent;
import android.net.Uri;
import android.os.Bundle;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.fragment.app.Fragment;

import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;


public class Administrator_Menu_Fragment extends Fragment {

    private Button btn_Administrator;

    @Nullable
    @Override
    public View onCreateView(@NonNull LayoutInflater inflater, @Nullable ViewGroup container, @Nullable Bundle savedInstanceState) {
        View inflate = inflater.inflate(R.layout.fragment_administrator__menu_, container, false);

        btn_Administrator = (Button)inflate.findViewById(R.id.btn_Administrator_login_fragment_to_activity);

        btn_Administrator.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {

                Intent adminIntent = new Intent(getActivity(), Administrator_Login.class);
                startActivity(adminIntent);

            }
        });
        return inflate;
    }
}