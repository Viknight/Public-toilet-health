package com.example.swachhsankalp;

import androidx.annotation.NonNull;
import androidx.appcompat.app.ActionBarDrawerToggle;
import androidx.appcompat.app.AppCompatActivity;
import androidx.appcompat.widget.Toolbar;
import androidx.core.view.GravityCompat;
import androidx.drawerlayout.widget.DrawerLayout;

import android.os.Bundle;
import android.view.MenuItem;

import com.google.android.material.navigation.NavigationView;

public class Homepage_Menu extends AppCompatActivity implements NavigationView.OnNavigationItemSelectedListener {
    private DrawerLayout drawer;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_home_page);

        Toolbar toolbar = findViewById(R.id.toolbar);
        setSupportActionBar(toolbar);

        drawer = findViewById(R.id.drawer_layout);

        NavigationView navigationView = findViewById(R.id.nav_view);
        navigationView.setNavigationItemSelectedListener(this);


        ActionBarDrawerToggle toggle = new ActionBarDrawerToggle(this, drawer, toolbar,
                R.string.navigation_draw_open, R.string.navigation_draw_close);
        drawer.addDrawerListener(toggle);
        toggle.syncState();

        if (savedInstanceState == null) {
            getSupportFragmentManager().beginTransaction().replace(R.id.fragment_container,
                    new Homepage_Menu_Fragment()).commit();
            navigationView.setCheckedItem(R.id.nav_Homepage_Menu);

        }
    }

    @Override
    public boolean onNavigationItemSelected(@NonNull MenuItem menuItem) {
        switch (menuItem.getItemId()) {

            case R.id.nav_Homepage_Menu:
                getSupportFragmentManager().beginTransaction().replace(R.id.fragment_container,
                        new Homepage_Menu_Fragment()).commit();
                break;

            case R.id.nav_Administrator_Menu:
                getSupportFragmentManager().beginTransaction().replace(R.id.fragment_container,
                        new Administrator_Menu_Fragment()).commit();
                break;

            case R.id.nav_Cleaners_Portal_Menu:
                getSupportFragmentManager().beginTransaction().replace(R.id.fragment_container,
                        new Cleaners_Menu_Fragment()).commit();
                break;

            case R.id.nav_Public_Grievances_Menu:
                getSupportFragmentManager().beginTransaction().replace(R.id.fragment_container,
                        new Public_Grievances_Menu_Fragment()).commit();
                break;

            case R.id.nav_Press_Releases_Menu:
                getSupportFragmentManager().beginTransaction().replace(R.id.fragment_container,
                        new Press_Releases_Menu_Fragment()).commit();
                break;

            case R.id.nav_About_Menu:
                getSupportFragmentManager().beginTransaction().replace(R.id.fragment_container,
                        new About_Menu_Fragment()).commit();
                break;

            case R.id.nav_Share_Menu:
                getSupportFragmentManager().beginTransaction().replace(R.id.fragment_container,
                        new Share_Menu_Fragment()).commit();
                break;

            case R.id.nav_Suggestion_Menu:
                getSupportFragmentManager().beginTransaction().replace(R.id.fragment_container,
                        new Suggestion_Menu_Fragment()).commit();
                break;

        }

        drawer.closeDrawer(GravityCompat.START);
        return true;

    }

    @Override
    public void onBackPressed() {
        if (drawer.isDrawerOpen(GravityCompat.START)) {
            drawer.closeDrawer(GravityCompat.START);
        } else {
            super.onBackPressed();

        }

    }
}
