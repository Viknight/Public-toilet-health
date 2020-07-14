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
import android.webkit.WebSettings;
import android.webkit.WebView;
import android.webkit.WebViewClient;
import android.widget.Button;

public class Press_Releases_Menu_Fragment extends Fragment {
    private WebView webView;

    private Button btn_Prss_Releases;

    @Nullable
    @Override
    public View onCreateView(@NonNull LayoutInflater inflater, @Nullable ViewGroup container, @Nullable Bundle savedInstanceState) {
        View inflate = inflater.inflate(R.layout.fragment_press__releases__menu_, container, false);

        Button press_release = (Button)inflate.findViewById(R.id.btn_Press_Releases);

        press_release.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {

                Intent in = new Intent(getActivity(), Press_Releases_WebView.class);
                in.putExtra("some", "Proceed Further");
                startActivity(in);
            }
        });

        return inflate;
    }


}