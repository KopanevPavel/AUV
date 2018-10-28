#include <iostream>
#include <unistd.h>
#include <math.h>
#include <string>


//#define N1 7
//#define M1 5
//#define N2 7
//#define M2 5
//#define N3 7
//#define M3 5

using namespace std;

class avtomat{    //Чуть позже сделаем его по нормальному



public:
    int x_now=0, y_now=0, z_now=200;
    string q0 = "stand";

    int left_bound,right_bound;

    int x_centre_portal, y_centre_portal, z_centre_portal; //Для ворот
    bool see_centre = false;
    bool match_centre = false;
    bool is_left_bound_check = false, is_right_bound_check=false;

    int x_flare, y_flare, z_flare;



    int direction=0;
    bool vidim_vorota = false;
//    int delta1[N1][M1];
//    int fy1[N1][M1];
//    int delta2[N2][M2];
//    int fy2[N2][M2];
//    int delta3[N3][M3];
//    int fy3[N3][M3];
//    int **delta, **fy;
    int problem=1;
    bool problem1=false, problem2=false, problem3=false;


    void go_left(int dist);
    void go_right(int dist);
    void go_forward(int dist);
    void go_back(int dist);
    void go_up(int dist);
    void go_down(int dist);
    void go_nanana(int dist);
    void turn_right_90();
    void adjustment(int x);
//    void go_through_portal();
};
avtomat A;

void avtomat::adjustment(int x_target) {
    int x_to_go;
    for(;;) {
/*      считывание класса автомата    */
        x_to_go = x_target - A.x_now;
        if (abs(x_to_go) >=8) {
            A.q0 = "stand";
            cout<<"stand"<<endl;
            A.match_centre = true;
            sleep(5);
            break;
        }
        if (x_to_go > 0) {
            A.go_right(5);
            continue;
        }
        if (x_to_go <0) {
            A.go_left(5);
            continue;
        }
    }
}


void avtomat::go_up(int z) {
    A.q0 = "up";
    cout<<"up: "<<z<<endl;
}
void avtomat::go_down(int z) {
    A.q0="down";
    cout<<"down: "<<z<<endl;
}

void avtomat::go_right(int z) {
    A.q0="right";
    cout<<"right: "<<z<<endl;
}
void avtomat::go_left(int z) {
    A.q0 = "left";
    cout<<"left: "<<z<<endl;
}
void avtomat::go_forward(int z) {
    A.q0="forward";
    cout<<"forward:"<<z<<endl;
}

void avtomat::go_back(int z) {
    A.q0="back";
    cout<<"back: "<<z<<endl;
}

//signal_input :-1 не стабилизировался в воде
//signal_input : 0 не видит цель
//signal_input : 1 видит цель
//signal_input : 2 не слышит цель
//signal_input : 3 слышит цель
//signal_input : 4 закончил действие



// Первое задание
void go_portal() {
//    int signal_input,signal_output, signal;
//    A.delta=A.delta1;
//    A.fy=A.fy;
    for(;;) {
        sleep(1);
/*      считывание класса автомата    */
        if (A.see_centre) {
            A.q0 = "stand";
            break;
        }
        // ищем центр ворот, если не видим изначально
        if (!A.see_centre) {
            if (!A.is_right_bound_check) {
                A.go_right(10);
                if (abs(A.x_now-A.right_bound) <= 50) {     //Перестаем движение
                    A.is_right_bound_check = true;          //за 50 см
                    A.q0 = "stand";                         //до границы
                }
                continue;
            }
            if (!A.is_left_bound_check) {
                A.go_left(10);
                if (abs(A.x_now-A.left_bound) <=50) {
                    A.is_left_bound_check = true;
                    A.q0 = "stand";
                }
                continue;
            }
            continue;
        }
        break;
    }
    A.adjustment(A.x_centre_portal);
    if (A.match_centre) A.go_forward((A.y_centre_portal-A.y_now)/2);
    sleep(10);
    A.match_centre=false;
    A.adjustment(A.x_centre_portal);
    A.go_forward(A.y_centre_portal-A.y_now+100);
    A.problem1=true;
}
// Второе задание
void crash_ball() {
/*      считывание класса автомата    */
    A.adjustment(A.x_flare);//Встаем напротив палки
    A.go_down(50);// спускаемся еще пониже

    //Пытаемся доплыть до флага
    if (A.y_flare-A.y_now > 0) {
        A.go_forward(A.y_flare-A.y_now-100);
        A.adjustment(A.x_flare);// проверяем находимся ли мы напротив палки
        A.go_forward(A.y_flare-A.y_now+25);
        A.go_back(5);//ерзаем
    }
    else if (A.y_now - A.y_flare > 0) {
        A.go_back(A.y_now-A.y_flare-100);
        A.adjustment(A.x_flare);// проверяем находимся ли мы напротив палки
        A.go_back(A.y_now-A.y_flare+25);
        A.go_forward(5);//ерзаем
    }
    //еще немного ерзаем на тот случай если мы кривые и не попали

/*      считывание класса автомата    */
    A.go_left(30);
    A.go_right(60);
    A.go_back(40);
    A.problem2=true;


}

void put_ball(){

}

void avtonom() {
    
    int signal_input;//,signal_output, signal;
    cin>>signal_input;
    while(signal_input==-1) {
        sleep(3);   
        cin >> signal_input;
    }
    A.go_down(100);
    sleep(5); //стабилизируется


    if (!A.problem1) go_portal();
    if (!A.problem2) crash_ball();
    if (!A.problem3) put_ball();

}




int main()
{

    //cin>>A.x_begin>>A.y_begin>>A.z_begin;
    //int (*find_len)(int, int, int) = length_pow_2;
    int n, x=0, y=0, z=0;
    cin>>n;
    int x1, y1, z1;
    for (int i=0; i<n; i++) {
        cin >>x1>>y1>>z1;
        x+=x1;
        y+=y1;
        z+=z1;
    }
    if (abs(x)+abs(y)+abs(z)==0) cout<<"YES"<<endl;
    else cout<< "NO"<<endl;


    return 0;
}





