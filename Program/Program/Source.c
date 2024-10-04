#include <stdio.h>
#include <windows.h>

#pragma region ���� «��

#pragma region ����� ����

#define LEVEL_UP_MONEY 100 // �ʱ� ������ ���
#define MAX_LEVEL 100 // �ִ� ���� ����

// ���� �޼� ���� ���� (0 = �̴޼�, 1 = �޼�)
int a_100 = 0;
int a_500 = 0;
int a_1000 = 0;
int a_10000 = 0;

// ���� ����
int level = 1; // ���� ����
int level_up_money = LEVEL_UP_MONEY; // �������� �ʿ��� ��

// �÷��̾� �⺻ ����
char player_name[100];
int player_maxhp = 100;
int player_hp = 100;
int player_attack = 10;
int player_mp = 100;
int player_maxmp = 100;

// ���� �⺻ ����
const char* monster_name = "� ��";
int monster_maxhp = 50;
int monster_level = 1;
int monster_hp = 50;
int monster_attack = 5;

// �� �� ��ȭ
int crystal = 0;
#pragma endregion

#pragma region ��ų ���� ���� ����

int skill_hasegi = 0; // �ϼ��� ��ų ���� ����
int skill_soriegedon = 0;

#pragma endregion

#pragma region ��ų �ʿ� ����

#define HASEGI_MANA_COST 10 // �ϼ��� ���� �Ҹ�
#define SORIEGEDON_MANA_COST 20 // �Ҹ����Ե� ���� �Ҹ�

#pragma endregion

#pragma region ��� ���� ���� ����

int p_sword = 0;  // �콼 �� ���� ���� (0: �̱���, 1: ����)
int p_padding = 0;      // �е� ���� ����
int p_book = 0;   // �β��� å ���� ����

#pragma endregion


#pragma endregion

#pragma region �÷��̾� ���� ����

void PlayerStats_Up()
{
    player_attack = 10 + level * 2; // ������ ���� ���ݷ� ����
    player_maxhp = 100 + level * 10; // ������ ���� �ִ� ü�� ����
    player_hp = player_maxhp; // ������ �� ü�� ȸ��
    player_mp = player_maxmp; // ������ �� ���� ȸ��
}

void MonsterStats_Up()
{
    monster_attack = 5 + level * 2; // ������ ���� ���� ���ݷ� ����
    monster_hp = 50 + level * 10;
    monster_maxhp = 50 + level * 10;// ������ ���� ���� ü�� ����
}

void PlayerStats()
{
    PlayerStats_Up(); // �÷��̾��� ������ ������Ʈ

    printf("-----[ �÷��̾� ���� ]-----\n");
    printf("�̸� : %s\n", player_name);
    printf("���� : %d\n", level);
    printf("ü�� : %d/%d\n", player_hp, player_maxhp);
    printf("���ݷ� : %d\n", player_attack);
    printf("---------------------------\n");
}

void MonsterStats()
{
    printf("-----[ ���� ���� ]-----\n");
    printf("�̸� : %s\n", monster_name);
    printf("���� : %d\n", monster_level);
    printf("ü�� : %d/%d\n", monster_hp, monster_maxhp);
    printf("���ݷ� : %d\n", monster_attack);
    printf("-----------------------\n");
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

        // ������ �� �÷��̾��� ���� ������Ʈ
        PlayerStats_Up();

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
        printf("���� �޼�: �� �� �޼�!\n");
    }
    if (money >= 10000 && a_10000 == 0)
    {
        a_1000 = 1;
        printf("���� �޼�: �� �� �޼�!\n");
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
    
    // �� �� ����
    if (a_1000 == 1)
    {
        printf(" [�޼�] �� �� ����\n");
    }
    else
    {
        printf(" [�̴޼�] �� �� ����\n");
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
        Sleep(100);
    }
}
#pragma endregion





#pragma region ���� ���

#pragma region ������ ���� ��� ����

