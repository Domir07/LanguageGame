#include <stdio.h>
#include <windows.h>

void clearInputBuffer() // 매우 중요한 기능
{
    while (getchar() != '\n');  // 버퍼에 남아 있는 문자를 모두 제거
}

#pragma region 변수 짬뽕
int victory_count = 0;  // 전투 승리 횟수
#pragma region 잡다한 변수

#define LEVEL_UP_MONEY 100 // 초기 레벨업 비용
#define MAX_LEVEL 100 // 최대 레벨 설정

// 업적 달성 여부 변수 (0 = 미달성, 1 = 달성)
int a_100 = 0;
int a_500 = 0;
int a_1000 = 0;
int a_10000 = 0;

// 레벨 변수
int level = 0; // 현재 레벨
int level_up_money = LEVEL_UP_MONEY; // 레벨업에 필요한 돈

// 플레이어 기본 정보
char player_name[100];
int player_maxhp = 100;
int player_hp = 100;
int player_attack = 10;
int player_mp = 100;
int player_maxmp = 100;

// 괴물 기본 정보
const char* monster_name = "어린 쥐";
int monster_maxhp = 50;
int monster_level = 0;
int monster_hp = 50;
int monster_attack = 5;

// 그 외 재화
int crystal = 100;
#pragma endregion

#pragma region 스킬 구입 여부 변수

int skill_hasegi = 0; // 하세기 스킬 구입 여부
int skill_sweepingblade = 0; // 소리에게돈
int skill_soriegedon = 0; // 일도양단

#pragma endregion

#pragma region 스킬 필요 마나

#define HASEGI_MANA_COST 10 // 하세기 마나 소모량
#define SWEEPINGBLADE_COST 20 // 소리에게돈 마나 소모량
#define SORIEGEDON_MANA_COST 100 // 일도양단

#pragma endregion

#pragma region 장비 구매 여부 변수

int p_sword = 0;  // 녹슨 검 구매 여부 (0: 미구매, 1: 구매)
int p_padding = 0;      // 패딩 구매 여부
int p_book = 0;   // 두꺼운 책 구매 여부

#pragma endregion


#pragma endregion

#pragma region 플레이어 괴물 정보

void PlayerStats_Up()
{
    player_attack = 10 + level * 2; // 레벨에 따라 공격력 증가
    player_maxhp = 100 + level * 10; // 레벨에 따라 최대 체력 증가
    player_hp = player_maxhp; // 레벨업 시 체력 회복
    player_mp = player_maxmp; // 레벨업 시 마나 회복
}

void MonsterStats_Up()
{
    monster_attack = 5 + level * 2; // 레벨에 따라 몬스터 공격력 증가
    monster_hp = 50 + level * 10;
    monster_maxhp = 50 + level * 20;// 레벨에 따라 몬스터 최대 체력 증가
}

void PlayerStats()
{
    printf("-----[ 플레이어 정보 ]-----\n");
    printf("이름 : %s\n", player_name);
    printf("레벨 : %d\n", level);
    printf("체력 : %d/%d\n", player_hp, player_maxhp);
    printf("공격력 : %d\n", player_attack);
    printf("마나 : %d/%d\n", player_mp, player_maxmp);
    printf("---------------------------\n");
}

void MonsterStats()
{
    printf("-----[ 괴물 정보 ]-----\n");
    printf("이름 : %s\n", monster_name);
    printf("레벨 : %d\n", monster_level);
    printf("체력 : %d/%d\n", monster_hp, monster_maxhp);
    printf("공격력 : %d\n", monster_attack);
    printf("-----------------------\n");
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
        printf("업적 달성: 만 원 달성!\n");
    }
    if (money >= 10000 && a_10000 == 0)
    {
        a_1000 = 1;
        printf("업적 달성: 만 원 달성!\n");
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
    
    // 만 원 업적
    if (a_1000 == 1)
    {
        printf(" [달성] 만 원 벌기\n");
    }
    else
    {
        printf(" [미달성] 만 원 벌기\n");
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
        Sleep(100);
    }
}
#pragma endregion

