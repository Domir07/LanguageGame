#include <stdio.h>
#include <windows.h>


#pragma region 변수 짬뽕

#define LEVEL_UP_MONEY 10 // 초기 레벨업 비용
#define MAX_LEVEL 100 // 최대 레벨 설정

// 업적 달성 여부 변수 (0 = 미달성, 1 = 달성)
int a_100 = 0;
int a_500 = 0;
int a_1000 = 0;

// 레벨 변수
int level = 1; // 현재 레벨
int level_up_money = LEVEL_UP_MONEY; // 레벨업에 필요한 돈

// 플레이어 기본 정보
char player_name[100];
int player_maxhp = 100;
int player_hp = 100;
int player_attack = 10;

// 괴물 기본 정보
const char* monster_name = "어린 쥐";
int monster_level = 1;
int monster_hp = 50;
int monster_attack = 5;

// 그 외 재화
int crystal = 0;

#pragma endregion

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

#pragma region 레벨 기능

void levelUp(int* money) // 돈을 소비해서 레벨업하는 함수
{
    if (level >= MAX_LEVEL)
    {
        printf("최대 레벨에 도달했습니다! 더 이상 레벨업할 수 없습니다.\n");
        return;
    }

    if (*money >= level_up_money) // 레벨업 비용이 충분한지 확인
    {
        *money -= level_up_money; // 돈을 소비
        level++; // 레벨 증가
        printf("레벨업!\n");
        printf("현재 레벨: %d\n", level);

        // 레벨업 후 플레이어의 스탯 업데이트
        PlayerStats_Up();

        level_up_money *= 2; // 다음 레벨업 비용 2배 증가
        printf("다음 레벨업에 필요한 금액: %d원\n", level_up_money);
    }
    else
    {
        printf("레벨업을 위해 %d원이 더 필요합니다.\n", level_up_money - *money);
    }
}

