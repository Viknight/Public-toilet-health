package com.example.swachhsankalp;

import android.content.Intent;
import android.net.Uri;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageView;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.fragment.app.Fragment;

public class Suggestion_Menu_Fragment extends Fragment {

    ImageView Suggestion_clickable_image;

    @Nullable
    @Override
    public View onCreateView(@NonNull LayoutInflater inflater, @Nullable ViewGroup container, @Nullable Bundle savedInstanceState) {
        View inflate = inflater.inflate(R.layout.fragment_suggestion_menu, container, false);

        Suggestion_clickable_image = (ImageView) inflate.findViewById(R.id.Suggestion_clickable_image);

        Suggestion_clickable_image.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                sendMail();
            }
        });

        return inflate;
    }

    private void sendMail() {

        Intent mailIntent = new Intent(Intent.ACTION_VIEW);
        Uri data = Uri.parse("mailto:?subject=" + "Suggestion/Feedback for Swachh Sankalp Android App"+ "&body=" + "Type your Suggestions/Feedbacks below this line: " + "&to=" + "varunyadav155@gmail.com,t.c.sangle@gmail.com");
        mailIntent.setData(data);
        startActivity(Intent.createChooser(mailIntent, "Send mail..."));
        }

    }
