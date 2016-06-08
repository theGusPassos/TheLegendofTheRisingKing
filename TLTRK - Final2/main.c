#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <math.h>
#include <windows.h>

#define TXT_NUMBER 5

#define true 1
#define false 0

#define roomLength 31
#define enemyLenght 20
#define itemLenght 10

#define EASY_GAME 91
#define HARD_GAME 90

#define Soldier 1
#define Jailer 2
#define Khez 3
#define Kawrosk 4
#define Trars 5
#define Jacub 6
#define WingedOb 7
#define Blefyhl 8
#define Wulo 9
#define Gnoss 10
#define CursedOb 11
#define Atehm 12
#define Xauhnulst 13
#define Fear 14
#define Gorlab 15

#define earthmage 16
#define watermage 17
#define thundermage 18
#define firemage 19

#define locfireMage 30
#define locwaterMage 9
#define locthunderMage 13
#define locearthMage 18



unsigned int currentRoom = 0, currentEnemy = 0, enemyCurrentHP = 0, dificulty;

unsigned int lvlTemp = 0, heroNextLvl = 30, heroMaxlvl = false;

unsigned int battleTurn = 0, yourDamage, enemyDamage, enemyRandomAtk, tempDef, tempAtk;

unsigned int enDamage = false, damage = false, block = false, enStatus = false, gameRunning = true, battleRunning = false,
            mageDamage = false, doubleDamage = false, withoutMP = false;

unsigned int fireMageDead = false, thunderMageDead = false, earthMageDead = false, waterMageDead = false;

unsigned int texts[TXT_NUMBER];
unsigned int map[5][7];

void creatingRooms();
void creatingEnemies();
void saveGame();
void loadGame();
void initializerHero();
void initializerTexts();
void gameMenu();
void gameplay();
void testEvent();
void printLoc();
void choices();
void printStatus();
void showSkill();
void useSkills(int skillChoice);
void printEnemyStatus();
void printIventary();
void useItem();
void testMage();
void testEnemy();
void enemyAppear(int enemyType);
void battle();
void printHealthBar(int currentHP, int maxHP, int who);
void battleChoice(char d);
void testHerosLife(int herosLife);
void testEnemysLife(int enemyLife);
void dropItem();
void heroLvlUp();
void heroStatusLvlUp();
void printBattleOptions();
void showEquips();
void itemsTaken();
void printItensStatus(int c);
void changingEquips(char choice);
void magicAtkOptions();
void magicAtkChoice(int choice);
void atualizeMap();
void printMap();
void useStatusPoints();
void useDexPoints();
void makeAtk(int element);
void spendSkillPoint(char c);
void spendDexPoint(int c);
void testFinalGame();
void whoAppear();
void testMageLife();
void startGame();
void deadMages();
void heroActionTest();
void enemyActionTest();
void enemyAction();
void brownAtk();
void redAtk();
void whiteAtk();
void blueAtk();
int magicAtk(int element, int heroInt, int enemyDef, int enemyWeakness);
int dexForWeapon(int currentWeapon);
int experience(int enemyLvl);
int Round(float myfloat);
int countDex(int atk);
int atk(int atk, int def, int luck, int dex);
int blockCount(int def, int dex);
int findCriticalHit(int luck);
int enemyAtk(int atk, int heroDef);
float countCritical();
int findDex(int dex);
void setColor(int ForgC);

struct Room
{
    char description[40];
    int currentLoc;
    int nLocation;
    int wLocation;
    int lLocation;
    int sLocation;
    int enemyTypes;

}roomList[roomLength];

struct Enemy
{
    char name[25];
    int enemyNumber;
    int lvl;
    int hp;
    int atk;
    int def;
    int weakness;

}enemyList[enemyLenght];

struct item
{
    char name[20];
    int type;
    int atk;
    int def;
    int inT;
    int luc;

}itemList[itemLenght];

struct heroItensStatus
{
    int lvl;
    int exp;
    int currentWeapon;
    int currentShield;
    int CurrentHP;
    int CurrentMP;
    int hp;
    int mp;
    int atk;
    int def;
    int inT;
    int luc;
    int swordDex;
    int twoHandSwordDex;
    int knifeDex;
    int rodDex;
    int shieldDex;
    int dexPoints;
    int statusPoints;
    int skills;

}hero;

struct collectables
{
    int sword;
    int twoHandSword;
    int knife;
    int rod;
    int shield;

    int fireGem;
    int thunderGem;
    int waterGem;
    int earthGem;

    int hpPotion;
    int mpPotion;
} your;


void creatingRooms()
{
    char d[40];
    int c, n, w, l, s, eT, i = 0;

    FILE *file;
    file = fopen("RoomList.txt", "r");

    if(file == NULL)
        printf("\nErro na abertura do arq\n");
    else

        while(i <= roomLength)
        {
            fscanf(file, "%[^\n] %d\n%d\n%d\n%d\n%d\nt - %d\n", &d, &c, &n, &w, &l, &s, &eT);

                strcpy(roomList[i].description, d);
                roomList[i].currentLoc = c;
                roomList[i].nLocation = n;
                roomList[i].wLocation = w;
                roomList[i].lLocation = l;
                roomList[i].sLocation = s;
                roomList[i].enemyTypes = eT;

            i++;
        }
        fclose(file);
}
void creatingEnemies()
{
    char n[25];
    int i = 0;
    int eN, eLVL, mHP, atk, def, weak;


    FILE *file = fopen("EnemyList.txt", "r");
    if(file == NULL)
    {
        printf("\nErro na abertura do arquivo\n");
    }
    else
    {
        while(i <= enemyLenght)
        {
            fscanf(file, "%[^\n] %d\nl %d\nh %d\na %d\nd %d\nw %d\n", &n, &eN, &eLVL, &mHP, &atk, &def, &weak);

            strcpy(enemyList[i].name, n);
            enemyList[i].enemyNumber = eN;
            enemyList[i].lvl = eLVL;
            enemyList[i].hp = mHP;
            enemyList[i].atk = atk;
            enemyList[i].def = def;
            enemyList[i].weakness = weak;

            i++;
        }
        fclose(file);
    }
}

void creatingItems()
{

    char iName[20];
    int i = 0;
    int iType, iAtk, iDef, iLuc, iInt;

    FILE * file = fopen("itemList.txt", "r");
    if(file == NULL)
    {
        printf("\nErro na abertura do arquivo.");
    }
    else
    {
        while(i <= itemLenght)
        {
            fscanf(file, "%[^\n] %d\na %d\nd %d\ni %d\nl %d\n", &iName, &iType, &iAtk, &iDef, &iInt, &iLuc);

            strcpy(itemList[i].name, iName);
            itemList[i].type = iType;
            itemList[i].atk = iAtk;
            itemList[i].def = iDef;
            itemList[i].luc = iLuc;
            itemList[i].inT = iInt;

            i++;
        }
        fclose(file);
    }
}