void LevelInfo(int* money) // 레벨 정보   
{
    system("cls");
    printf("-----[ 레벨 정보 ]-----\n");
    printf("현재 레벨: %d\n", level);
    printf("다음 레벨업 비용: %d원\n", level_up_money);
    printf("최대 레벨: %d\n", MAX_LEVEL);
    printf("\n레벨업: 'L'\n");
    printf("메뉴로 돌아가기 : 'ESC'\n");

    while (1)
    {
        if (GetAsyncKeyState(0x4C) & 0x0001) // 'L' 키를 누르면 레벨업 시도
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

#pragma region 플레이어 괴물 정보

void PlayerStats_Up()
{
    player_attack = 10 + level * 2; // 레벨에 따라 공격력 증가
    player_maxhp = 100 + level * 10; // 레벨에 따라 최대 체력 증가
}

void MonsterStats_Up()
{
    monster_attack = 5 + level * 2; // 레벨에 따라 몬스터 공격력 증가
    monster_hp = 50 + level * 5; // 레벨에 따라 몬스터 체력 증가
}

void PlayerStats()
{
    PlayerStats_Up(); // 플레이어의 스탯을 업데이트

    printf("-----[ 플레이어 정보 ]-----\n");
    printf("이름 : %s\n", player_name);
    printf("레벨 : %d\n", level);
    printf("체력 : %d/%d\n", player_hp, player_maxhp);
    printf("공격력 : %d\n", player_attack);
    printf("---------------------------\n");
}

void MonsterStats()
{
    printf("-----[ 괴물 정보 ]-----\n");
    printf("이름 : %s\n", monster_name);
    printf("레벨 : %d\n", monster_level);
    printf("체력 : %d\n", monster_hp);
    printf("공격력 : %d\n", monster_attack);
    printf("-----------------------\n");
}
#pragma endregion

#pragma region 스킬 해금

void Skill_Open(int* crystal)
{
    // 스킬은 던전에서 획득 가능한 크리스탈 재화를 사용한다.
    system("cls");
    printf("[보유 크리스탈: %d원]\n", *crystal);
    printf("\n");
    printf("-----[ 스킬 목록 ]-----\n");
    printf(" '1'. [하세기] : 괴물에게 물리 피해를 준다. (1 크리스탈) - 클릭당 1원 추가 벌기.\n");
    printf("-----------------------\n");
    printf("\n");
    printf("구매할 스킬의 번호를 입력해주세요.\n");
    printf("돌아가기 : 'ESC'\n");
}

#pragma endregion


#pragma region 던전 기능

void enterDungeon(int* money)
{
    system("cls");
    printf("던전에 입장했습니다.\n");

    Sleep(1000);

    // 몬스터 스탯 초기화
    MonsterStats_Up();  // 던전 입장 시마다 몬스터 스탯을 초기화

    // 플레이어와 몬스터 정보 로딩
    PlayerStats();
    Sleep(1000);
    MonsterStats();
    Sleep(1000);

    // 전투 시작
    while (player_hp > 0 && monster_hp > 0) // 플레이어, 괴물 HP가 0이 될 때까지 반복
    {
        // 플레이어 턴
        printf("%s의 공격! 에게 %d의 피해를 입혔습니다.\n", player_name, player_attack);
        monster_hp -= player_attack; // 괴물 HP를 플레이어 공격력만큼 뺀다
        Sleep(1000);
        if (monster_hp <= 0)
        {
            printf("%s을(를) 물리쳤습니다!\n", monster_name);
            crystal++; // 크리스탈 획득
            printf("크리스탈을 1개 획득했습니다. 보유 크리스탈 : %d\n", crystal);
            break;
        }

        // 몬스터 턴
        printf("%s의 공격! 플레이어에게 %d의 피해를 입혔습니다.\n", monster_name, monster_attack);
        player_hp -= monster_attack; // 플레이어 HP를 괴물의 공격력만큼 뺀다
        if (player_hp <= 0)
        {
            printf("%s이(가) 사망했습니다.\n", player_name);
            exit(0); // 게임 종료
        }

        Sleep(1000);
    }

    printf("던전을 나갑니다.\n");
    printf("아무 키나 눌러주세요.\n");
}

#pragma endregion


#pragma region 메뉴 기능
void Menu(int* money, int* click_value)
{
    system("cls");
    printf("-----[ 메뉴 ]-----\n");
    printf("1. 플레이어 정보\n");
    printf("2. 레벨업\n");
    printf("3. 상점\n");
    printf("4. 업적\n");
    printf("5. 던전 입장\n");
    printf("\n");
    printf("번호를 입력해주세요.\n");
    printf("------------------\n");
    printf("메뉴 나가기: 'ESC'\n");

    while (1)
    {
        // '1' 을 눌렀을 때 플레이어 정보 확인
        if (GetAsyncKeyState(0x31) & 0x0001)
        {
            system("cls");
            printf("-----[ 플레이어 정보 ]-----\n");
            printf("이름 : %s\n", player_name);
            printf("레벨 : %d\n", level);
            printf("체력 : %d/%d\n", player_hp, player_maxhp);
            printf("공격력 : %d\n", player_attack);
            printf("---------------------------\n");
            printf("\n");
            printf("돌아가려면 'ESC'를 눌러주세요.\n");
        }

        // '2' 를 눌렀을 때 레벨업 창 열기
        if (GetAsyncKeyState(0x32) & 0x0001)
        {
            LevelInfo(money); // 레벨 메뉴
            break;
        }

        // '3' 을 눌렀을 때 상점 열기
        if (GetAsyncKeyState(0x33) & 0x0001)
        {
            openShop(money, click_value); // 상점 열기
            break;
        }

        // '4' 를 눌렀을 때 업적 확인
        if (GetAsyncKeyState(0x34) & 0x0001)
        {
            showAchievements(); // 업적 확인
            break;
        }

        // '5' 를 눌렀을 때 던전 입장
        if (GetAsyncKeyState(0x35) & 0x0001)
        {
            enterDungeon(money); // 던전 입장
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

    // 플레이어 이름 설정
    printf("플레이어의 이름을 입력하세요 : \n");
    printf("\n");
    printf("한글로 입력하면 짧은 튜토리얼이 스킵되는 현상이 있습니다!\n");

    char name[100];
    scanf_s("%s", player_name, 100);

    printf("%s님, 게임을 시작합니다!\n", player_name);
    printf("\n");
    printf("-----[ 조작키 ]-----\n");
    printf("스페이스바 : 돈 벌기\n");
    printf("M : 메뉴 열기\n");

    while (1)
    {
        // 스페이스바로 돈 벌기
        if (GetAsyncKeyState(VK_SPACE) & 0x0001)
        {
            system("cls");
            money += click_value;
            printf("금액 : %d\n", money);
            printf("스페이스바 : 돈 벌기\n");
            printf("M : 메뉴 열기\n");

            // 업적 체크 함수 호출
            Achievements(money);
        }

        // 메뉴 열기
        if (GetAsyncKeyState(0x4D) & 0x0001) // 'M' 를 눌렀을 때
        {
            Menu(&money, &click_value); // 메뉴 열기
        }

        Sleep(100);
    }

    return 0;
}
