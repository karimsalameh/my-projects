#include "sha256.cpp"
#include<iostream>
#include<string>
#include<vector>
#include <ctime>
#include <random>
#include <map>

using namespace std;
int state=true;
string id_gen(int current_time){

    default_random_engine gen(current_time);
    uniform_int_distribution<int> dist(0, 1000000);
    int random_number=dist(gen);
    string user_id=to_string(random_number);

return user_id;
}
int main(){
    system("clear");
    string username;
    string password;
    string user_id;
    string salt;
    string hashed_password;
    string salted_hashed_password;
    map <string,vector<vector<string>>> table_map;

    vector<vector<string>> table;

    while(state==true){

    
    int choice;
    cout<<"1. Sign up \n2. Loggin \n3.Show table \n4. Exit \n";
    cin>>choice;


    if(choice==1){
        cout<<"Enter your username \n";
        cin>>username;

        if (table_map.count(username) > 0) {
            cout<<"Username already exists \n";
            continue;
        }

        cout<<"Enter your password \n";
        cin>>password;
        cout<<"\n \n";

        int current_time=time(nullptr);
        string time_stamp=to_string(current_time);

        user_id=id_gen(current_time);

        hashed_password=sha256(password);

        salt=sha256(username+user_id+time_stamp);
        salted_hashed_password=sha256(password+salt);

        table={
            {user_id, username, password},
            {user_id, username, hashed_password},
            {user_id, username, salt, salted_hashed_password}
        };
        table_map[username]=table;

    }
    else if (choice==2){
        int temp_count = 0;
        string temp_username;
        cout<<"Enter your username \n";
        cin>>temp_username;
        
        if (table_map.count(temp_username) == 0) {
            cout<<"Username doesn't exist \n";
            continue;
        }

        cout<<"Enter your password \n";
        string temp_password;
        cin>>temp_password;
        string temp_hashed_password=sha256(temp_password);
        

        string temp_salt = table_map[temp_username][2][2];
        
        string temp_salted_hashed_password=sha256(temp_password+temp_salt);
        vector<string> temp_list={temp_password,temp_hashed_password,temp_salted_hashed_password};

        for(int i=0;i<table_map[temp_username].size();i++){
           if( temp_list[i]== table_map[temp_username][i][table_map[temp_username][i].size()-1]){
            temp_count++;

           }
        }
        
        if(temp_count==3){
            cout<<"password is correct! \n";

        }
        else{
            cout<<"password is incorrect! \n";
            
        }

    }
    else if (choice==3){
        for(const auto& pair:table_map){
            cout << "Username: " << pair.first << endl;
            for(const auto& row:pair.second){
                for(const auto& element:row){
                    cout << element << " ";
                }
                cout << endl;
            }
            cout << endl;
        }

    }
    else if (choice==4){
        state=false;
    }
    else{
        cout<<"Invalid choice \n";
    }
    }

return 0;

}