void saveGame()
{
    FILE *file = fopen("SaveGame.txt", "w");

    if(file == NULL)
    {
        printf(" Falha na abertura do arquivo!\n");
    }
    else
    {
        printf("     - # Saving Game... # -\n");
        printf("\n>    ");

        fprintf(file, "%d  \n%d  \n%d  \n%d   \n", hero.lvl, hero.exp, heroNextLvl, dificulty);
        fprintf(file, "%d  \n%d  \n%d  \n%d  \n%d  \n", currentRoom, hero.CurrentHP, hero.CurrentMP, hero.currentWeapon, hero.currentShield);
        fprintf(file, "%d  \n%d  \n%d  \n%d  \n", hero.atk, hero.def, hero.luc, hero.inT);
        fprintf(file, "%d  \n%d  \n%d  \n%d  \n", your.fireGem, your.waterGem, your.thunderGem, your.earthGem);
        fprintf(file, "%d  \n%d  \n%d  \n%d  \n%d  \n", your.sword, your.twoHandSword, your.knife, your.shield, your.rod);
        fprintf(file, "%d  \n%d  \n%d  \n%d  \n", hero.swordDex, hero.twoHandSwordDex, hero.shieldDex, hero.knifeDex);
        fprintf(file, "%d  \n%d  \n", hero.dexPoints, hero.statusPoints);

        getch();
        currentEnemy = 0;
    }
}
void loadGame()
{
    FILE *file = fopen("SaveGame.txt", "r");

    int lvl, xp, nextLvl, dif;
    int thisRoom, thisHP, thisMp, thisWeapon, thisShield;
    int a, d, l, i;
    int fire, water, wind, earth;
    int s, tS, k, sh, r;
    int swordDex, twoHandSwordDex, shieldDex, knifeDex;
    int dPoints, sPoints;


    if(file == NULL)
    {
        printf(" Falha na abertura do arquivo!\n");
    }
    else
    {
        printf("    - # Loading Game... # -\n");
        printf("\n>    ");

        fscanf(file, "%d  \n%d  \n%d  \n%d  \n", &lvl, &xp, &nextLvl, &dif);
        fscanf(file, "%d  \n%d  \n%d  \n%d  \n%d  \n", &thisRoom, &thisHP, &thisMp, &thisWeapon, &thisShield);
        fscanf(file, "%d  \n%d  \n%d  \n%d  \n", &a, &d, &l, &i);
        fscanf(file, "%d  \n%d  \n%d  \n%d  \n", &fire, &water, &wind, &earth);
        fscanf(file, "%d  \n%d  \n%d  \n%d  \n%d  \n", &s, &tS, &k, &sh, &r);
        fscanf(file, "%d  \n%d  \n%d  \n%d  \n", &swordDex, &twoHandSwordDex, &shieldDex, &knifeDex);
        fscanf(file, "%d  \n%d  \n", &dPoints, &sPoints);

        hero.lvl = lvl;
        hero.exp = xp;
        heroNextLvl = nextLvl;

        currentRoom = thisRoom;
        hero.CurrentHP = thisHP;
        hero.CurrentMP = thisMp;
        hero.currentWeapon = thisWeapon;
        hero.currentShield = thisShield;

        hero.atk = a;
        hero.def = d;
        hero.luc = l;
        hero.inT = i;

        your.fireGem = fire;
        your.waterGem = wind;
        your.thunderGem = wind;
        your.earthGem = earth;

        your.sword = s;
        your.twoHandSword = tS;
        your.shield = sh;
        your.knife = k;
        your.rod = r;

        hero.swordDex = swordDex;
        hero.twoHandSwordDex = twoHandSwordDex;
        hero.shieldDex = shieldDex;
        hero.knifeDex = knifeDex;

        hero.dexPoints = dPoints;
        hero.statusPoints = sPoints;

        creatingEnemies();
        creatingRooms(0);
        creatingItems();

        gameplay(1);

        getch();
    }
}

void initializerHero(int d)
{

    if(d == 1)
        d = 0;
    else if(d == 2)
        d = 5;

    hero.lvl = 5;
    hero.exp = 0;
    hero.currentWeapon = 1;
    hero.currentShield = 0;
    hero.hp = 10 + d;
    hero.atk = 2 + d;
    hero.mp = 10;
    hero.def = 1 + d;
    hero.inT = 1;
    hero.luc = 1;
    hero.swordDex = 1;
    hero.twoHandSwordDex = 1;
    hero.knifeDex = 1;
    hero.rodDex = 1;
    hero.shieldDex = 1;
    hero.dexPoints = 0;
    hero.statusPoints = 0;
    hero.skills = 0;

    hero.CurrentHP = hero.hp;
    hero.CurrentMP = hero.mp;
    lvlTemp = hero.lvl;
}
void initializerTexts()
{
    int i;
    for(i = 0; i < TXT_NUMBER; i++)
    {
        texts[i] = 0;
    }
}

void initializerInitialItems(int d)
{
    d = d -1;

    your.sword = 1;
    your.twoHandSword = d;
    your.knife = d;
    your.shield = d;
    your.rod = d;

    your.hpPotion = 2 + d;
    your.mpPotion = 1 + d;
    your.fireGem = d;
    your.earthGem = d;
    your.thunderGem = d;
    your.waterGem = d;
}
void gameMenu()
{
    int c;

    printf("\n\n         - The Legend of the Rising King - \n");
    printf("                     One by one\n\n\n");
    printf("                   RPG made with C");
    printf("\n\n                      - # -\n");
    printf("\n\n\n                  1 - New Game\n");
    printf("                  2 - Load Game\n");
    printf("                  3 - Close Game");
    printf("\n\n>    ");
    scanf("%d", &c);

    switch(c)
    {
    case 1:
        startGame();
        break;
    case 2:
        loadGame();
        break;
    case 3:
        exit(EXIT_SUCCESS);
    default:
        printf("Type a valid option");
    }
}
void startGame()
{
    int choice;

    system("cls");

    printf("\n\n  x --  --  --  --  --  -- | --  --  --  --  --  --  x\n");
    printf("\n\n                       1 - HARD\n");
    printf("\n                       2 - VERY EASY\n");
    printf("\n>    ");

    scanf(" %d", &choice);
    dificulty = choice;

    initializerInitialItems(choice);
    initializerHero(choice);
    initializerTexts();
    creatingEnemies();
    creatingRooms();
    creatingItems();

    gameplay(0);

}

