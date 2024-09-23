#include <stdio.h>
#include <windows.h>

int main()
{
    int money = 0;
    int click_value = 1; // 클릭당 벌리는 돈

    printf("-----[ 조작키 ]-----\n");
    printf("스페이스바 : 돈 벌기\n");
    printf("S : 상점 열기\n");

    while (1)
    {
        // 스페이스바로 돈 벌기
        if (GetAsyncKeyState(VK_SPACE) & 0x0001)
        {
            system("cls");
            money += click_value;
            printf("금액 : %d\n", money);
            printf("스페이스바 : 돈 벌기\n");
            printf("S : 상점 열기\n");
        }

        // 상점 열기
        if (GetAsyncKeyState(0x53) & 0x0001) // 'S' 를 눌렀을 때
        {
            system("cls");
            printf("상점에 입장했습니다.\n");
            printf("\n");
            printf("[현재 금액: %d원]\n", money);
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
                    if (money >= 100)
                    {
                        money -= 100;
                        click_value++;
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

                Sleep(100); // 너무 자주 루프를 돌지 않도록 약간 대기
            }

            system("cls"); // 화면 초기화
            printf("금액 : %d\n", money);
            printf("스페이스바 : 돈 벌기\n");
            printf("'S' : 상점 열기\n");
        }

        Sleep(100); // 너무 자주 루프를 돌지 않도록 약간 대기
    }

    return 0;
}