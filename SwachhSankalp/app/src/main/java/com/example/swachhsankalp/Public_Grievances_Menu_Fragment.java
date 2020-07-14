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
import android.widget.TextView;


public class Public_Grievances_Menu_Fragment extends Fragment {

    private TextView public_grievance;

    @Nullable
    @Override
    public View onCreateView(@NonNull LayoutInflater inflater, @Nullable ViewGroup container, @Nullable Bundle savedInstanceState) {
        View inflate = inflater.inflate(R.layout.fragment_public__grievances__menu_, container, false);

        public_grievance = inflate.findViewById(R.id.tv_public_grievance);

        public_grievance.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {

                Intent mailIntent = new Intent(Intent.ACTION_VIEW);
                Uri data = Uri.parse("mailto:?subject=" + "Public Grievance through Swachh Sankalp App"+ "&body=" + "Add your Grievance/suggestion/feedback below this line:" + "&to=" + "info@swachhsankalp.com");
                mailIntent.setData(data);
                startActivity(Intent.createChooser(mailIntent, "Send mail..."));

            }
        });

        return inflate;
    }
}