void gameplay(int i)
{
    while(gameRunning ==  true)
    {
        testFinalGame();
        testEvent();
        testMage();

        if(i != 1)
            testEnemy();

        atualizeMap();
        printLoc();
        choices();
    }
}
void testLevelUp()
{
        if(lvlTemp != hero.lvl)
        {
            system("cls");
            heroStatusLvlUp();
            printf("\n\n  x --  --  --  --  --  -- | --  --  --  --  --  --  x\n");
            printf("\n                      > Level Up <\n");
            printf("\n        You receive dexterity points and skills points!\n");
            printf("\n\n  x --  --  --  --  --  -- | --  --  --  --  --  --  x\n");

            getch();
        }
}
void testEvent()
{
    system("cls");

    if(currentRoom == 1 && texts[0] != 1)
    {
        printf("\n\n  x --  --  --  --  --  -- | --  --  --  --  --  --  x\n\n");
        printf("   To bring humanity back on top,\n\n\n");
        printf("   Kobe travel the space searching from the Four Mage Jail,\n\n\n");
        printf("   Their power will be necessary from conquering the universe.\n");

        getch();
        texts[0] = 1;
    }
    else if(currentRoom == 5 && texts[1] != 1)
    {
        printf("\n\n  x --  --  --  --  --  -- | --  --  --  --  --  --  x\n\n");
        printf("    One of then have the power to kill the other\n");
        printf("    it's your job to figure it out\n");

        getch();
        texts[1] = 1;
    }

}

void printLoc()
{
    int n = roomList[currentRoom].nLocation;
    int w = roomList[currentRoom].wLocation;
    int l = roomList[currentRoom].lLocation;
    int s = roomList[currentRoom].sLocation;

    system("cls");

    printf("\n\n  x --  --  --  --  --  -- | --  --  --  --  --  --  x\n");
    printf("\n                      > %s <\n", roomList[currentRoom].description);
    printMap();

    printf("\n                           |");
    printf("\n         - Menu -          |");

    printf("       - Movement -");


    printf("\n");
    printf("\n        1. Status ");
                        if(hero.dexPoints > 0 || hero.statusPoints > 0)
                        {
                            setColor(9);
                            printf("[+Points]");
                            setColor(7);

                            printf("|");
                        }
                        else
                                printf("         |");

                        if(roomList[currentRoom].nLocation > 0)
                                printf("         [N] %s", roomList[n].description);



    printf("\n        2. Equip           |");
                        if(roomList[currentRoom].wLocation > 0)
                                printf("         [W] %s", roomList[w].description);


    printf("\n        3. Inventary       |");
                        if(roomList[currentRoom].lLocation > 0)
                                printf("         [L] %s", roomList[l].description);

    printf("\n        4. Save Game       |");
                        if(roomList[currentRoom].sLocation)
                                printf("         [S] %s", roomList[s].description);

    printf("\n        0. Close Game      |");
}
void choices()
{
    char choice;
    char sair;

    printf("\n\n>    ");
    scanf(" %c", &choice);


    if((choice  == 'n'  && roomList[currentRoom].nLocation > 0)|| (choice == 'N' && roomList[currentRoom].nLocation > 0)) //Se o jogador escolheu ir para norte
    {
        currentRoom = roomList[currentRoom].nLocation; //Agora a localização atual = a localização NORTE
    }
    else if((choice  == 'w'  && roomList[currentRoom].wLocation > 0)|| (choice == 'W' && roomList[currentRoom].wLocation > 0))
    {
        currentRoom = roomList[currentRoom].wLocation;
    }
    else if((choice  == 'l'  && roomList[currentRoom].lLocation > 0)|| (choice == 'L' && roomList[currentRoom].lLocation > 0))
    {
        currentRoom = roomList[currentRoom].lLocation;
    }
    else if((choice  == 's'  && roomList[currentRoom].sLocation > 0)|| (choice == 'S' && roomList[currentRoom].sLocation > 0))
    {
        currentRoom = roomList[currentRoom].sLocation;
    }
    else if(choice == '1')
    {
        printStatus();
    }
    else if(choice == '2')
    {
        showEquips();
    }
    else if(choice == '3')
    {
        printIventary();
    }
    else if(choice == '4')
    {
        saveGame();
    }
    else if(choice == '0')
    {
        printf(" Do you really want to close the game?");
        printf("[Y]es /[N]o");
        scanf(" %c", &sair);

        if(sair == 'y' || sair == 'Y')
            exit(EXIT_SUCCESS);
    }
    else
    {
        printf(" Type a valid option");
        getchar();
        currentEnemy = 0;
        printLoc();
    }


}

void printStatus()
{
    char choice;
    system("cls");

    printf("\n\n  x --  --  --  --  --  -- | --  --  --  --  --  --  x\n");
    printf("\n                     # Kobe Status #");

    printf("\n\n                       lvl: %d\n", hero.lvl);

    printf("                       XP: %d/%d\n", hero.exp, heroNextLvl);
    printf("                       Equipment: %s\n", itemList[hero.currentWeapon].name);
    printf("                       Secundary: %s\n", itemList[hero.currentShield].name);

            deadMages();

    printf("\n x --  --  --  --  --  -- | --  --  --  --  --  --  x\n");

    printf("\n                           \n");

    printf("    HP: ");
    setColor(10);
    printf("%d/%d              ", hero.CurrentHP, hero.hp);
    setColor(7);

                    printf("       > Dex Points <\n");

    printf("    MP: ");
    setColor(9);
    printf("%d/%d\n\n", hero.CurrentMP, hero.mp);
    setColor(7);

    printf("    ATK: %d + [%d]               ", hero.atk, itemList[hero.currentWeapon].atk);
                    printf("   Sword: %d\n", hero.swordDex);

    printf("    DEF: %d + [%d]               ", hero.def, itemList[hero.currentWeapon].def + itemList[hero.currentShield].def);
                    printf("   Shield: %d\n", hero.shieldDex);

    printf("    LUCK: %d + [%d]             ", hero.luc, itemList[hero.currentWeapon].luc);
                    printf("    Knife: %d\n", hero.knifeDex);

    printf("    INT: %d + [%d]              ", hero.inT, itemList[hero.currentWeapon].inT);
                    printf("    Two Hand Sword: %d\n", hero.twoHandSwordDex);

    if(hero.statusPoints > 0)
    {
        setColor(14);
        printf("\n  [1] Use skills points");
    }


    if(hero.dexPoints > 0)
    {
        setColor(14);
        printf("\n  [2] Use dex points");
    }
        setColor(7);

    printf("\n\n  x --  --  --  --  --  -- | --  --  --  --  --  --  x\n");

    printf("\n          - [0] Exit");
    printf("\n\n>    ");
    scanf(" %c", &choice);

    if(choice == '1' && hero.statusPoints > 0)
        useStatusPoints();

    if(choice == '2' && hero.dexPoints > 0)
        useDexPoints();

    currentEnemy = 0;
}

