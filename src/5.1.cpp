#include <iostream>
#include <arpa/inet.h>
using namespace std;

void socket_addr_5_1_2_()// 5.1.2章节， 通用Socket地址
{
    in_addr addr1;
    addr1.s_addr = inet_addr("1.2.3.4");
    const char* szValue1 = inet_ntoa(addr1);

    in_addr addr2;
    addr2.s_addr = inet_addr("10.194.71.60");
    const char* szValue2 = inet_ntoa(addr2);

    cout << szValue1 << endl;
    cout << szValue2 << endl;
}
