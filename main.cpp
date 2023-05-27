#include<bits/stdc++.h>
using namespace std;

void start();
void menu();
struct question
{
    int id, from, to, parent;
    string statement;
    question(int id1, int from1, int to1, int parent1, string statement1)
    {
        id = id1;
        from = from1;
        to = to1;
        parent =parent1;
        statement=statement1;
    }
};
struct answer
{
    int id, from, to, parent;
    string statement;
    answer(int id1, int from1, int to1, int parent1, string statement1)
    {
        id = id1;
        from = from1;
        to = to1;
        parent =parent1;
        statement=statement1;
    }
};
class user
{
private:
    string user_name ;
    string password;
    string email;
    string name;
    int number;
    int id;
    int agree;

public:
    user() {}
    user(string user_name, string password, string email, string name,int number, int id, int agree)
    {
        this->user_name = user_name;
        this->password = password;
        this->email=email;
        this->name=name;
        this->number=number;
        this->id=id;
        this->agree=agree;
    }

    void ask_question()
    {
        cout<<"Enter user id or -1 to cancel : ";
        int to_id ;
        cin >> to_id;
        cout<<"\n";
        if(to_id == -1)return;
        fstream add("users.txt", ios :: in | ios :: out | ios :: app);
        string user_name2 ;
        while(add >> user_name2)
        {
            string password2, name2,email2;
            int number2, id1,agree;
            add>>password2 >> name2 >> email2 >> number2 >> id1 >>agree;
            if(id1 == to_id)
            {
                fstream addquestion("question.txt", ios :: in | ios :: out | ios :: app);
                if(agree == 0)
                {
                    cout<<"Note : anonymous question are not allowed for this user \n";
                }
                cout<<"For thread question  : Enter question id or -1 for new question :";

                int num;
                cin>>num;
                string statement;
                cin.ignore();
                getline(cin, statement,'\n');

                ifstream numberid("numberofquestion.txt", ios :: in );
                int numberofquestion;
                numberid >> numberofquestion;
                int newnumber = numberofquestion;
                newnumber++;
                numberid.close();
                ofstream out("numberofquestion.txt", ios :: out );
                out.clear();
                out << newnumber;

                addquestion << newnumber <<" ";
                addquestion << this->id <<" ";
                addquestion << to_id <<" ";
                addquestion << num <<" ";
                addquestion << statement <<"\n";

                return ;

            }
        }
        add.close();
        cout<<"YOU CAN ASK THIS USER BECAUSE HE IS NOT FOUND \n";
        return ;
    }
    void answer_question()
    {
        cout<<"Enter Question id or -1 to cancel :";
        int number ;
        cin>>number;
        if(number==-1)return ;
        fstream read( "question.txt", ios::in | ios :: out | ios::app );
        int id ;
        while(read >> id)
        {
            int from, to, parent ;
            read >> from >> to >> parent ;
            string statement;
            getline(read, statement,'\n');
            if(id  == number)
            {
                fstream read1( "users.txt", ios::in | ios :: out | ios::app );
                bool AQ=false;
                bool AQagree=false;
                string user_name ;
                while(read1 >> user_name)
                {
                    string password;
                    string email;
                    string name;
                    int number;
                    int id;
                    int agree;
                    read1>> password >> email >> name >> number >> id >> agree ;
                    if(id == from && number == 1)AQ=true;
                    if(id == to && agree == 1)AQagree=true;
                }
                if(AQ && AQagree)
                {
                    cout<<"Question id ("<<id<<")"<<"from AQ";
                }
                else cout<<"Question id ("<<id<<")"<<"from user id ("<<from<<")";
                cout<<" to "<<to<<" ";
                cout<<"Question : "<<statement<<"\n";
                cout<<"print the answer :";

                string answer1;
                cin.ignore();
                getline(cin, answer1,'\n');

                ifstream numberid("numberofquestion.txt", ios :: in);
                numberid.clear();

                int numberofquestion;
                numberid >> numberofquestion;
                int newnumber = numberofquestion;
                newnumber++;
                ofstream out("numberofquestion.txt", ios :: out);
                out.clear();
                out << newnumber;
                fstream print_answer("answer.txt", ios :: in | ios :: out | ios :: app );
                print_answer.clear();

                print_answer << newnumber <<" ";
                print_answer << this -> id <<" ";
                print_answer << from<<" ";
                print_answer << number<<" ";
                print_answer << answer1<<"\n";

                print_answer.close();
                numberid.close();
                read1.close();

                return ;
            }
        }
        cout<<"Question NOT FOUND \n" ;
        return ;

    }

