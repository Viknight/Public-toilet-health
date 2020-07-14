package com.example.swachhsankalp;

import android.content.Intent;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.fragment.app.Fragment;

public class Share_Menu_Fragment extends Fragment {

    Button btn_share_app;


    @Nullable
    @Override
    public View onCreateView(@NonNull LayoutInflater inflater, @Nullable ViewGroup container, @Nullable Bundle savedInstanceState) {
        View inflate = inflater.inflate(R.layout.fragment_share_menu, container, false);

        btn_share_app = (Button) inflate.findViewById(R.id.btn_share_app);

        btn_share_app.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {

                Intent shareIntent = new Intent(Intent.ACTION_SEND);
                shareIntent.setType("text/plain");
                String shareBody = "Swachh Sankalp App";
                String shareSub = "Link to Swachh Sankalp App";
                shareIntent.putExtra(Intent.EXTRA_SUBJECT,shareBody);
                shareIntent.putExtra(Intent.EXTRA_TEXT,shareSub);
                startActivity(Intent.createChooser(shareIntent, "Share Using"));
            }
        });

        return inflate;
    }
}