void weaponShop(int* money)
{
    system("cls");
    printf("���� ������ �����߽��ϴ�.\n");
    printf("\n");
    printf("[���� �ݾ�: %d��]\n", *money);
    printf("\n");
    printf("-----[ ���� ]-----\n");

    // �콼 �� ���� ���
    if (rusty_sword_bought == 0)
        printf(" '1'. �콼 �� (500��) : ���ݷ� + 5\n");
    else
        printf(" '1'. �콼 �� [���� �Ϸ�]\n");

    // �е� ���� ���
    if (padding_bought == 0)
        printf(" '2'. �е� (1000��) : ü�� + 20\n");
    else
        printf(" '2'. �е� [���� �Ϸ�]\n");

    // �β��� å ���� ���
    if (thick_book_bought == 0)
        printf(" '3'. �β��� å (1000��) : ���� + 20 \n");
    else
        printf(" '3'. �β��� å [���� �Ϸ�]\n");

    printf("------------------\n");
    printf("\n");
    printf("������ ��ǰ�� ��ȣ�� �Է����ּ���.\n");
    printf("���� ������ : 'ESC'\n");

    while (1)
    {
        // '1' �� ������ ��, �콼 �� ����
        if (GetAsyncKeyState(0x31) & 0x0001)
        {
            if (rusty_sword_bought == 1)  // �̹� ������ ���
            {
                printf("�̹� ������ ����Դϴ�!\n");
            }
            else if (*money >= 500)  // ���� ����
            {
                *money -= 500;
                player_attack += 5;  // ���ݷ� ����
                rusty_sword_bought = 1;  // ��� ���� �Ϸ�
                printf("�콼 ���� �����߽��ϴ�! ���ݷ��� 5 �����߽��ϴ�.\n");
            }
            else
            {
                printf("���� �����մϴ�!\n");
            }
        }

        // '2' �� ������ ��, �е� ����
        if (GetAsyncKeyState(0x32) & 0x0001)
        {
            if (padding_bought == 1)  // �̹� ������ ���
            {
                printf("�̹� ������ ����Դϴ�!\n");
            }
            else if (*money >= 1000)  // ���� ����
            {
                *money -= 1000;
                player_maxhp += 20;  // �ִ�ü�� ����
                player_hp = player_maxhp;  // �ִ�ü�� ȸ��
                padding_bought = 1;  // ��� ���� �Ϸ�
                printf("�е��� �����߽��ϴ�! ü���� 20 �����߽��ϴ�.\n");
            }
            else
            {
                printf("���� �����մϴ�!\n");
            }
        }

        // '3' �� ������ ��, �β��� å ����
        if (GetAsyncKeyState(0x33) & 0x0001)
        {
            if (thick_book_bought == 1)  // �̹� ������ ���
            {
                printf("�̹� ������ ����Դϴ�!\n");
            }
            else if (*money >= 1000)
            {
                *money -= 1000;
                player_maxmp += 20;  // �ִ븶�� ����
                player_mp = player_maxmp;  // ���� ȸ��
                thick_book_bought = 1;  // ��� ���� �Ϸ�
                printf("�β��� å�� �����߽��ϴ�! ������ 20 �����߽��ϴ�.\n");
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
            Sleep(1000);
            break;
        }

        Sleep(100);
    }

    system("cls");
}

#pragma endregion

// ���� ��� �Լ�
void openShop(int* money, int* click_value, int *player_hp)
{
    system("cls");
    printf("������ �����߽��ϴ�.\n");
    printf("\n");
    printf("[���� �ݾ�: %d��]\n", *money);
    printf("\n");
    printf("-----[ ���� ]-----\n");
    printf(" '1'. Ŭ���� ���� ���� (100��) : Ŭ���� 1�� �߰� ����.\n");
    printf(" '2'. ȸ�� ���� (50��) : �÷��̾� ü�� 20 ȸ��.\n");
    printf(" '3'. ���� ���� \n");
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

        // '2' �� ������ �� ü�� ȸ��
        if (GetAsyncKeyState(0x32) & 0x0001)
        {
            if (*money >= 50)
            {
                *money -= 50;
                *player_hp += 20;
                if (*player_hp > player_maxhp) *player_hp = player_maxhp; // �ִ� ü���� ���� �ʵ���
                printf("<ü���� ȸ���Ǿ����ϴ�! ���� ü��: %d/%d>\n", *player_hp, player_maxhp);
            }
            else
            {
                printf("���� �����մϴ�!\n");
            }
        }

        // '3' �� ������ �� ���� ���� ����
        if (GetAsyncKeyState(0x33) & 0x0001)
        {

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

#pragma region ��ų �ر�

void Skill_Open(int* crystal)
{
    system("cls");
    printf("[���� ũ����Ż: %d]\n", *crystal);
    printf("\n");
    printf("-----[ ��ų ��� ]-----\n");
    printf(" '1'. [�ϼ���] : �������� ���ݷ�(+10)�� ���ظ� �ش�. (3 ũ����Ż)\n");
    printf(" '2'. [�Ҹ����Ե�] : �������� ���ݷ�(+20)�� ���ظ� �ش�. (10 ũ����Ż)\n");
    printf("-----------------------\n");
    printf("\n");

    int shop_num = 0;
    printf("������ ��ų�� ��ȣ�� �Է����ּ��� : ");
    scanf_s("%d", &shop_num);

    if (shop_num == 1)
    {
        if (*crystal >= 3)
        {
            *crystal -= 3;
            skill_hasegi = 1; // �ϼ��� ��ų ���� �Ϸ�
            printf("[�ϼ���] ��ų�� ȹ���߽��ϴ�!\n");
        }
        else
        {
            printf("ũ����Ż�� �����մϴ�.\n");
        }
    }

    if (shop_num == 2)
    {
        if (*crystal >= 10)
        {
            *crystal -= 10;
            skill_soriegedon = 1;
            printf("[�Ҹ����Ե�] ��ų�� ȹ���߽��ϴ�!\n");
        }
        else
        {
            printf("ũ����Ż�� �����մϴ�.\n");
        }
    }
}

#pragma endregion

#pragma region ��ųâ

void Skill_Use()
{
    system("cls");

    printf("��� ������ ��ų ���:\n");

    // ������ ��ų�� ���� ���
    if (skill_hasegi == 1)
    {
        printf(" '1'. [�ϼ���] : �������� ���ݷ�(+10)�� ���ظ� �ش�. (�Ҹ� ����: %d)\n", HASEGI_MANA_COST);
    }
    if (skill_soriegedon == 1)
    {
        printf(" '2'. [�Ҹ����Ե�] : �������� ���ݷ�(+20)�� ���ظ� �ش�. (�Ҹ� ����: %d)\n", SORIEGEDON_MANA_COST);
    }

    printf("\n��ų�� ������� �������� 'ESC'�� ��������.\n");

    while (1)
    {
        // '1' �� ������ �� �ϼ��� ��ų ���
        if (GetAsyncKeyState(0x31) & 0x0001 && skill_hasegi == 1)
        {
            if (player_mp >= HASEGI_MANA_COST)
            {
                int hasegi_damage = player_attack + 10;
                printf("%s�� [�ϼ���] ��ų�� ����� %s���� %d�� ���ظ� �������ϴ�!\n", player_name, monster_name, hasegi_damage);
                monster_hp -= hasegi_damage;
                player_mp -= HASEGI_MANA_COST; // ���� �Ҹ�
                printf("���� ����: %d/%d\n", player_mp, player_maxmp);
                break;
            }
            else
            {
                printf("������ �����մϴ�! (���� ����: %d)\n", player_mp);
            }
        }
        // '2' �� ������ �� �Ҹ����Ե� ��ų ���
        if (GetAsyncKeyState(0x32) & 0x0001 && skill_soriegedon == 1)
        {
            if (player_mp >= SORIEGEDON_MANA_COST)
            {
                int soriegedon_damage = player_attack + 20;
                printf("%s�� [�Ҹ����Ե�] ��ų�� ����� %s���� %d�� ���ظ� �������ϴ�!\n", player_name, monster_name, soriegedon_damage);
                monster_hp -= soriegedon_damage;
                player_mp -= SORIEGEDON_MANA_COST; // ���� �Ҹ�
                printf("���� ����: %d/%d\n", player_mp, player_maxmp);
                break;
            }
            else
            {
                printf("������ �����մϴ�! (���� ����: %d)\n", player_mp);
            }
        }

        // 'ESC' �� ������ �� ��ų â ������
        if (GetAsyncKeyState(VK_ESCAPE) & 0x0001)
        {
            printf("��ų â�� �ݽ��ϴ�.\n");
            Sleep(1000);
            break;
        }

        Sleep(100);
    }

    system("cls");
}

#pragma endregion

#pragma region ���� ���

void enterDungeon(int* money)
{
    system("cls");
    printf("������ �����߽��ϴ�.\n");

    Sleep(1000);

    PlayerStats_Up();
    // ���� ���� �ʱ�ȭ
    MonsterStats_Up();  // ���� ���� �ø��� ���� ������ �ʱ�ȭ

    // �÷��̾�� ���� ���� �ε�
    PlayerStats();
    Sleep(1000);
    MonsterStats();
    Sleep(1000);

    // ���� ����
    while (player_hp > 0 && monster_hp > 0) // �÷��̾�, ���� HP�� 0�� �� ������ �ݺ�
    {
        while (getchar() != '\n');

        int skill_choice = 0;

        // �÷��̾�� ������ ���� ü�� ���� ǥ��
        printf("���� ����: \n");
        printf("�÷��̾� ü��: %d/%d\n", player_hp, player_maxhp);
        printf("�÷��̾� ����: %d/%d\n", player_mp, player_maxmp);  // ���� ���µ� ǥ��
        printf("���� ü��: %d/%d\n", monster_hp, monster_maxhp); // ���� ü�� ����

        // �÷��̾��� ��ų ����
        printf("\n� ��ų�� ����Ͻðڽ��ϱ�?\n");
        printf("1. �Ϲ� ���� (���� 20 ȸ��)\n");  // �Ϲ� ���ݿ� ���� ȸ�� ���� �߰�
        printf("2. ȸ�� (�÷��̾� ü�� 20 ȸ��)\n");
        printf("3. ��ų ���\n");
        printf("0. ���� ��Ż\n");
        printf("��ȣ�� �Է����ּ��� : ");
        scanf_s("%d", &skill_choice);

        system("cls");

        // ��ų ���ÿ� ���� �ൿ
        if (skill_choice == 1) // �Ϲ� ����
        {
            printf("%s�� ����! %s���� %d�� ���ظ� �������ϴ�.\n", player_name, monster_name, player_attack);
            monster_hp -= player_attack; // ���� HP�� �÷��̾� ���ݷ¸�ŭ ����

            // ���� ȸ�� ���� �߰�
            int mana_plus = 20;  // �Ϲ� ���� �� ȸ���� ���� ��
            player_mp += mana_plus;
            if (player_mp > player_maxmp) player_mp = player_maxmp; // �ִ� ������ ���� �ʵ��� ����
            printf("�Ϲ� �������� ������ %d ȸ���Ǿ����ϴ�. ���� ����: %d/%d\n", mana_plus, player_mp, player_maxmp);
        }
        else if (skill_choice == 2) // ȸ��
        {
            player_hp += 20;
            if (player_hp > player_maxhp) player_hp = player_maxhp; // �ִ� ü�� ���� �ʵ��� ����
            printf("%s�� ü���� 20 ȸ���߽��ϴ�! ���� ü��: %d/%d\n", player_name, player_hp, player_maxhp);
        }
        else if (skill_choice == 3) // ��ų ���
        {
            Skill_Use();
        }
        else if (skill_choice == 4) // ����
        {
            printf("�������� ��Ż�մϴ�.\n");
            Sleep(1000);
            break;
        }
        else // �߸��� �Է� ó��
        {
            printf("�߸��� �����Դϴ�. �ٽ� �õ����ּ���.\n");
            continue; // ������ �� ���� �ٽ� ��ų �������� ���ư�
        }

        Sleep(1000);
        if (monster_hp <= 0)
        {
            printf("%s��(��) �����ƽ��ϴ�!\n", monster_name);
            crystal++; // ũ����Ż ȹ��
            printf("ũ����Ż�� 1�� ȹ���߽��ϴ�. ���� ũ����Ż : %d\n", crystal);
            break;
        }

        // ���� ��
        printf("%s�� ����! �÷��̾�� %d�� ���ظ� �������ϴ�.\n", monster_name, monster_attack);
        player_hp -= monster_attack; // �÷��̾� HP�� ������ ���ݷ¸�ŭ ����
        if (player_hp <= 0)
        {
            printf("%s��(��) ����߽��ϴ�.\n", player_name);
            exit(0); // ���� ����
        }

        Sleep(1000);
    }

    printf("������ �����ϴ�.\n");
    printf("�ƹ� Ű�� �����ּ���.\n");
}

#pragma endregion

#pragma region �޴� ���
void Menu(int* money, int* click_value)
{
    system("cls");
    printf("-----[ �޴� ]-----\n");
    printf("1. �÷��̾� ����\n");
    printf("2. ������\n");
    printf("3. ����\n");
    printf("4. ����\n");
    printf("5. ���� ����\n");
    printf("\n");
    printf("��ȣ�� �Է����ּ���.\n");
    printf("------------------\n");
    printf("�޴� ������ / �� ���� : 'ESC'\n");

    while (1)
    {
        // '1' �� ������ �� �÷��̾� ���� Ȯ��
        if (GetAsyncKeyState(0x31) & 0x0001)
        {
            system("cls");
            printf("-----[ �÷��̾� ���� ]-----\n");
            printf("�̸� : %s\n", player_name);
            printf("���� : %d\n", level);
            printf("ü�� : %d/%d\n", player_hp, player_maxhp);
            printf("���ݷ� : %d\n", player_attack);
            printf("---------------------------\n");
            printf("\n");
            printf("���ư����� 'ESC'�� �����ּ���.\n");
        }

        // '2' �� ������ �� ������ â ����
        if (GetAsyncKeyState(0x32) & 0x0001)
        {
            LevelInfo(money); // ���� �޴�
            break;
        }

        // '3' �� ������ �� ���� ����
        if (GetAsyncKeyState(0x33) & 0x0001)
        {
            openShop(money, click_value, player_hp, player_maxhp); // ���� ����
            break;
        }

        // '4' �� ������ �� ���� Ȯ��
        if (GetAsyncKeyState(0x34) & 0x0001)
        {
            showAchievements(); // ���� Ȯ��
            break;
        }

        // '5' �� ������ �� ���� ����
        if (GetAsyncKeyState(0x35) & 0x0001)
        {
            enterDungeon(money); // ���� ����
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

    // �÷��̾� �̸� ����
    printf("���� �̸� �����Ҷ� m�̳� �Ѹ� �Է��ϸ� ������ Ʃ�丮���� ��ŵ�ǰ� �޴��� �̵��Ǵ� ������ �ֽ��ϴ�!\n");
    printf("\n");
    printf("�÷��̾��� �̸��� �Է��ϼ��� : ");

    scanf_s("%s", player_name, 100);

    while (1)
    {
        if (strlen(player_name) < 2)
        {
            printf("�̸��� �ʹ� ª���ϴ�! �ٽ� �Է����ּ���.\n");
            scanf_s("%s", player_name, 100);
        }
        else
        {
            break;
        }
    }


    printf("%s��, ������ �����մϴ�!\n", player_name);
    printf("\n");
    printf("-----[ ����Ű ]-----\n");
    printf("�����̽��� : �� ����\n");  
    printf("M : �޴� ����\n");   
    while (1)
    {
        // �����̽��ٷ� �� ����
        if (GetAsyncKeyState(VK_SPACE) & 0x0001)
        {
            system("cls");
            money += click_value;
            printf("�ݾ� : %d\n", money);
            printf("�����̽��� : �� ����\n");
            printf("M : �޴� ����\n");

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
