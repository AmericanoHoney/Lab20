#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdlib>

using namespace std;

char score2grade(int score){
    if(score >= 80) return 'A';
    if(score >= 70) return 'B';
    if(score >= 60) return 'C';
    if(score >= 50) return 'D';
    else return 'F';
}

string toUpperStr(string x){
    string y = x;
    for(unsigned i = 0; i < x.size();i++) y[i] = toupper(x[i]);
    return y;
}

void importDataFromFile(string filename,vector<string>& names,vector<int>& scores,vector<char>& grades){
    ifstream source(filename);
    string textline;
    char name[100];
    int a,b,c,sum=0;
    char format[] = "%[^:] : %d %d %d";
    while(getline(source,textline)){
        sscanf(textline.c_str(),format,name,&a,&b,&c);
        sum=a+b+c;
        names.push_back(name);
        scores.push_back(sum);
        grades.push_back(score2grade(sum));
    }
}

void getCommand(string &command, string &key){
    cout << "Please input your command: ";
    cin >> command;
    if(toUpperStr(command) == "NAME"||toUpperStr(command) == "GRADE") {
        cin.ignore();
        getline(cin,key);
    }
    else {
        getline(cin,key);
    }
}

void searchName(vector<string> &names, vector<int> &scores, vector<char> &grades, string key){
    bool found = false;
    cout << "---------------------------------\n";
    for(unsigned int i=0;i<names.size();i++){
        if(toUpperStr(key)==toUpperStr(names[i]))
        {
            printf("%s's score = %d\n%s's grade = %c\n",names[i].c_str(),scores[i],names[i].c_str(),grades[i]);
            found = true;
            break;
        }
    }
    if(!found) printf ("Cannot found.\n");
    cout << "---------------------------------\n";
}

void searchGrade(vector<string> &names, vector<int> &scores, vector<char> &grades, string key){
    bool found = false;
    cout << "---------------------------------\n";
    for(unsigned int i=0;i<grades.size();i++){
        if(toUpperStr(key)[0]==grades[i])
        {
            printf("%s (%d)\n",names[i].c_str(),scores[i]);
            found = true;
        }
    }
    if(!found) printf ("Cannot found.\n");
    cout << "---------------------------------\n";
}

int main(){
    string filename = "name_score.txt";
    vector<string> names;
    vector<int> scores;
    vector<char> grades; 
    importDataFromFile(filename, names, scores, grades);
    
    do{
        string command, key;
        getCommand(command,key);
        command = toUpperStr(command);
        key = toUpperStr(key);
        if(command == "EXIT") break;
        else if(command == "GRADE") searchGrade(names, scores, grades, key);
        else if(command == "NAME") searchName(names, scores, grades, key);
        else{
            cout << "---------------------------------\n";
            cout << "Invalid command.\n";
            cout << "---------------------------------\n";
        }
    }while(true);
    
    return 0;
}