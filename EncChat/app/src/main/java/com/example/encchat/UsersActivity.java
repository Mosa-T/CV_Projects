package com.example.encchat;

import android.content.Intent;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuInflater;
import android.view.MenuItem;
import android.view.View;
import android.widget.TextView;

import androidx.appcompat.app.AppCompatActivity;
import androidx.appcompat.widget.Toolbar;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;

import com.firebase.ui.database.FirebaseRecyclerAdapter;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;
import com.squareup.picasso.Picasso;

import de.hdodenhof.circleimageview.CircleImageView;

public class UsersActivity extends AppCompatActivity {

    private RecyclerView users_rv;
    private DatabaseReference mDatabase;
    FirebaseRecyclerAdapter<Users,UsersViewHolder> firebaseRecyclerAdapter;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_users);

        Toolbar myToolbar = (Toolbar) findViewById(R.id.users_appbar);
        setSupportActionBar(myToolbar);
        getSupportActionBar().setTitle("Search Users");
        getSupportActionBar().setDisplayHomeAsUpEnabled(true);

        mDatabase = FirebaseDatabase.getInstance().getReference().child("Users");
        users_rv = (RecyclerView) findViewById(R.id.rv_users);
        users_rv.setHasFixedSize(true);
        users_rv.setLayoutManager(new LinearLayoutManager(this));

    }




    @Override
    public boolean onCreateOptionsMenu(Menu menu) {

        MenuInflater menuInflater = getMenuInflater();
        menuInflater.inflate(R.menu.searchbut,menu);

        MenuItem item = menu.findItem(R.id.search_bar);

        android.widget.SearchView searchView = (android.widget.SearchView) item.getActionView();

        searchView.setOnQueryTextListener(new android.widget.SearchView.OnQueryTextListener() {
            @Override
            public boolean onQueryTextSubmit(String query) {
                return false;
            }

            @Override
            public boolean onQueryTextChange(String newText) {






                if (firebaseRecyclerAdapter != null) firebaseRecyclerAdapter.cleanup();
            /* Nullify the adapter data if the input length is less than 2 characters */
                if (newText.equals("") || newText.length() < 2) {
                    users_rv.setAdapter(null);

            /* Define and set the adapter otherwise. */
                } else {

                    firebaseRecyclerAdapter = new FirebaseRecyclerAdapter<Users, UsersViewHolder>(
                            Users.class,
                            R.layout.user_item,
                            UsersViewHolder.class,
                            mDatabase.orderByChild("name")
                                    .startAt(newText).endAt(newText + "~").limitToFirst(5)
                    ) {
                        @Override
                        protected void populateViewHolder(UsersViewHolder viewHolder, Users model, int position) {
                            final String user_id = getRef(position).getKey();

                            viewHolder.setName(model.getName());
                            viewHolder.setStatus(model.getStatus());
                            viewHolder.setDp(model.getThumb_image());

                            viewHolder.mView.setOnClickListener(new View.OnClickListener() {
                                @Override
                                public void onClick(View v) {

                                    Intent profIntent = new Intent(UsersActivity.this, ProfileActivity.class);
                                    profIntent.putExtra("from_user_id", user_id);
                                    startActivity(profIntent);
                                }
                            });
                        }
                    };

                    users_rv.setAdapter(firebaseRecyclerAdapter);
                }


                return true;
            }
        });


        return super.onCreateOptionsMenu(menu);
    }



    public static class UsersViewHolder extends RecyclerView.ViewHolder{

        View mView;

        public UsersViewHolder(View itemView) {
            super(itemView);
            mView = itemView;
        }

        public void setStatus(String status){
            TextView user_status_tv = (TextView) mView.findViewById(R.id.user_item_status);
            user_status_tv.setText(status);
        }
        public void setName(String name){

            TextView user_name_tv = (TextView) mView.findViewById(R.id.user_item_name);
            user_name_tv.setText(name);
        }

        public void setDp(String thumb_image){
            CircleImageView userdp = (CircleImageView) mView.findViewById(R.id.user_item_dp);
            Picasso.get().load(thumb_image).centerCrop().fit().placeholder(R.drawable.ic_person_black_24dp).into(userdp);
        }
    }

}