void deadMages()
{
    if(earthMageDead == true)
    {
        setColor(6);
        printf("   Brown Mage   ");
        setColor(7);
    }
    if(thunderMageDead == true)
    {
        setColor(15);
        printf("    White Mage    ");
        setColor(7);
    }
    if(waterMageDead == true)
    {
        setColor(9);
        printf("    Blue Mage    ");
        setColor(7);
    }
    if(fireMageDead == true)
    {
        setColor(12);
        printf("    Red Mage    ");
        setColor(7);
    }

}

void useStatusPoints()
{
    char c;

    system("cls");

    printf("\n\n  x --  --  --  --  --  -- | --  --  --  --  --  --  x\n");
    printf("                  Using Points\n\n");
    printf("                   Avaible Points: %d", hero.statusPoints);

    printf("\n      [A]tk + 1");
    printf("\n      [D]ef + 1");
    printf("\n      [L]uck + 1");
    printf("\n      [I]nt + 1");

    printf("\n\n\n        [0] Exit");
    printf("\n\n>     ");

    scanf(" %c", &c);

    if(c != '0')
        spendSkillPoint(c);

    getch();
}

void spendSkillPoint(char c)
{
    if(c == 'a' || c == 'A')
    {
        hero.atk++;
        hero.statusPoints--;
        printf(" You increase your damage!");
    }
    else if(c == 'D' || c == 'd')
    {
        hero.def++;
        hero.statusPoints--;
        printf(" You increase your defense!");
    }
    else if(c == 'L' || c == 'l')
    {
        hero.luc++;
        hero.statusPoints--;
        printf(" You increase your critical hit!");
    }
    else if(c == 'i' || c == 'I')
    {
        hero.inT++;
        hero.statusPoints--;
        printf(" You increase your magical damage!");
    }
    else
    {
        printf(" Type a valid option!");
    }
}
void useDexPoints()
{
    int c;

    system("cls");

    printf("\n\n  x --  --  --  --  --  -- | --  --  --  --  --  --  x\n");
    printf("                  Using Points\n\n");
    printf("                  Avaible dex Points: %d", hero.dexPoints);

    printf("\n Destreza com: \n");
    printf("\n [1] Sword + 1");
    printf("\n [2] Two Hand Sword + 1");
    printf("\n [3] Knife + 1");
    printf("\n [4] Shield + 1");

    printf("\n\n\n        [0] Exit");
    printf("\n\n>     ");

    scanf(" %d", &c);

    if(c != 0)
        spendDexPoint(c);

    getch();
}
void spendDexPoint(int c)
{
    if(c == 1)
    {
        hero.swordDex++;
        hero.dexPoints--;
        printf(" You increase your sword dexterity!");
    }
    else if(c == 2)
    {
        hero.twoHandSwordDex++;
        hero.dexPoints--;
        printf(" You increase your two hand sword dexterity!");
    }
    else if(c == 3)
    {
        hero.knifeDex++;
        hero.dexPoints--;
        printf(" You increase your knife dexterity!");
    }
    else if(c == 4)
    {
        hero.shieldDex++;
        hero.dexPoints--;
        printf(" You increase your shield dexterity!");
    }
    else
    {
        printf(" Type an valid option.");
    }
}

void showEquips()
{
    int choice;

    system("cls");
    printf("\n\n  x --  --  --  --  --  -- | --  --  --  --  --  --  x\n\n");
    printf("                       Equipments\n\n");

    printf("\n    Equipado: %s", itemList[hero.currentWeapon].name);
    printf("\n             > %s", itemList[hero.currentShield].name);

    printf("\n\n  x --  --  --  --  --  -- | --  --  --  --  --  --  x\n\n");

    printf("\n                       Avaible: \n\n");

    itemsTaken();

    printf("                          [0] Exit\n");
    printf(">     ");
    scanf(" %d", &choice);

    if(choice != 0)
    {
        char c;
        printItensStatus(choice);

        printf("\n       Do you want to equip this item?\n");
        printf("        [Y]es / [N]o\n\n");
        printf(">    ");
        scanf(" %c", &c);


        if(c == 'y' || c == 'N')
        {
           changingEquips(choice);
        }


    }
}
void changingEquips(char choice)
{

    if(choice == 2 || choice == 4)
    {
        printf("        > You can't use a shield with this <\n\n");
        getch();

        hero.currentWeapon = choice;
        hero.currentShield = 0;
    }
    else if(choice != 5)
    {
        printf("        > You equip this < \n\n");

        getch();
        hero.currentWeapon = choice;
    }
    else if(choice == 5)
    {
        printf(" Only one hand sword can be used with the shield\n\n");

        printf(" You equip the shield.\n\n");
        hero.currentShield = 5;
        getch();

    }
    currentEnemy = 0;
}

void itemsTaken()
{
    if(your.sword > 0)
        printf("    [1] Sword \n");

    if(your.twoHandSword > 0)
        printf("    [2] Two hand sword  \n");

    if(your.knife > 0)
        printf("    [3] Knife \n");

    if(your.rod > 0)
        printf("    [4] Rod \n");

    if(your.shield > 0)
        printf("    [5] Shield \n");


}

void printItensStatus(int item)
{
    int dex;

    printf("\n\n  x --  --  --  --  --  -- | --  --  --  --  --  --  x\n\n");

   printf("                       > %s Status <\n\n", itemList[item].name);

   printf("                            Atk: %d\n", itemList[item].atk);
   printf("                            Def: %d\n", itemList[item].def);
   printf("                            Int: %d\n", itemList[item].inT);
   printf("                            Luck: %d\n", itemList[item].luc);

    dex = dexForWeapon(item);

    printf("             Your dexterity with this kind of item: %d", dex);

   printf("\n\n  x --  --  --  --  --  -- | --  --  --  --  --  --  x\n\n");

}

void showSkill()
{
    int skillChoice;

    printf("\n                      - Skills -\n\n");

    switch(hero.lvl)
    {
    case 7:
        printf(" [2] Enemy status (-5 de mp)\n");

            printf("        Get all enemy status\n\n");
    case 6:
        printf(" [1] Heal   (-3 mp)\n");

            printf("       Heal 7 hp points\n\n");
    }

    printf("\n                      [0] Exit");

    printf("\n>    ");
    scanf("%d", &skillChoice);

    useSkills(skillChoice);

    getch();
}

