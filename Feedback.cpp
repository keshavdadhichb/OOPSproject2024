#include <iostream>
using namespace std;
class feedback{
private:
    float quality[100], friendliness[100], cleaning[100],overall[100];
    int i=0;
    char feed[100][1000];
public:
    void text(){
        cout<<"Your Room has been cleaned\nPlease share us your experience through this feedback"<<endl;
    }
    void check()
    {
        int j=0;
        cout<<"Rate the given criteria out of 10"<<endl;
        cout<<"Cleaning : ";
        do{
            cin>>cleaning[i];
            if ((cleaning[i]>10)||(cleaning[i]<0)){
                cout<<"Incorrect Input\nPlease answer in 0 to 10"<<endl;
            }
        }while((cleaning[i]>10)||(cleaning[i]<0));
        cout<<"Quality of the products used : ";
        do{
            cin>>quality[i];
            if ((quality[i]>10)||(cleaning[i]<0)){
                cout<<"Incorrect Input\nPlease answer in 0 to 10"<<endl;
            }
        }while((cleaning[i]>10)||(cleaning[i]<0));
        cout<<"Friendliness of the worker : ";
        do{
            cin>>friendliness[i];
            if ((friendliness[i]>10)||(friendliness[i]<0)){
                cout<<"Incorrect Input\nPlease answer in 0 to 10"<<endl;
            }
        }while((friendliness[i]>10)||(friendliness[i]<0));

        overall[i]= (cleaning[i]+quality[i]+friendliness[i])/3;
        cout<<"Enter any Feedback(Under 100 words): ";
        cin>>feed[i][j];
        cout<<"Thank you for your feedback"<<endl;
        if (overall[i]>5){
            cout<<"We hope you get our cleaning service again."<<endl;
        }
        else{
            cout<<"We are so sorry to hear your concerns and make it better next time."<<endl;
        }
        i++;

    }
    void line(){
        cout<<"_______________________________________________"<<endl;
    }
};

int main()
{
    feedback f;
    f.line();
    f.text();
    f.line();
    f.check();
    return 0;
}