    void print_question_to_me()
    {
        fstream read( "question.txt", ios::in | ios :: out | ios::app );
        read.clear();
        int id ;
        while(read >> id)
        {
            int from, to, parent ;
            read >> from >> to >> parent ;
            string statement;
            getline(read, statement);
            if(to == this -> id)
            {
                cout<<"Question id ("<<id<<")"<<"from user id ("<<from<<")";
                cout<<"Qestion :"<<statement<<" ";
                fstream readfromanswer( "answer.txt", ios::in | ios :: out | ios::app );
                readfromanswer.clear();
                int id2;
                while(readfromanswer >> id2)
                {
                    int from, to, parent ;
                    readfromanswer >> from >> to >> parent ;
                    string statement;
                    getline(readfromanswer, statement,'\n');
                    if(parent == id)
                    {
                        cout<<" answer :"<<statement<<endl;
                    }
                }
                fstream read1( "question.txt", ios::in | ios :: out | ios::app );
                read1.clear();
                int id1 ;
                while(read1 >> id1)
                {
                    int from, to, parent ;
                    read1 >> from >> to >> parent ;
                    string statement;
                    getline(read1, statement,'\n');
                    if( parent == id )
                    {
                        cout<<"\t thread :: Qestion :";
                        cout<<statement<<"\n";
                        fstream readfromanswer( "answer.txt", ios::in | ios :: out | ios::app );
                        readfromanswer.clear();
                        int id2;
                        while(readfromanswer >> id2)
                        {
                            int from, to, parent ;
                            readfromanswer >> from >> to >> parent ;
                            string statement;
                            getline(readfromanswer, statement);
                            if(parent == id1)
                            {
                                cout<<" answer :"<<statement<<endl;
                            }
                        }

                    }

                }
                readfromanswer.close();
                readfromanswer.close();


            }
        }
        read.close();
    }
    void print_question_from_me()
    {
        fstream read( "question.txt", ios::in | ios :: out | ios::app );
        read.clear();
        int id ;
        while(read >> id)
        {
            int from, to, parent ;
            read >> from >> to >> parent ;
            string statement;
            getline(read, statement, '\n');
            if(from == this -> id)
            {
                fstream read1( "users.txt", ios::in | ios :: out | ios::app );
                read1.clear();
                bool AQ=false;
                bool AQagree=false;
                string user_name ;
                while(read1 >> user_name)
                {
                    string password;
                    string email;
                    string name;
                    int number;
                    int id;
                    int agree;
                    read1>> password >> email >> name >> number >> id >> agree ;
                    if(id == from && number == 1)AQ=true;
                    if(id == to && agree == 1)AQagree=true;
                }
                if(AQ && AQagree)
                {
                    cout<<"Question id ("<<id<<")"<<"from AQ"<<" ";
                }
                else cout<<"Question id ("<<id<<")"<<"from user id ("<<from<<")";
                cout<<"Qestion :"<<statement<<"\n";
                fstream readfromanswer( "answer.txt", ios::in | ios :: out | ios::app );
                readfromanswer.clear();
                int id2;
                while(readfromanswer >> id2)
                {
                    int from, to, parent ;
                    readfromanswer >> from >> to >> parent ;
                    string statement;
                    getline(readfromanswer, statement,'\n');
                    if(parent == id)
                    {
                        cout<<" answer :"<<statement<<endl;
                    }
                }
                fstream read3( "question.txt", ios::in | ios :: out | ios::app );
                read3.clear();
                int id1 ;
                while(read3 >> id1)
                {
                    int from, to, parent ;
                    read3 >> from >> to >> parent ;
                    string statement;
                    getline(read3, statement);
                    if( parent == id )
                    {
                        cout<<"\t thread :: Qestion :";
                        cout<<statement<<" ";
                        fstream readfromanswer( "answer.txt", ios::in | ios :: out | ios::app );
                        readfromanswer.clear();
                        int id2;
                        while(readfromanswer >> id2)
                        {
                            int from, to, parent ;
                            readfromanswer >> from >> to >> parent ;
                            string statement;
                            getline(read, statement,'\n');
                            if(parent == id1)
                            {
                                cout<<" answer :"<<statement<<endl;
                            }
                        }
                    }
                }
                read3.close();
                readfromanswer.close();
                read1.close();
            }
        }
        read.close();
    }
    void list_system_user()
    {
        fstream read1( "users.txt", ios::in | ios :: out | ios::app );
        read1.clear();
        string user_name ;
        string password;
        string email;
        string name;
        int number;
        int id;
        int agree;
        while(read1 >> user_name >> password>> email>> name>> number>> id>> agree)
        {

            cout << "ID :" << id<< "\t name :" << name  << endl;
        }
        read1.close();

        return ;

    }
    void feed()
    {
        fstream read1( "question.txt", ios::in | ios :: out | ios::app );
        read1.clear();
        int id ;
        while(read1 >> id)
        {
            int from, to,parent;
            string statement;
            read1 >> from >> to >> parent;
            getline(read1, statement,'\n');
            fstream read3( "users.txt", ios::in | ios :: out | ios::app );
            read3.clear();
            bool AQ=false;
            bool AQagree=false;
            string user_name ;
            while(read3 >> user_name)
            {
                string password;
                string email;
                string name;
                int number;
                int id2;
                int agree;
                read3>> password >> email >> name >> number >> id2 >> agree ;
                if(id == from && number == 1)AQ=true;
                if(id == to && agree == 1)AQagree=true;
            }
            fstream read2( "answer.txt", ios::in | ios :: out | ios::app );
            read2.clear();
            int id3;
            while(read2 >> id3)
            {
                int from2, to2,parent2;
                string statement2;
                read2 >> from2 >> to2 >> parent2;
                getline(read2, statement2,'\n');
                if(parent2 == id)
                {
                    if(AQ && AQagree)
                    {
                        cout<<"Question id ("<<id<<")"<<"from AQ"<<" ";
                    }
                    else cout<<"Question id ("<<id<<")"<<"from user id ("<<from<<")";
                    cout<<"Qestion :"<<statement<<" # answer :"<<statement2<<endl;
                }
            }
            read2.close();
            read3.close();





        }
        read1.close();


        return ;
    }
    void delete_question()
    {
        cout<<"Enter question id or -1 to cancle :";
        int number ;
        cin >> number;
        if(number == -1)return;
        vector<question>questions;
        vector<answer>answers;
        map < int, int >questiondelete;

        fstream read3( "question.txt", ios::in | ios :: out | ios::app );
        read3.clear();
        int id1 ;
        while(read3 >> id1)
        {
            int from, to, parent ;
            read3 >> from >> to >> parent ;
            string statement;
            getline(read3, statement);
            if(id1 == number && from != this -> id)
            {
                cout<<"\n YOU CAN NOT DO THAT BECAUSE YOU HAVE NOT THIS QUESTION \n";
                return ;
            }
            if(parent == number || id1 == number)
            {
                questiondelete[ id1 ]++;
                continue;
            }
            questions.push_back( question( id1, from, to, parent, statement ));
        }
        read3.close();
        fstream read4( "answer.txt", ios::in | ios :: out | ios::app );
        read4.clear();
        int id2 ;
        while(read4 >> id2)
        {
            int from, to, parent ;
            read4 >> from >> to >> parent ;
            string statement;
            getline(read4, statement);
            if(questiondelete[parent])
            {
                continue;
            }
            answers.push_back( answer( id2, from, to, parent, statement ));
        }
        read4.close();
        fstream readfromfile( "question.txt", ios :: out);
        fstream readfromfile2( "answer.txt", ios :: out);
        readfromfile.clear();
        readfromfile2.clear();

        for(int i=0; i<questions.size(); i++)
        {
            readfromfile << questions[i].id<<" ";
            readfromfile << questions[i].from<<" ";
            readfromfile << questions[i].to<<" ";
            readfromfile << questions[i].parent<<" ";
            readfromfile << questions[i].statement<<"\n";
        }
        readfromfile.close();
        for(int i=0; i<answers.size(); i++)
        {
            readfromfile2 << answers[i].id<<" ";
            readfromfile2 << answers[i].from<<" ";
            readfromfile2 << answers[i].to<<" ";
            readfromfile2 << answers[i].parent<<" ";
            readfromfile2 << answers[i].statement<<"\n";
        }
        readfromfile2.close();
        return ;
    }
    void Enter_number()
    {
        cout<<"Enter number in range 1 - 8 :" ;
        int number ;
        cin>>number ;
        if( number < 1 || number > 8 )
        {
            cout<<"ERROR :  INVALID NUMBER ... TRY AGAIN \n" ;
            Enter_number();
        }
        if(number == 1)
        {
            print_question_to_me();
            menu();
            Enter_number();
        }
        if(number == 2)
        {
            print_question_from_me();
            menu();
            Enter_number();

        }
        if(number == 3)
        {
            answer_question();
            menu();

            Enter_number();

        }
        if(number == 4)
        {
            delete_question();
            Enter_number();

        }
        if(number == 5)
        {
            ask_question();
            menu();
            Enter_number();

        }
        if(number == 6)
        {
            list_system_user();
            menu();
            Enter_number();

        }
        if(number == 7)
        {
            feed();
            menu();
            Enter_number();

        }
        if(number == 8)
        {
            start();
        }
    }
    void  set_user_name(string user_name)
    {
        this->user_name=user_name;
    }
    void  set_password(string password)
    {
        this->password=password;
    }
    void  set_email(string email)
    {
        this->email=email;
    }
    void  set_name(string name)
    {
        this->name=name;
    }
    void set_number(int number)
    {
        this->number=number;
    }
    void set_id(int id)
    {
        this->id=id;
    }
    void set_agree(int agree)
    {
        this->agree=agree;
    }

};
void menu()
{
    cout<<"\n Menu : \n";
    cout<<"\t 1: Print Question To Me \n" ;
    cout<<"\t 2: Print Question From Me \n" ;
    cout<<"\t 3: Answer Question \n" ;
    cout<<"\t 4: Delete Question \n" ;
    cout<<"\t 5: Ask Question \n" ;
    cout<<"\t 6: List System Users \n" ;
    cout<<"\t 7: Feed \n" ;
    cout<<"\t 8: Logout \n" ;
}
void sign_up()
{
    fstream add( "users.txt", ios::in | ios::out | ios::app );

    cout<<"Enter user name. (no space) : ";
    string user_name;
    cin>>user_name;

    cout<<"Enter password : ";
    string password;
    cin>>password;

    cout<<"Enter email : ";
    string email;
    cin>>email;

    cout<<"Enter name : ";
    string name ;
    cin>>name;

    cout<<"you are :  anonymous or not ? :(0 or 1)";
    int number;
    cin>>number;

    cout<<"Allow anonymous questions? :(0 or 1)";
    int agree;
    cin>>agree;

    string user_name2 ;
    while(add >> user_name2)
    {
        string password2, name2,email2;
        int number2, id1, agree;
        add>>password2 >> name2 >> email2 >> number2 >> id1 >>agree;
        if(user_name2 == user_name)
        {
            cout<<"YOU CAN NOT SIGN_UP BECAUSE YOU ALREADY SING UP ";
            return ;
        }
    }
    add.clear();
    ifstream in("numberofuser.txt");
    in.clear();
    int numberofuser;
    in >> numberofuser;
    int newnumber=numberofuser;
    newnumber++;
    add << user_name <<" ";
    add << password<<" ";
    add << email<<" ";
    add << name<<" ";
    add << number<<" ";
    add << newnumber <<" ";
    add << agree <<"\n";
    add.close();
    in.close();
    ofstream out("numberofuser.txt");
    out.clear();
    out << newnumber ;
    out.close();

}
void log_in()
{
    fstream in("users.txt", ios::in | ios::out | ios::app);
    in.clear();
    user user_1;
    cout<<"Enter user name: ";
    string user_name;
    cin>>user_name;


    cout<<"\n";
    cout<<"Enter user password: ";
    string password ;
    cin>>password;

    cout<<"\n";
    string user_name2;
    while(in >> user_name2)
    {
        string password2, name, email ;
        int number, id,agree;
        in>>password2 >> name >> email >> number >> id >> agree;
        if(user_name2 == user_name)
        {
            user_1.set_user_name(user_name);
            user_1.set_password(password);
            user_1.set_name(name);
            user_1.set_email(email);
            user_1.set_number(number);
            user_1.set_id(id);
            user_1.set_agree(agree);


            menu();
            user_1.Enter_number();
            return;
        }
    }
    in.close();
    cout<<"YOU CAN NOT LOG IN USER NOT FOUND \n" ;
    return ;
}
void start()
{
    while(true)
    {
        cout << "Menu :\n";
        cout << "\t 1: login \n";
        cout << "\t 2: sign up \n";
        cout << "Enter number in range 1 - 2 :" ;
        int number ;
        cin >> number ;
        if(number == 1)
        {
            log_in();
        }
        else if(number==2)sign_up();
        else continue;
    }
}

int main()
{

    start();







































































































    return 0;
}