void useSkills(int skillChoice)
{
    if(skillChoice == 2 && hero.CurrentMP >= 5)
    {
        hero.CurrentMP = hero.CurrentMP - 5;
        printEnemyStatus();

        getch();
    }
    else if(skillChoice == 1 &&  hero.CurrentMP > 3)
    {
        hero.CurrentMP = hero.CurrentMP - 3;
        hero.CurrentHP = hero.CurrentHP + 3;

        if(hero.CurrentHP > hero.hp)
            hero.CurrentHP = hero.hp;

        printf("                  # You heal 7 HP #\n\n");

        getch();
    }
    else if(skillChoice != 0)
    {
        printf("           You don't have MP");
        getch();
    }
}

void printEnemyStatus()
{
    enStatus = true;
    printf("\n\n                   - %s Status -\n\n ", enemyList[currentEnemy].name);
            printf("                        level: %d\n", enemyList[currentEnemy].lvl);
            printf("                         hp: %d\n", enemyList[currentEnemy].hp);
            printf("                         atk: %d\n", enemyList[currentEnemy].atk);
            printf("                         def: %d\n", enemyList[currentEnemy].def);

            if(enemyList[currentEnemy].weakness > 0)
            {
                int weakness = enemyList[currentEnemy].weakness;


                if(weakness == 1)
                    printf("                         weakness: Fire");
                else if(weakness == 2)
                    printf("                         weakness: Water");
                else if(weakness == 3)
                    printf("                         weakness: Earth");
                else if(weakness == 4)
                    printf("                         weakness: Wind");

            }
            printf("\n\n                           - # -");
            printf("\n>    ");
}

void printIventary()
{
    int item;

    printf("\n\n  x --  --  --  --  --  -- | --  --  --  --  --  --  x\n");
    printf("\n                      - Inventary -\n\n");

    if(your.hpPotion > 0)
        printf("   [1] HP Potion x%d \n\n", your.hpPotion);

    if(your.mpPotion > 0)
        printf("   [2] MP Potion x%d \n\n", your.mpPotion);

    printf("\n                          [0] Exit");
    printf("\n\n>    ");
    scanf("%d", &item);

    if(item != 0)
        useItem(item);

}

void useItem(int item)
{

    if(item == 1 && your.hpPotion > 0)
    {
        your.hpPotion--;
        hero.CurrentHP = hero.CurrentHP + 5;

        printf("                    # You heal 5 de HP #\n\n");

        if(hero.CurrentHP > hero.hp)
            hero.CurrentHP = hero.hp;

        getch();
    }
    else if(item == 2 && your.mpPotion > 0)
    {
        your.mpPotion--;
        hero.CurrentMP = hero.CurrentMP + 5;

        printf("                  # You restore 5 de MP #\n\n");

        if(hero.CurrentMP > hero.mp)
            hero.CurrentMP = hero.mp;

        getch();
    }
    else
    {
        printf("             You don't have potions\n\n");
        getch();
    }

}

void testMage()
{
    if(currentRoom == locfireMage && fireMageDead == false)
    {
        currentEnemy = firemage;
        battleRunning = true;
        battle(12);
    }
    if(currentRoom == locwaterMage && waterMageDead == false)
    {
        currentEnemy = watermage;
        battleRunning = true;
        battle(15);
    }
    if(currentRoom == locearthMage && earthMageDead == false)
    {
        currentEnemy = earthmage;
        battleRunning = true;
        battle(6);
    }
    if(currentRoom == locthunderMage && thunderMageDead == false)
    {
        currentEnemy = thundermage;
        battleRunning = true;
        battle(9);
    }
}

void testFinalGame()
{
    if((fireMageDead == true && earthMageDead == true) && (thunderMageDead == true && waterMageDead == true))
    {
         system("cls");



         printf("\n\n  x --  --  --  --  --  -- | --  --  --  --  --  --  x\n\n");
         printf(" Final game TEXT\n");
         printf("\n                      You finish the game");
         printf("\n\n                   Tanks for playing! :D\n\n\n\n\n");
         printf("\n\n  x --  --  --  --  --  -- | --  --  --  --  --  --  x\n\n");
         getch();
         gameRunning = false;

         exit(EXIT_SUCCESS);

    }
}

void testEnemy()
{
    int rdm;

    srand((unsigned) time (NULL));
    rdm = (1 + (rand() % 2));

    if(roomList[currentRoom].enemyTypes > 0 && rdm == 2)
    {
        enemyAppear(roomList[currentRoom].enemyTypes);
    }
}

void enemyAppear(int enemyType)
{
    int r;

    srand((unsigned) time (NULL));
    r = (rand() % 3);

    switch(enemyType)
    {
    case 1:
        if(r == 0)
        {
            currentEnemy = Soldier;
        }
        else if(r == 1)
        {
            currentEnemy = Jailer;
        }
        else if(r == 2)
        {
            currentEnemy = Khez;
        }
        break;
    case 2:
        if(r == 0)
        {
            currentEnemy = Kawrosk;
        }
        else if(r == 1)
        {
            currentEnemy = Trars;
        }
        else if(r == 2)
        {
            currentEnemy = Jacub;
        }
        break;
    case 3:
        if(r == 0)
        {
            currentEnemy = WingedOb;
        }
        else if(r == 1)
        {
            currentEnemy = Blefyhl;
        }
        else if(r == 2)
        {
            currentEnemy = Wulo;
        }
        break;
    case 4:
        if(r == 0)
        {
            currentEnemy = Gnoss;
        }
        else if(r == 1)
        {
            currentEnemy = CursedOb;
        }
        else if(r == 2)
        {
            currentEnemy = Atehm;
        }
        break;
    case 5:
        if(r == 0)
        {
            currentEnemy = Xauhnulst;
        }
        else if(r == 1)
        {
            currentEnemy = Fear;
        }
        else if(r == 2)
        {
            currentEnemy = Gorlab;
        }
    }

    battleRunning = true;
    battle(7);
}

void whoAppear()
{
        printf("\n\n  x --  --  --  --  --  -- | --  --  --  --  --  --  x\n");
        printf("\n\n               > Battle in %s <\n\n", roomList[currentRoom].description);
        printf("\n                  # A %s has appear #\n\n", enemyList[currentEnemy].name);

        enemyCurrentHP = enemyList[currentEnemy].hp;

        getch();
        system("cls");
}

