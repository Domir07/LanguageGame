#include <stdio.h>
#include <windows.h>

// 업적 달성 여부 변수 (0 = 미달성, 1 = 달성)
int a_100 = 0;
int a_500 = 0;
int a_1000 = 0;

#pragma region 업적 기능
void Achievements(int money) // 업적을 체크 함수
{
    if (money >= 100 && a_100 == 0) // 업적 재달성 막는 식 (소지금이 100 이상이고, 업적 변수가 0일때)
    {
        a_100 = 1; // 업적 달성 표시 (업적 변수 0을 1로 만들어서 업적 재달성을 막음)
        printf("업적 달성: 100원 달성!\n");
    }
    if (money >= 500 && a_500 == 0)
    {
        a_500 = 1;
        printf("업적 달성: 500원 달성!\n");
    }
    if (money >= 1000 && a_1000 == 0)
    {
        a_1000 = 1;
        printf("업적 달성: 1000원 달성!\n");
    }
}

void showAchievements() // 업적 달성 출력
{
    system("cls");
    printf("-----[ 업적 ]-----\n");

    // 100원 업적
    if (a_100 == 1)
    {
        printf(" [달성] 100원 벌기\n");
    }
    else
    {
        printf(" [미달성] 100원 벌기\n");
    }

    // 500원 업적
    if (a_500 == 1)
    {
        printf(" [달성] 500원 벌기\n");
    }
    else
    {
        printf(" [미달성] 500원 벌기\n");
    }

    // 1000원 업적
    if (a_1000 == 1)
    {
        printf(" [달성] 1000원 벌기\n");
    }
    else
    {
        printf(" [미달성] 1000원 벌기\n");
    }

    printf("\n메뉴로 돌아가기 : 'ESC'\n");

    // ESC 누르면 업적 창 닫기
    while (1)
    {
        if (GetAsyncKeyState(VK_ESCAPE) & 0x0001)
        {
            system("cls");
            break;
        }
        Sleep(100); // 너무 자주 루프를 돌지 않도록 대기
    }
}
#pragma endregion

#pragma region 상점 기능
// 상점 기능 함수
void openShop(int* money, int* click_value)
{
    system("cls");
    printf("상점에 입장했습니다.\n");
    printf("\n");
    printf("[현재 금액: %d원]\n", *money);
    printf("\n");
    printf("-----[ 상점 ]-----\n");
    printf(" '1'. 클릭당 수입 증가 (100원) - 클릭당 1원 추가 벌기.\n");
    printf("------------------\n");
    printf("\n");
    printf("구매할 상품의 번호를 입력해주세요.\n");
    printf("상점 나가기 : 'ESC'\n");

    while (1)
    {
        // '1' 을 눌렀을 때, 클릭당 수입 증가
        if (GetAsyncKeyState(0x31) & 0x0001)
        {
            if (*money >= 100)
            {
                *money -= 100;
                (*click_value)++;
                printf("<클릭당 수입이 증가했습니다!>\n");
            }
            else
            {
                printf("돈이 부족합니다!\n");
            }
        }

        // 'ESC' 키를 눌렀을 때 상점 나가기
        if (GetAsyncKeyState(VK_ESCAPE) & 0x0001)
        {
            printf("상점을 나갑니다.\n");
            Sleep(1000); // 메시지를 보여주기 위해 약간 대기
            break; // 상점 나가기
        }

        Sleep(100);
    }

    system("cls"); // 채팅청소
}
#pragma endregion


#pragma region 메뉴 기능
void Menu(int* money, int* click_value)
{
    system("cls");
    printf("-----[ 메뉴 ]-----\n");
    printf("1. 상점 열기\n");
    printf("2. 업적 확인\n");
    printf("메뉴 나가기: 'ESC'\n");

    while (1)
    {
        // '1' 을 눌렀을 때 상점 열기
        if (GetAsyncKeyState(0x31) & 0x0001)
        {
            Shop(money, click_value); // 상점 열기
            break;
        }

        // '2' 를 눌렀을 때 업적 확인
        if (GetAsyncKeyState(0x32) & 0x0001)
        {
            showAchievements(); // 업적 확인
            break;
        }

        // 'ESC' 키를 눌렀을 때 메뉴 나가기
        if (GetAsyncKeyState(VK_ESCAPE) & 0x0001)
        {
            system("cls");
            break; // 메뉴 나가기
        }

        Sleep(100);
    }
}
#pragma endregion

int main()
{
    int money = 0;
    int click_value = 1; // 클릭당 벌리는 돈

    printf("-----[ 조작키 ]-----\n");
    printf("스페이스바 : 돈 벌기\n");
    printf("M : 메뉴 열기 (상점/업적)\n");

    while (1)
    {
        // 스페이스바로 돈 벌기
        if (GetAsyncKeyState(VK_SPACE) & 0x0001)
        {
            system("cls");
            money += click_value;
            printf("금액 : %d\n", money);
            printf("스페이스바 : 돈 벌기\n");
            printf("M : 메뉴 열기 (상점/업적)\n");

            // 업적 체크 함수 호출
            Achievements(money);
        }

        // 메뉴 열기
        if (GetAsyncKeyState(0x4D) & 0x0001) // 'M' 를 눌렀을 때
        {
            openMenu(&money, &click_value); // 메뉴 열기
        }

        Sleep(100);
    }

    return 0;
}
