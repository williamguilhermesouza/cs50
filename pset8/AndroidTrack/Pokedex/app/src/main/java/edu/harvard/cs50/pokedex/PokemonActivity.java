package edu.harvard.cs50.pokedex;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Context;
import android.content.SharedPreferences;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.AsyncTask;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.TextView;

import com.android.volley.Request;
import com.android.volley.RequestQueue;
import com.android.volley.Response;
import com.android.volley.VolleyError;
import com.android.volley.toolbox.JsonObjectRequest;
import com.android.volley.toolbox.Volley;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.io.IOException;
import java.net.URL;

public class PokemonActivity extends AppCompatActivity {
    private ImageView imageView;
    private TextView nameTextView;
    private TextView numberTextView;
    private TextView type1TextView;
    private TextView type2TextView;
    private TextView description;
    private Button catchButton;
    private String url;
    private RequestQueue requestQueue;
    private String pokemonName;
    public String is_caught = "Catch";
    SharedPreferences pref;
    SharedPreferences.Editor editor;
    String key = "statePrefs";



    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_pokemon);

        requestQueue = Volley.newRequestQueue(getApplicationContext());
        url = getIntent().getStringExtra("url");
        imageView = findViewById(R.id.pokemon_image);
        nameTextView = findViewById(R.id.pokemon_name);
        numberTextView = findViewById(R.id.pokemon_number);
        type1TextView = findViewById(R.id.pokemon_type1);
        type2TextView = findViewById(R.id.pokemon_type2);
        description = findViewById(R.id.description);
        catchButton = findViewById(R.id.catch_button);

        load();
    }

    private class DownloadSpriteTask extends AsyncTask<String, Void, Bitmap> {
        @Override
        protected Bitmap doInBackground(String... strings) {
            try {
                URL url = new URL(strings[0]);
                return BitmapFactory.decodeStream(url.openStream());
            } catch (IOException e) {
                Log.e("cs50", "Download sprite error", e);
                return null;
            }
        }

        @Override
        protected void onPostExecute(Bitmap bitmap) {
            imageView.setImageBitmap(bitmap);

        }
    }

    public void load() {
        type1TextView.setText("");
        type2TextView.setText("");
        description.setText("");




        JsonObjectRequest request = new JsonObjectRequest(Request.Method.GET, url, null, new Response.Listener<JSONObject>() {
            @Override
            public void onResponse(JSONObject response) {
                try {
                    nameTextView.setText(response.getString("name"));
                    numberTextView.setText(String.format("#%03d", response.getInt("id")));



                    JSONObject imgDict = response.getJSONObject("sprites");
                    String imgUrl = imgDict.getString("front_default");
                    new DownloadSpriteTask().execute(imgUrl);

                    pokemonName = response.getString("name");

                    pref = getSharedPreferences(key, Context.MODE_PRIVATE);
                    editor = pref.edit();
                    if (!pref.contains(pokemonName)) {
                        editor.putString(pokemonName, "Catch");
                    }

                    String state = pref.getString(pokemonName, "Catch");
                    catchButton.setText(state);

                    editor.apply();

                    JSONArray typeEntries = response.getJSONArray("types");
                    for (int i = 0; i < typeEntries.length(); i++) {
                        JSONObject typeEntry = typeEntries.getJSONObject(i);
                        int slot = typeEntry.getInt("slot");
                        String type = typeEntry.getJSONObject("type").getString("name");

                        if (slot == 1) {
                            type1TextView.setText(type);
                        }
                        else if (slot == 2) {
                            type2TextView.setText(type);
                        }
                    }

                    String pokeId = response.getString("id");

                    String descUrl = "https://pokeapi.co/api/v2/pokemon-species/" + pokeId;

                    JsonObjectRequest requestDesc = new JsonObjectRequest(Request.Method.GET, descUrl, null, new Response.Listener<JSONObject>() {
                        @Override
                        public void onResponse(JSONObject response) {
                            try {

                                JSONArray textEntries = response.getJSONArray("flavor_text_entries");
                                for (int i = 0; i < textEntries.length(); i++) {
                                    JSONObject textEntry = textEntries.getJSONObject(i);
                                    String language = textEntry.getJSONObject("language").getString("name");
                                    String descText = textEntry.getString("flavor_text");

                                    if (language.contains("en")) {
                                        description.setText(descText);
                                        break;
                                    }
                                }

                            } catch (JSONException e) {
                                Log.e("cs50", descUrl, e);
                            }
                        }
                    }, new Response.ErrorListener() {
                        @Override
                        public void onErrorResponse(VolleyError error) {
                            Log.e("cs50", "Pokemon description error", error);
                        }
                    });

                    requestQueue.add(requestDesc);

                } catch (JSONException e) {
                    Log.e("cs50", "Pokemon json error", e);
                }
            }
        }, new Response.ErrorListener() {
            @Override
            public void onErrorResponse(VolleyError error) {
                Log.e("cs50", "Pokemon details error", error);
            }
        });


        requestQueue.add(request);

    }



    public void toggleCatch(View view) {
        if (is_caught.equals("Release")) {
            is_caught = "Catch";
        } else {
            is_caught = "Release";
        }
        editor.remove(pokemonName);
        editor.putString(pokemonName, is_caught).apply();
        catchButton.setText(is_caught);

    }
}