void battle(int color)
{
        whoAppear();

        while(battleRunning == true)
        {

            tempDef = hero.def + itemList[hero.currentShield].def;
            tempAtk = hero.atk + itemList[hero.currentWeapon].atk;

            setColor(color);

            printf("\n\n  x --  --  --  --  --  -- | --  --  --  --  --  --  x\n");

            printf("\n                      - Batalha -\n");
            printf("  Turno | %d |\n\n", battleTurn);

            setColor(12);
            printf("                              %s\n", enemyList[currentEnemy].name);
            setColor(color);
            printf("                              HP: ");
            setColor(12);
            printf("%d/%d", enemyCurrentHP, enemyList[currentEnemy].hp);
            setColor(color);

            printf("\n                              ");
            printHealthBar(enemyCurrentHP, enemyList[currentEnemy].hp, 1);

            printf("\n\n\n\n\n  ");

            printHealthBar(hero.CurrentHP, hero.hp, 0);

            printf("\n   HP: ");
            setColor(10);
            printf("%d/%d\n", hero.CurrentHP, hero.hp);
            setColor(color);
            printf("      MP: ");
            setColor(9);
            printf("%d/%d\n", hero.CurrentMP, hero.mp);
            setColor(color);

            printf("\n\n  x --  --  --  --  --  -- | --  --  --  --  --  --  x\n");

            printBattleOptions();
            enemyAction();

            hero.CurrentHP = hero.CurrentHP - enemyDamage;

            testEnemysLife(enemyCurrentHP);
            testHerosLife(hero.CurrentHP);

            system("cls");
            battleTurn++;

        }

}

void printBattleOptions()
{
    char d;
    if(battleRunning == true)
    {
        printf("\n                           |");

        printf("\n     [1] Attack            |");  heroActionTest();
        printf("\n     [2] Defend            |");
        printf("\n     [3] Magic             |");  enemyActionTest();
        printf("\n     [4] Itens             |");

        if(hero.skills > 0)
            printf("\n     [5] Skills            |") ;

        printf("\n\n>    ");

        scanf(" %c", &d);
        battleChoice(d);

    }
}

void battleChoice(char d)
{
    int dex;

    if(d == '1')
    {
        damage = true;

        dex = findDex(hero.currentWeapon);
        yourDamage = atk(tempAtk, enemyList[currentEnemy].def, hero.luc, dex);

        if(yourDamage < 0)
        {
            yourDamage = 0;
        }

        enemyCurrentHP = enemyCurrentHP - yourDamage;

    }
    else if(d == '2')
    {
        tempDef = blockCount(hero.def, hero.shieldDex);
        block = true;
    }
    else if(d == '3')
    {
        magicAtkOptions();
    }
    else if(d == '4')
    {
        printIventary();
    }
    else if(d == '5' && hero.skills > 0)
    {
        showSkill();
    }
    else
    {
        printf(" Type a valid command.");
        getch();
    }
}

void enemyAction()
{
    int r;

    if(enemyList[currentEnemy].enemyNumber < 16)
    {
        enemyDamage = enemyAtk(enemyList[currentEnemy].atk, tempDef);
    }
    else
    {

        mageDamage = true;
        srand((unsigned) time (NULL));
        r = 1 + (rand() % 5);

        switch(enemyList[currentEnemy].enemyNumber)
        {
        case 16:
            brownAtk(r);
            break;
        case 17:
            whiteAtk(r);
            break;
        case 18:
            blueAtk(r);
            break;
        case 19:
            redAtk(r);
        }
    }
}

void brownAtk(int random)
{
    if(random < 3)
    {
        enemyDamage = enemyList[currentEnemy].atk - tempDef;
        enemyRandomAtk = 1;
    }
    else if(random == 4)
    {
        enemyList[currentEnemy].atk = enemyList[currentEnemy].atk + 2;
        enemyRandomAtk = 2;
    }
    else if(random == 5)
    {
        enemyDamage = tempAtk;
        enemyRandomAtk = 3;
    }

}

void whiteAtk(int random)
{
    if(random == 4 && hero.currentShield > 0)
    {
        hero.currentShield = 0;
        enemyRandomAtk = 4;
    }
    else if(random == 5 && hero.currentWeapon > 0)
    {
        hero.currentWeapon = 0;
        enemyRandomAtk = 5;
    }
     else
    {
        enemyDamage = enemyList[currentEnemy].atk - tempDef;
        enemyRandomAtk = 1;
    }
}

void blueAtk(int random)
{
    if(random < 3)
    {
        enemyDamage = enemyList[currentEnemy].atk - tempDef;
        enemyRandomAtk = 1;
    }
    else if(random == 4)
    {
        enemyCurrentHP = enemyCurrentHP + 20;
        if(enemyCurrentHP > enemyList[currentEnemy].hp)
            enemyCurrentHP = enemyList[currentEnemy].hp;

        enemyRandomAtk = 6;
    }
    else if(random == 5)
    {
        enemyCurrentHP = enemyCurrentHP + 10;
        hero.CurrentHP = hero.CurrentHP - 10;

        enemyRandomAtk = 7;
    }
}
void redAtk(int random)
{
    if(random == 1)
    {
        enemyDamage = enemyList[currentEnemy].atk - tempDef;
        enemyRandomAtk = 1;
    }
    else if(random == 2)
    {
        tempDef = tempDef - 2;
        enemyRandomAtk = 8;
    }
    else if(random > 2 && random < 6)
    {
        enemyList[currentEnemy].atk = enemyList[currentEnemy].atk * 2;
        enemyRandomAtk = 9;
    }
}

int enemyAtk(int atk, int heroDef)
{
    int trueDamage;

        enDamage = true;
        trueDamage = atk - heroDef;

        if(trueDamage < 0)
        {
            trueDamage = 0;
        }

    return trueDamage;
}

void heroActionTest()
{
    if(enStatus == true)
    {
        printf(" You got enemy status");
        enStatus = false;
    }
    if(damage == true)
    {
        printf(" You deal %d damage", yourDamage);

        if(doubleDamage == true)
        {
            printf(" - DoubleDamage!");
            doubleDamage = false;
        }
        damage = false;
    }
    if(block  == true)
    {
        printf(" You block %d damage", tempDef);
        block = false;
    }

    if(withoutMP == true)
    {
        printf(" You don't have enough MP");
        withoutMP = false;
    }

}