#pragma region 상점에 딸린 장비 상점

void weaponShop(int* money)
{
    system("cls");
    printf("무기 상점에 입장했습니다.\n");
    printf("\n");
    printf("[현재 금액: %d원]\n", *money);
    printf("\n");
    printf("-----[ 상점 ]-----\n");

    // 녹슨 검 상태 출력
    if (p_sword == 0)
        printf(" '1'. 녹슨 검 (500원) : 공격력 + 5\n");
    else
        printf(" '1'. 녹슨 검 [구매 완료]\n");

    // 패딩 상태 출력
    if (p_padding == 0)
        printf(" '2'. 패딩 (1000원) : 체력 + 20\n");
    else
        printf(" '2'. 패딩 [구매 완료]\n");

    // 두꺼운 책 상태 출력
    if (p_book == 0)
        printf(" '3'. 두꺼운 책 (1000원) : 마나 + 20 \n");
    else
        printf(" '3'. 두꺼운 책 [구매 완료]\n");

    printf("------------------\n");
    printf("\n");
    printf("구매할 상품의 번호를 입력해주세요.\n");
    printf("상점 나가기 : 'ESC'\n");

    while (1)
    {
        // '1' 을 눌렀을 때, 녹슨 검 구입
        if (GetAsyncKeyState(0x31) & 0x0001)
        {
            if (p_sword == 1)  // 이미 구매한 경우
            {
                printf("이미 구매한 장비입니다!\n");
            }
            else if (*money >= 500)  // 구매 가능
            {
                *money -= 500;
                player_attack += 5;  // 공격력 증가
                p_sword = 1;  // 장비 구매 완료
                printf("녹슨 검을 구입했습니다! 공격력이 5 증가했습니다.\n");
            }
            else
            {
                printf("돈이 부족합니다!\n");
            }
        }

        // '2' 를 눌렀을 때, 패딩 구입
        if (GetAsyncKeyState(0x32) & 0x0001)
        {
            if (p_padding == 1)  // 이미 구매한 경우
            {
                printf("이미 구매한 장비입니다!\n");
            }
            else if (*money >= 1000)  // 구매 가능
            {
                *money -= 1000;
                player_maxhp += 20;  // 최대체력 증가
                player_hp = player_maxhp;  // 최대체력 회복
                p_padding = 1;  // 장비 구매 완료
                printf("패딩을 구입했습니다! 체력이 20 증가했습니다.\n");
            }
            else
            {
                printf("돈이 부족합니다!\n");
            }
        }

        // '3' 을 눌렀을 때, 두꺼운 책 구입
        if (GetAsyncKeyState(0x33) & 0x0001)
        {
            if (p_book == 1)  // 이미 구매한 경우
            {
                printf("이미 구매한 장비입니다!\n");
            }
            else if (*money >= 1000)
            {
                *money -= 1000;
                player_maxmp += 20;  // 최대마나 증가
                player_mp = player_maxmp;  // 마나 회복
                p_book = 1;  // 장비 구매 완료
                printf("두꺼운 책을 구입했습니다! 마나가 20 증가했습니다.\n");
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
            Sleep(1000);
            break;
        }

        Sleep(100);
    }

    system("cls");
}

#pragma endregion

#pragma region 스킬 해금
void Skill_Open(int* crystal)
{
    system("cls");
    printf("[보유 크리스탈: %d]\n", *crystal);
    printf("\n");
    printf("구매할 스킬의 번호를 눌러주세요. \n");
    printf("-----[ 스킬 목록 ]-----\n");

    // 스킬이 이미 구매된 경우 "[구매 완료]" 표시 추가
    if (skill_hasegi == 0) {
        printf(" '1'. [하세기] : 20 마나를 소모해, 괴물에게 공격력(+10)의 피해를 준다. (1 크리스탈)\n");
    }
    else {
        printf(" '1'. [하세기] [구매 완료]\n");
    }

    if (skill_sweepingblade == 0) {
        printf(" '2'. [질풍검] : 30 마나를 소모해, 괴물에게 공격력(+20)의 피해를 준다. (5 크리스탈)\n");
    }
    else {
        printf(" '2'. [질풍검] [구매 완료]\n");
    }

    if (skill_soriegedon == 0) {
        printf(" '3'. [소리에게돈] : 100 마나를 소모해, 괴물에게 공격력(+100)의 피해를 준다. (10 크리스탈)\n");
    }
    else {
        printf(" '3'. [소리에게돈] [구매 완료]\n");
    }

    printf(" 'ESC' : 나가기 \n");
    printf("-----------------------\n");
    printf("\n");

    while (1)
    {
        // '1' 을 눌렀을 때 하세기 스킬 구매
        if (GetAsyncKeyState(0x31) & 0x0001)
        {
            if (skill_hasegi == 1)  // 이미 구매한 경우
            {
                printf("이미 [하세기] 스킬을 구매했습니다!\n");
            }
            else if (*crystal >= 1)
            {
                *crystal -= 1;
                skill_hasegi = 1; // 하세기 스킬 구입 완료
                printf("[하세기] 스킬을 획득했습니다!\n");
            }
            else
            {
                printf("크리스탈이 부족합니다!\n");
            }
        }

        // '2' 을 눌렀을 때 소리에게돈 스킬 구매 시도
        if (GetAsyncKeyState(0x32) & 0x0001)
        {
            if (skill_sweepingblade == 1)  // 이미 구매한 경우
            {
                printf("이미 [질풍검] 스킬을 구매했습니다!\n");
            }
            else if (*crystal >= 5)
            {
                *crystal -= 5;
                skill_sweepingblade = 1;  // 스킬 구매 완료
                printf("[질풍검] 스킬을 획득했습니다!\n");
            }
            else
            {
                printf("크리스탈이 부족합니다!\n");
            }
        }

        // '3' 을 눌렀을 때 일도양단 스킬 구매 시도
        if (GetAsyncKeyState(0x33) & 0x0001)
        {
            if (skill_soriegedon == 1)  // 이미 구매한 경우
            {
                printf("이미 [소리에게돈] 스킬을 구매했습니다!\n");
            }
            else if (*crystal >= 10)
            {
                *crystal -= 10;
                skill_soriegedon = 1;  // 스킬 구매 완료
                printf("[소리에게돈] 스킬을 획득했습니다!\n");
            }
            else
            {
                printf("크리스탈이 부족합니다!\n");
            }
        }

        // 'ESC' 키를 눌렀을 때 바로 상점 나가기
        if (GetAsyncKeyState(VK_ESCAPE) & 0x0001)
        {
            printf("스킬 상점을 나갑니다.\n");
            Sleep(1000);
            system("cls");
            // ESC 키 입력을 초기화
            GetAsyncKeyState(VK_ESCAPE);
            break;
        }

        Sleep(100);
    }
}

#pragma endregion

#pragma region 스킬창

// 사용할 수 있는 스킬이 없으면 창을 열지 않음.
int checkAvailableSkills()
{
    return skill_hasegi || skill_sweepingblade; skill_soriegedon; // 하나라도 보유한 스킬이 있으면 true(1), 없으면 false(0)
}

void Skill_Use()
{
    int choice = 0;
    system("cls");
    printf("마나: %d/%d\n", player_mp, player_maxmp);
    printf("사용 가능한 스킬 목록 :\n");

    // 스킬이 하나도 없을 때 메시지 출력
    if (!checkAvailableSkills()) {
        printf("사용할 수 있는 스킬이 없습니다.\n");
        Sleep(2000); // 2초 대기 후 스킬창 닫기
        system("cls");
        return;
    }

    // 보유한 스킬에 따라서 출력
    if (skill_hasegi == 1)
    {
        printf(" '1'. [하세기] : 괴물에게 %d의 피해를 준다. (소모 마나: %d)\n", player_attack + 10, HASEGI_MANA_COST);
    }
    if (skill_sweepingblade == 1)
    {
        printf(" '2'. [질풍검] : 괴물에게 %d의 피해를 준다. (소모 마나: %d)\n", player_attack + 20, SWEEPINGBLADE_COST);
    }
    if (skill_soriegedon == 1)
    {
        printf(" '3'. [소리에게돈] : 괴물에게 %d의 피해를 준다. (소모 마나: %d)\n", player_attack + 100, SORIEGEDON_MANA_COST);
    }

    printf("\n스킬을 사용하지 않으려면 '4'를 입력하세요.\n");

    // 스킬 입력 전에 입력 버퍼를 초기화
    clearInputBuffer();
    printf("번호를 입력하세요 : ");
    scanf_s("%d", &choice);

    while (1) {
        // '1' 을 눌렀을 때 하세기 스킬 사용
        if (choice == 1) {
            if (player_mp >= HASEGI_MANA_COST) {
                int hasegi_damage = player_attack + 10;
                printf("%s가 [하세기] 스킬을 사용해 %s에게 %d의 피해를 입혔습니다!\n", player_name, monster_name, hasegi_damage);
                monster_hp -= hasegi_damage;
                player_mp -= HASEGI_MANA_COST; // 마나 소모
                printf("남은 마나: %d/%d\n", player_mp, player_maxmp);
                Sleep(2000); // 출력된 내용이 보일 수 있도록 2초 대기
                system("cls");
                return; // 턴 종료
            }
            else {
                printf("마나가 부족합니다! (현재 마나: %d)\n", player_mp);
                Sleep(2000); // 마나 부족 메시지가 보이도록 2초 대기
            }
        }

        // '2' 을 눌렀을 때 질풍검 스킬 사용
        if (choice == 2) {
            if (player_mp >= SWEEPINGBLADE_COST) {
                int sweepingblade_damage = player_attack + 20;
                printf("%s가 [질풍검] 스킬을 사용해 %s에게 %d의 피해를 입혔습니다!\n", player_name, monster_name, sweepingblade_damage);
                monster_hp -= sweepingblade_damage;
                player_mp -= SWEEPINGBLADE_COST; // 마나 소모
                printf("남은 마나: %d/%d\n", player_mp, player_maxmp);
                Sleep(2000);
                system("cls");
                return; // 턴 종료
            }
            else {
                printf("마나가 부족합니다! (현재 마나: %d)\n", player_mp);
                Sleep(2000); // 마나 부족 메시지가 보이도록 2초 대기
            }
        }

        // '3' 을 눌렀을 때 소리에게돈 스킬 사용
        if (choice == 3)
        {
            if (player_mp >= SORIEGEDON_MANA_COST) {
                int soriegedon_damage = player_attack + 100;
                printf("%s가 [소리에게돈] 스킬을 사용해 %s에게 %d의 피해를 입혔습니다!\n", player_name, monster_name, soriegedon_damage);
                monster_hp -= soriegedon_damage;
                player_mp -= SORIEGEDON_MANA_COST; // 마나 소모
                printf("남은 마나: %d/%d\n", player_mp, player_maxmp);
                Sleep(2000);
                system("cls");
                return; // 턴 종료
            }
            else {
                printf("마나가 부족합니다! (현재 마나: %d)\n", player_mp);
                Sleep(2000); // 마나 부족 메시지가 보이도록 2초 대기
            }
        }

        if (choice == 4) {
            printf("스킬 창을 닫습니다.\n");
            Sleep(1000); // 스킬창 닫기 메시지 1초 대기
            system("cls");
            return; // 플레이어 턴 유지 (턴이 넘어가지 않음)
        }

        Sleep(100);
    }
}

#pragma endregion

#pragma region 상점 기능

// 상점 기능 함수
void openShop(int* money, int* click_value, int *player_hp)
{
    // 클릭당 수입 증가 초기 비용 설정
    static int click_value_cost = 100;

    system("cls");
    printf("상점에 입장했습니다.\n");
    printf("\n");
    printf("[현재 금액: %d원]\n", *money);
    printf("\n");
    printf("-----[ 상점 ]-----\n");
    printf(" '1'. 클릭당 수입 증가 (100원) : 클릭당 1원 추가 벌기.\n");
    printf(" '2'. 회복 물약 (50원) : 플레이어 체력 20 회복.\n");
    printf(" '3'. 무기 상점 열기.\n");
    printf(" '4'. 스킬 상점 열기.\n");
    printf("------------------\n");
    printf("\n");
    printf("선택, 구매할 상품의 번호를 입력해주세요.\n");
    printf("상점 나가기 : 'ESC'\n");

    while (1)
    {
        // '1' 을 눌렀을 때, 클릭당 수입 증가
        if (GetAsyncKeyState(0x31) & 0x0001)
        {
            if (*money >= click_value_cost)
            {
                *money -= click_value_cost;
                (*click_value)++; // 클릭당 수입 증가
                printf("<클릭당 수입이 증가했습니다!>\n");

                // 클릭당 수입 증가 비용을 2배로 늘림
                click_value_cost *= 2;

                printf("다음 클릭당 수입 증가 비용: %d원\n", click_value_cost);
            }
            else
            {
                printf("돈이 부족합니다!\n");
            }
        }

        // '2' 를 눌렀을 때 체력 회복
        if (GetAsyncKeyState(0x32) & 0x0001)
        {
            if (*money >= 50)
            {
                *money -= 50;
                *player_hp += 20;
                if (*player_hp > player_maxhp) *player_hp = player_maxhp; // 최대 체력을 넘지 않도록
                printf("<체력이 회복되었습니다! 현재 체력: %d/%d>\n", *player_hp, player_maxhp);
            }
            else
            {
                printf("돈이 부족합니다!\n");
            }
        }

        // '3' 를 눌렀을 때 무기 상점 입장
        if (GetAsyncKeyState(0x33) & 0x0001)
        {
            weaponShop(money);
        }

        // '4' 를 눌렀을 때 스킬 상점 입장
        if (GetAsyncKeyState(0x34) & 0x0001)
        {
            Skill_Open(&crystal);
        }

        // 'ESC' 키를 눌렀을 때 상점 나가기
        if (GetAsyncKeyState(VK_ESCAPE) & 0x0001)
        {
            printf("상점을 나갑니다.\n");
            Sleep(1000);
            break; // 상점 나가기
        }

        Sleep(100);
    }

    system("cls"); // 채팅청소
}
#pragma endregion

#pragma region 던전 기능

void enterDungeon(int* money)
{
    clearInputBuffer();
    system("cls");
    printf("던전에 입장했습니다.\n");

    Sleep(1000);

    PlayerStats_Up();
    MonsterStats_Up();  // 던전 입장 시마다 몬스터 스탯을 초기화

    PlayerStats();
    MonsterStats();



    // 전투 시작
    while (player_hp > 0 && monster_hp > 0)
    {
        int skill_choice = 0;

        printf("현재 상태: \n");
        printf("%s의 체력: %d/%d\n", player_name, player_hp, player_maxhp);
        printf("%s의 마나: %d/%d\n", player_name, player_mp, player_maxmp);
        printf("---------------------------------\n");
        printf("%s의 체력: %d/%d\n", monster_name, monster_hp, monster_maxhp);

        // 플레이어의 스킬 선택
        printf("\n어떤 행동을 하시겠습니까?\n");
        printf("1. %s 정보\n", player_name);
        printf("2. 일반 공격 (마나 20 회복)\n");
        printf("3. 회복 (플레이어 체력 20 회복)\n");
        printf("4. 스킬 목록\n");  // 항상 스킬 목록은 표시되지만, 들어가면 사용 가능한 스킬이 없다면 "사용할 수 있는 스킬이 없습니다."를 출력
        printf("5. 전투 이탈\n");
        printf("번호를 입력해주세요 : ");
        scanf_s("%d", &skill_choice);

        system("cls");

        if (skill_choice == 1)
        {
            printf("-----[ %s 정보 ]-----\n", player_name);
            printf("이름 : %s\n", player_name);
            printf("레벨 : %d\n", level);
            printf("체력 : %d/%d\n", player_hp, player_maxhp);
            printf("공격력 : %d\n", player_attack);
            printf("마나 : %d/%d\n", player_mp, player_maxmp);
            printf("---------------------------\n");
        }

        if (skill_choice == 2) { // 일반 공격
            printf("%s의 공격! %s에게 %d의 피해를 입혔습니다.\n", player_name, monster_name, player_attack);
            monster_hp -= player_attack; // 괴물 HP를 플레이어 공격력만큼 뺀다

            // 마나 회복
            int mana_plus = 20;
            player_mp += mana_plus;
            if (player_mp > player_maxmp) player_mp = player_maxmp; // 최대 마나를 넘지 않도록 조정
            printf("일반 공격으로 마나가 %d 회복되었습니다. 현재 마나: %d/%d\n", mana_plus, player_mp, player_maxmp);

        }
        else if (skill_choice == 3) // 체력 회복
        {
            int heal = player_maxhp * 0.2;  // 최대 체력의 20% 회복
            player_hp += heal;
            if (player_hp > player_maxhp) player_hp = player_maxhp;  // 최대 체력을 넘지 않도록 조정
            printf("%s가 체력을 %d 회복했습니다! 현재 체력: %d/%d\n", player_name, heal, player_hp, player_maxhp);
        }
        else if (skill_choice == 4) // 스킬창
        {
            Skill_Use();

        }
        else if (skill_choice == 5) // 도망가기
        {
            printf("전투에서 이탈합니다.\n");
            Sleep(1000);
            break;

        }
        else { // 잘못된 입력
            printf("잘못된 선택입니다. 다시 시도해주세요.\n");
            continue;
        }

        Sleep(1000);
        if (monster_hp <= 0)
        {
            printf("%s을(를) 물리쳤습니다!\n", monster_name);
            crystal++; // 크리스탈 획득
            victory_count++; // 승리 횟수 증가
            printf("크리스탈을 1개 획득했습니다. 보유 크리스탈 : %d\n", crystal);
            printf("현재 전투 승리 횟수: %d/50\n", victory_count);

            // 50번 승리 시 엔딩 출력
            if (victory_count >= 50)
            {
                printf("축하합니다! 50번의 전투에서 승리하여 게임을 클리어하셨습니다!\n");
                printf("게임 엔딩을 감상해주세요...\n");
                Sleep(1000);
                printf("THE END\n");
                exit(0);  // 게임 종료
            }

            break;
        }

        // 몬스터 턴
        printf("%s의 공격! 플레이어에게 %d의 피해를 입혔습니다.\n", monster_name, monster_attack);
        player_hp -= monster_attack;
        if (player_hp <= 0) {
            printf("%s이(가) 사망했습니다.\n", player_name);
            exit(0);
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
    printf("메뉴 나가기 / 돈 벌기 : 'ESC'\n");

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
            openShop(money, click_value, player_hp, player_maxhp); // 상점 열기
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
    printf("현재 이름 설정할때 m이나 ㅡ를 입력하면 간단한 튜토리얼이 스킵되고 메뉴로 이동되는 현상이 있습니다!\n");
    printf("\n");
    printf("플레이어의 이름을 입력하세요 : ");

    scanf_s("%s", player_name, 100);

    while (1)
    {
        if (strlen(player_name) < 2)
        {
            printf("이름이 너무 짧습니다! 다시 입력해주세요.\n");
            scanf_s("%s", player_name, 100);
        }
        else
        {
            break;
        }
    }


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
