#include <stdio.h>
#include <windows.h>

#define LEVEL_UP_MONEY 100 // �ʱ� ������ ���
#define MAX_LEVEL 100 // �ִ� ���� ����

// ���� �޼� ���� ���� (0 = �̴޼�, 1 = �޼�)
int a_100 = 0;
int a_500 = 0;
int a_1000 = 0;

// ���� ����
int level = 1; // ���� ����
int level_up_money = LEVEL_UP_MONEY; // �������� �ʿ��� ��

#pragma region ���� ���
void Achievements(int money) // ������ üũ �Լ�
{
    if (money >= 100 && a_100 == 0) // ���� ��޼� ���� �� (�������� 100 �̻��̰�, ���� ������ 0�϶�)
    {
        a_100 = 1; // ���� �޼� ǥ�� (���� ���� 0�� 1�� ���� ���� ��޼��� ����)
        printf("���� �޼�: 100�� �޼�!\n");
    }
    if (money >= 500 && a_500 == 0)
    {
        a_500 = 1;
        printf("���� �޼�: 500�� �޼�!\n");
    }
    if (money >= 1000 && a_1000 == 0)
    {
        a_1000 = 1;
        printf("���� �޼�: 1000�� �޼�!\n");
    }
}

void showAchievements() // ���� �޼� ���
{
    system("cls");
    printf("-----[ ���� ]-----\n");

    // 100�� ����
    if (a_100 == 1)
    {
        printf(" [�޼�] 100�� ����\n");
    }
    else
    {
        printf(" [�̴޼�] 100�� ����\n");
    }

    // 500�� ����
    if (a_500 == 1)
    {
        printf(" [�޼�] 500�� ����\n");
    }
    else
    {
        printf(" [�̴޼�] 500�� ����\n");
    }

    // 1000�� ����
    if (a_1000 == 1)
    {
        printf(" [�޼�] 1000�� ����\n");
    }
    else
    {
        printf(" [�̴޼�] 1000�� ����\n");
    }

    printf("\n�޴��� ���ư��� : 'ESC'\n");

    // ESC ������ ���� â �ݱ�
    while (1)
    {
        if (GetAsyncKeyState(VK_ESCAPE) & 0x0001)
        {
            system("cls");
            break;
        }
        Sleep(100); // �ʹ� ���� ������ ���� �ʵ��� ���
    }
}
#pragma endregion

#pragma region ���� ���
// ���� ��� �Լ�
void openShop(int* money, int* click_value)
{
    system("cls");
    printf("������ �����߽��ϴ�.\n");
    printf("\n");
    printf("[���� �ݾ�: %d��]\n", *money);
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
            if (*money >= 100)
            {
                *money -= 100;
                (*click_value)++;
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

        Sleep(100);
    }

    system("cls"); // ä��û��
}
#pragma endregion

#pragma region ���� ���

void levelUp(int* money) // ���� �Һ��ؼ� �������ϴ� �Լ�
{
    if (level >= MAX_LEVEL)
    {
        printf("�ִ� ������ �����߽��ϴ�! �� �̻� �������� �� �����ϴ�.\n");
        return;
    }

    if (*money >= level_up_money) // ������ ����� ������� Ȯ��
    {
        *money -= level_up_money; // ���� �Һ�
        level++; // ���� ����
        printf("������!\n");
        printf("���� ����: %d\n", level);
        level_up_money *= 2; // ���� ������ ��� 2�� ����
        printf("���� �������� �ʿ��� �ݾ�: %d��\n", level_up_money);
    }
    else
    {
        printf("�������� ���� %d���� �� �ʿ��մϴ�.\n", level_up_money - *money);
    }
}

void LevelInfo(int* money) // ���� ����   
{
    system("cls");
    printf("-----[ ���� ���� ]-----\n");
    printf("���� ����: %d\n", level);
    printf("���� ������ ���: %d��\n", level_up_money);
    printf("�ִ� ����: %d\n", MAX_LEVEL);
    printf("\n������: 'L'\n");
    printf("�޴��� ���ư��� : 'ESC'\n");

    while (1)
    {
        if (GetAsyncKeyState(0x4C) & 0x0001) // 'L' Ű�� ������ ������ �õ�
        {
            levelUp(money);
        }

        if (GetAsyncKeyState(VK_ESCAPE) & 0x0001)
        {
            system("cls");
            break;
        }

        Sleep(100);
    }
}
#pragma endregion

#pragma region ��ų �ر�

void Skill_Open(int* crystal)
{
    // ��ų�� �������� ȹ�� ������ ũ����Ż ��ȭ�� ����Ѵ�.
    system("cls");
    printf("[���� ũ����Ż: %d��]\n", *crystal);
    printf("\n");
    printf("-----[ ��ų ��� ]-----\n");
    printf(" '1'. [�ϼ���] : �������� ���� ���ظ� �ش�. (1 ũ����Ż) - Ŭ���� 1�� �߰� ����.\n");
    printf("-----------------------\n");
    printf("\n");
    printf("������ ��ų�� ��ȣ�� �Է����ּ���.\n");
    printf("���ư��� : 'ESC'\n");
}

#pragma endregion


#pragma region ���� ���

#pragma endregion


#pragma region �޴� ���
void Menu(int* money, int* click_value)
{
    system("cls");
    printf("-----[ �޴� ]-----\n");
    printf("1. ���� ����\n");
    printf("2. ���� Ȯ��\n");
    printf("3. ���� �޴�\n");
    printf("�޴� ������: 'ESC'\n");

    while (1)
    {
        // '1' �� ������ �� ���� ����
        if (GetAsyncKeyState(0x31) & 0x0001)
        {
            openShop(money, click_value); // ���� ����
            break;
        }

        // '2' �� ������ �� ���� Ȯ��
        if (GetAsyncKeyState(0x32) & 0x0001)
        {
            showAchievements(); // ���� Ȯ��
            break;
        }

        // '3' �� ������ �� ���� �޴� ����
        if (GetAsyncKeyState(0x33) & 0x0001)
        {
            LevelInfo(money); // ���� �޴�
            break;
        }

        // 'ESC' Ű�� ������ �� �޴� ������
        if (GetAsyncKeyState(VK_ESCAPE) & 0x0001)
        {
            system("cls");
            break; // �޴� ������
        }

        Sleep(100);
    }
}
#pragma endregion



int main()
{
    int money = 0;
    int click_value = 1; // Ŭ���� ������ ��
    int crystal = 0;

    printf("-----[ ����Ű ]-----\n");
    printf("�����̽��� : �� ����\n");
    printf("M : �޴� ���� (����/����)\n");

    while (1)
    {
        // �����̽��ٷ� �� ����
        if (GetAsyncKeyState(VK_SPACE) & 0x0001)
        {
            system("cls");
            money += click_value;
            printf("�ݾ� : %d\n", money);
            printf("�����̽��� : �� ����\n");
            printf("M : �޴� ���� (����/����)\n");

            // ���� üũ �Լ� ȣ��
            Achievements(money);
        }

        // �޴� ����
        if (GetAsyncKeyState(0x4D) & 0x0001) // 'M' �� ������ ��
        {
            Menu(&money, &click_value); // �޴� ����
        }

        Sleep(100);
    }

    return 0;
}