void enemyActionTest()
{
    if(enDamage == true)
    {
        printf(" The enemy deal %d damage", enemyDamage);
        enDamage = false;
    }
    else
    {
        mageDamage = false;

        if(enemyRandomAtk == 1)
        {
            printf(" The Mage deal %d magic damage", enemyDamage);
        }
        else if(enemyRandomAtk == 2)
        {
            printf(" The Mage increase the damage in 2");
        }
        else if(enemyRandomAtk == 3)
        {
            printf(" The Mage use your damage agaist yourself %d damage", enemyDamage);
        }
        else if(enemyRandomAtk == 4)
        {
            printf(" The Mage stoled your shield");
        }
        else if(enemyRandomAtk == 5)
        {
            printf(" The Mage stoled your shield");
        }
        else if(enemyRandomAtk == 6)
        {
            printf(" The Mage restore 5 HP");
        }
        else if(enemyRandomAtk == 7)
        {
            printf(" The enemy drain your life");
        }
        else if(enemyRandomAtk == 8)
        {
            printf(" The Mage decrease your defense -2 def");
        }
        else if(enemyRandomAtk == 9)
        {
            printf(" The Mage duplicate the damage");
        }
    }
}

int findDex(int dex)
{
    int thisDex;

    switch(dex)
    {
    case 1:
        thisDex = hero.swordDex;
        break;
    case 2:
        thisDex = hero.twoHandSwordDex;
        break;
    case 3:
        thisDex = hero.knifeDex;
        break;
    default:
        thisDex = 0;
    }
    return thisDex;
}

int blockCount(int def, int dex)
{
    int thisDef, tempDex;

    tempDex = 1 + (dex / 10);
    thisDef = tempDex + def;

    return thisDef;
}

void magicAtkOptions()
{
    int gemChoice;
    damage = true;
    printf("\n             - Chose the element? -\n (-5 MP)\n\n");
    printf("   [1] Go back\n");

    if(your.fireGem == 1)
    {
        printf("\n    [2] Fire ");
    }
    if(your.waterGem == 1)
    {
        printf("\n    [3] Water ");
    }
    if(your.earthGem == 1)
    {
        printf("\n    [4] Earth ");
    }
    if(your.thunderGem == 1)
    {
        printf("\n    [5] Thunder ");
    }

    printf("\n\n>    ");
    scanf(" %d", &gemChoice);

    if(hero.CurrentMP >= 5 && gemChoice != 1)
    {
        magicAtkChoice(gemChoice);
    }
    else if(gemChoice != 1)
    {
        printf("         > You don't have enough mana. <");

        withoutMP = true;
        damage = false;
        block = false;

        getch();
    }

}

void magicAtkChoice(int choice)
{

    if(choice == 2)
    {
        makeAtk(1);
    }
    else if(choice == 3)
    {
        makeAtk(2);
    }
    else if(choice == 4)
    {
        makeAtk(3);
    }
    else if(choice == 5)
    {
        makeAtk(4);
    }
    else
    {
        printf(" Type a valid command.");
        damage = false;
    }
}

void makeAtk(int element)
{
    int trueDamage;

    trueDamage = magicAtk(element, hero.inT + itemList[hero.currentWeapon].inT, enemyList[currentEnemy].def,
                          enemyList[currentEnemy].weakness);

    enemyCurrentHP = enemyCurrentHP - trueDamage;
    yourDamage = trueDamage;

}

int magicAtk(int element, int heroInt, int enemyDef, int enemyWeakness)
{
    int trueDamage;

    damage = true;

    hero.CurrentMP = hero.CurrentMP - 5;

    trueDamage = heroInt - enemyDef;
    if(trueDamage < 0)
    {
        trueDamage  = 0;
    }

    if(element == enemyWeakness)
    {
        trueDamage = trueDamage * 2;
        doubleDamage = true;
    }
    return trueDamage;
}

void testHerosLife(int herosLife)
{
    if(herosLife <= 0)
    {
        system("cls");

        printf("\n\n          - # - # - # - # - # - # - # - # - # - # - # - # -\n\n\n");
        printf("\n                       - You are Dead -\n\n\n");
        printf("\n                        # GAME OVER #\n\n\n\n");
        printf("          - # - # - # - # - # - # - # - # - # - # - # - # -\n\n\n");

        battleRunning = false;
        getch();

        exit(EXIT_SUCCESS);
    }
}

void testEnemysLife(int enemyLife)
{
    if(enemyLife <= 0)
    {

        testMageLife();
        system("cls");

        enemyCurrentHP = 0;

        printf("\n                - You have killed the enemy - \n");

        if(heroMaxlvl != true)
        {
            printf("\n                   You won %d EXP!\n", experience(enemyList[currentEnemy].lvl));
            hero.exp = hero.exp + experience(enemyList[currentEnemy].lvl);

            dropItem();

            printf("\n                        Lvl: %d\n", hero.lvl);
            printf("\n                        XP: %d/%d", hero.exp, heroNextLvl);
            printf("\n\n>    ");

            enDamage = false;
            damage = false;
            enemyDamage = 0;
            yourDamage = 0;
            lvlTemp = hero.lvl;
            battleRunning = false;

            getch();
            battleTurn = 0;
            system("cls");

            heroLvlUp();
            testLevelUp();

            setColor(7);
        }
    }
}

void testMageLife()
{
     if(currentEnemy == earthmage)
     {
         earthMageDead = true;
         printf("\n\n\n            > You have killed the Brown Mage <\n\n");
         printf("      You receive a gem, you now can use the Earth Skills");
         your.earthGem = 1;
         getch();
     }
     if(currentEnemy == thundermage)
     {
         thunderMageDead = true;
         printf("\n\n\n            > You have killed the White Mage <\n\n");
         printf("       You receive a gem, you now can use the Thunder Skills");
         your.thunderGem = 1;
         getch();
     }
     if(currentEnemy == firemage)
     {
         fireMageDead = true;
         printf("\n\n\n            > You have killed the Red Mage <\n\n");
         printf("         You receive a gem, you now can use the Fire Skills ");
         your.fireGem = 1;
         getch();
     }
     if(currentEnemy == watermage)
     {
          waterMageDead = true;
          printf("\n\n\n            > You have killed the Blue Mage <\n\n");
          printf("          You receive a gem, you now can use the Water Skills ");
          your.waterGem = 1;
         getch();
     }
}

void printHealthBar(int currentHP, int maxHP, int who)
{
    int temp, result;

    temp = 100 * currentHP;
    result = temp / maxHP;


    if(who == 1 || result <= 20)
        setColor(12);
    else
        setColor(10);

    if(result <= 1)
    {
        printf(" ");
    }
    else if(result <= 10)
    {
        printf("\xdb");
    }
    else if(result <= 20)
    {
        printf("\xdb\xdb");
    }
    else if(result <= 30)
    {
        printf("\xdb\xdb\xdb");
    }
    else if(result <= 40)
    {
        printf("\xdb\xdb\xdb\xdb");
    }
    else if(result <= 50)
    {
        printf("\xdb\xdb\xdb\xdb\xdb");
    }
    else if(result <= 60)
    {
        printf("\xdb\xdb\xdb\xdb\xdb\xdb");
    }
    else if(result <= 70)
    {
        printf("\xdb\xdb\xdb\xdb\xdb\xdb\xdb");
    }
    else if(result <= 80)
    {
        printf("\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb");
    }
    else if(result <= 99)
    {
        printf("\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb");
    }
    else if(result == 100)
    {
        printf("\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb");
    }
    setColor(7);
}

