#include <stdio.h>
#include <windows.h>

int main()
{
    int money = 0;
    int click_value = 1; // Ŭ���� ������ ��

    printf("-----[ ����Ű ]-----\n");
    printf("�����̽��� : �� ����\n");
    printf("S : ���� ����\n");

    while (1)
    {
        // �����̽��ٷ� �� ����
        if (GetAsyncKeyState(VK_SPACE) & 0x0001)
        {
            system("cls");
            money += click_value;
            printf("�ݾ� : %d\n", money);
            printf("�����̽��� : �� ����\n");
            printf("S : ���� ����\n");
        }

        // ���� ����
        if (GetAsyncKeyState(0x53) & 0x0001) // 'S' �� ������ ��
        {
            system("cls");
            printf("������ �����߽��ϴ�.\n");
            printf("\n");
            printf("[���� �ݾ�: %d��]\n", money);
            printf("\n");
            printf("-----[ ���� ]-----\n");
            printf(" '1'. Ŭ���� ���� ���� (100��) - Ŭ���� 1�� �߰� ����.\n");
            printf("------------------\n");
            printf("\n");
            printf("������ ��ǰ�� ��ȣ�� �Է����ּ���.\n");
            printf("���� ������ : 'ESC'\n");

            while (1)
            {
                // '1' �� ������ ��, Ŭ���� ���� ����
                if (GetAsyncKeyState(0x31) & 0x0001)
                {
                    if (money >= 100)
                    {
                        money -= 100;
                        click_value++;
                        printf("<Ŭ���� ������ �����߽��ϴ�!>\n");
                    }
                    else
                    {
                        printf("���� �����մϴ�!\n");
                    }

                }

                // 'ESC' Ű�� ������ �� ���� ������
                if (GetAsyncKeyState(VK_ESCAPE) & 0x0001)
                {
                    printf("������ �����ϴ�.\n");
                    Sleep(1000); // �޽����� �����ֱ� ���� �ణ ���
                    break; // ���� ������
                }

                Sleep(100); // �ʹ� ���� ������ ���� �ʵ��� �ణ ���
            }

            system("cls"); // ȭ�� �ʱ�ȭ
            printf("�ݾ� : %d\n", money);
            printf("�����̽��� : �� ����\n");
            printf("'S' : ���� ����\n");
        }

        Sleep(100); // �ʹ� ���� ������ ���� �ʵ��� �ణ ���
    }

    return 0;
}