#include<iostream>
#include<fstream>  // подключение библиотеки файлового ввода/вывода через потоки
using namespace std;
struct color { unsigned char r; unsigned char g; unsigned char b; };
int main() {
    ifstream fff("1.bmp", ios::binary); //  ios::binary влияет ТОЛЬКО на endl.
    ofstream ggg("rez2.bmp", ios::binary);//сюда пишем (поток типа ofstream= output file stream)
    if (!fff) { cout << "No file d:\\1.bmp. Can't open\n"; exit(1); }
    if (!ggg) { cout << "   file d:\\rez.bmp. Can't create\n"; exit(1); }

    char buf[100];// куда читать байты
    unsigned char r, g, b;//компоненты цвета
    color c;
    color f;
    int w, h;//надеемся. что тут в int 4 байта
    fff.read((char*)&buf, 18);   //чтение 18 байт заголовка bmp
    ggg.write((char*)&buf, 18);    //запись 18 байт заголовка bmp
    fff.read((char*)&w, 4);//cout << "w=" << w;   //чтение width из заголовка bmp
    fff.read((char*)&w, 4);// cout << ", h=" << w; //чтение height из заголовка bmp
    w = 256; ggg.write((char*)&w, 4);    //запись width в заголовок bmp (кратно 4, обязательно для нас, чтобы не делать выравнивание)
    h = 256; ggg.write((char*)&h, 4);    //запись height в заголовок bmp
    fff.read((char*)&buf, 28);   //чтение 28 байт заголовка bmp
    ggg.write((char*)&buf, 28);    //запись 28 байт заголовка bmp

    //c.r = c.g = 0, c.b = 243;
    //for (int i = 1; i <= h; ++i) {
    //    //++r;g=0;b=0;//диагональный градиент т.к. написали ++r
    //    for (int j = 1; j <= w; ++j) {
    //        ggg.write((char*)&c, sizeof(c));     //запись сразу всего цвета
    //        ++c.g;
    //        /*    ggg.write((char *)&b, sizeof(b));   //запись одной компоненты цвета
    //            ggg.write((char *)&g, sizeof(g));    //запись одной компоненты цвета
    //            ggg.write((char *)&r, sizeof(r));    //запись одной компоненты цвета
    //            ++g;
    //            */
    //    }
    //    //++c.r; c.g = c.b = 0;
    //}
    
    cout << "background color\n";
    int cr, cg, cb;
    cin >> cb;
    cin >> cg;
    cin >> cr;
    
    c.r = cr; c.g = cg; c.b = cb;
    cout << "\nfigure color\n";
    
    cin >> cb;
    cin >> cg;
    cin >> cr;
    
    f.r = cr; f.g = cg; f.b = cb;
    int centr_h, centr_w, width,height;

    
    centr_h=240;
    centr_w=32;
    width=32;
    height=16;



    for (int i = 1; i <= h; ++i) {

        for (int j = 1; j <= w; ++j) {
            if ((i >= centr_h - height) && (i<= centr_h + height) && (j>= centr_w - width) && (j<= centr_w + width)) {
                ggg.write((char*)&f, sizeof(f));
                
            }
            else { ggg.write((char*)&c, sizeof(c));}     //запись сразу всего цвета
        }

    }

    fff.close();//закрыли файл
    ggg.close();//закрыли файл
    return 0;
}