void dropItem()
{
    int rdm;

    srand((unsigned) time (NULL));
    rdm = (1 + (rand() % 2));

    if(enemyList[currentEnemy].enemyNumber == 2 && your.knife != 1 && rdm == 2)
    {
        printf("\n            - # You find a Knife # - \n");
        your.knife = 1;
    }
    else if(enemyList[currentEnemy].enemyNumber == 4 && your.shield != 1 && rdm == 2)
    {
        printf("\n            - # You find a Shield # - \n");
        your.shield = 1;
    }
    else if((enemyList[currentEnemy].enemyNumber == 6 || enemyList[currentEnemy].enemyNumber == 9) && your.rod != 1 && rdm == 2)
    {
        printf("\n            - # You find a Rod # - \n");
        your.rod = 1;
    }
    else if((enemyList[currentEnemy].enemyNumber > 12 && enemyList[currentEnemy].enemyNumber < 16) && your.twoHandSword != 1 && rdm == 2)
    {
        printf("\n            - # You find a Two Hand Sword # - \n");
        your.twoHandSword = 1;
    }
    if(rdm == 2)
    {
        srand((unsigned) time (NULL));
        rdm = (1 + (rand() % 3));
        if(rdm == 2)
        {
            printf("\n            - # You won a MP potion # - \n");
            your.mpPotion++;
        }
        else
        {
            printf("\n            '- # You won a HP potion ! # -\n");
            your.hpPotion++;
        }
    }
}


int atk(int atk, int def, int luck, int dex)
{
    float tempDamage, damage, tempCritical;
    int trueDamage;

    tempDamage = atk * (1 + (dex / 10));
    tempCritical = findCriticalHit(luck);

    damage = tempDamage * tempCritical;
    trueDamage = Round(damage);

    return trueDamage;
}

int findCriticalHit(int luck)
{
    int r, criticalHit;
    float tempCriticalHit;


        srand((unsigned) time (NULL));
        r = (rand() % 10);

        luck = luck / 2;
        tempCriticalHit = (luck + r) / 5;

        criticalHit = Round(tempCriticalHit);

        if(criticalHit <= 0)
        {
            criticalHit = 1;
        }
        else if(criticalHit >= 2)
        {
            criticalHit = 2;
            doubleDamage = true;
        }


        return criticalHit;
}

int Round(float myfloat)
{
  double integral;
  float fraction = (float)modf(myfloat, &integral);

  if (fraction >= 0.5)
    integral += 1;
  if (fraction <= -0.5)
    integral -= 1;

  return (int)integral;
}

int dexForWeapon(int currentWeapon)
{
    int dex;

    switch(currentWeapon)
    {
    case 1:
        dex = hero.swordDex;
        break;
    case 2:
        dex = hero.twoHandSwordDex;
        break;
    case 3:
        dex = hero.knifeDex;
        break;
    case 4:
        dex = hero.rodDex;
        break;
    }
    return dex;
}

int experience(int enemyLvl)
{
    int experienceR = enemyLvl * 5;
    return experienceR;
}

void heroLvlUp()
{
    if(hero.exp < 30)
    {
        heroNextLvl = 30;
        hero.lvl = 5;
    }
    else if((hero.exp > 29) && (hero.exp < 60))
    {
        heroNextLvl = 60;
        hero.lvl = 6;
    }
    else if((hero.exp > 59) && (hero.exp < 120))
    {
        heroNextLvl = 120;
        hero.lvl = 7;
    }
    else if((hero.exp > 119) && (hero.exp < 240))
    {
        heroNextLvl = 240;
        hero.lvl = 8;
    }
    else if((hero.exp > 239) && (hero.exp < 480))
    {
        heroNextLvl = 480;
        hero.lvl = 9;
    }
    else if((hero.exp > 479) && (hero.exp < 960))
    {
        heroNextLvl = 960;
        hero.lvl = 10;
        heroStatusLvlUp();
    }
    else if((hero.exp > 959) && (hero.exp < 1920))
    {
        heroNextLvl = 1920;
       hero.lvl = 11;
    }
    else if((hero.exp > 1919) && (hero.exp < 3840))
    {
        heroNextLvl = 3840;
        hero.lvl = 12;
    }
    else if((hero.exp > 3839) && (hero.exp < 7680))
    {
        heroNextLvl = 7680;
        hero.lvl = 13;
    }
    else if((hero.exp > 7679) && (hero.exp < 15260))
    {
        heroNextLvl = 15260;
        hero.lvl = 14;
    }
    else if(hero.exp >= 15259)
    {
        heroNextLvl = 0;
        hero.lvl = 15;
        heroMaxlvl = true;
    }
}

void heroStatusLvlUp()
{
    hero.hp = hero.hp + 2;
    hero.mp = hero.mp + 2;


    hero.CurrentHP = hero.hp;
    hero.CurrentMP = hero.mp;

    hero.dexPoints++;
    hero.statusPoints++;
}

void resetMap()
{
    int i, n;

    for(i = 0; i <= 4; i++)
    {
        for(n = 0; n <= 6; n++)
        {
            map[i][n] = 1;
        }
    }
    map[2][3] = 3;
}

void atualizeMap()
{
    resetMap();
    if(roomList[currentRoom].nLocation > 0)
    {
        map[0][3] = 0;
        map[1][3] = 0;
    }
    if(roomList[currentRoom].wLocation > 0)
    {
        map[2][0] = 0;
        map[2][1] = 0;
        map[2][2] = 0;
    }
    if(roomList[currentRoom].lLocation > 0)
    {
        map[2][4] = 0;
        map[2][5] = 0;
        map[2][6] = 0;
    }
    if(roomList[currentRoom].sLocation > 0)
    {
        map[3][3] = 0;
        map[4][3] = 0;
    }
}

void printMap()
{
    int i, n;

    printf("\n                         > map <\n");
    for(i = 0; i <= 4; i++)
    {
        for(n = 0; n <= 6; n++)
        {

            if(n == 0)
                printf("                          ");


            if(map[i][n] == 1)
                printf("\xDB");
            else if(map[i][n] == 0)
                printf(" ");
            else
                printf("*");
        }
        printf("\n");
    }
}

void setColor(int color)
{

     HANDLE hConsole;
     hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

     SetConsoleTextAttribute(hConsole, color);

     return;
}
int main()
{
    gameMenu();

  return 0;
}


