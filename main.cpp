#include<iostream>
#include<string>
#include<vector>
#include<cstdlib>
#include<ctime>
#include<limits>

using namespace std;

// Creates a pause
void pause()
{
    cin.ignore();
    cin.get();
}

// Basically the main screen
void menu()
{
    cout << "[1] Check weapon stats." << endl;
    cout << "[2] Check player stats." << endl;
    cout << "[3] Move." << endl;
    cout << "[4] Exit game." << endl;
}

// Structures for weapons, enemies and player
struct weapon
{
    string name;
    int minDMG;
    int maxDMG;
};

struct enemy
{
    string name;
    int HP;
    int DEF;
    int minDMG;
    int maxDMG;
    int level;
    int special;
};

struct player
{
    string name="";
    int HP;
    int DEF;
    int level = 0;
    int expp = 0;
};

// List of weapons
vector<weapon> weapons =
    {
        {"Rusty Sword", 5, 10},
        {"Iron Dagger", 8, 12},
        {"Wooden Staff", 6, 14},
        {"Bronze Axe", 10, 18},
        {"Steel Sword", 12, 20},
        {"Silver Bow", 15, 25},
        {"Magic Wand", 14, 28},
        {"Golden Mace", 18, 30},
        {"Obsidian Blade", 20, 35},
        {"Emerald Staff", 22, 38},
        {"Adamantium Dagger", 25, 40},
        {"Crystal Sword", 28, 45},
        {"Dragon Slayer", 30, 50},
        {"Enchanted Bow", 32, 52},
        {"Titanium Axe", 35, 55},
        {"Stormcaller Staff", 38, 60},
        {"Phoenix Feather", 40, 65},
        {"Soul Reaver", 42, 68},
        {"Darksteel Sword", 45, 70},
        {"Void Blade", 48, 75},
        {"Celestial Hammer", 50, 80}
    };

// List of enemies
vector<enemy> enemies =
    {
        {"Slime", 20, 1, 2, 4, 1},
        {"Spider", 25, 1, 2, 5, 2},
        {"Skeleton", 30, 2, 3, 6, 3},
        {"Wolf", 40, 3, 4, 8, 4},
        {"Spirit King", 60, 20, 35, 70, 21},
        {"Zombie", 50, 4, 5, 10, 6},
        {"Ghost", 60, 3, 4, 12, 5},
        {"Bandit", 70, 5, 6, 15, 7},
        {"Golem", 80, 5, 8, 16, 8},
        {"Stone Colossus", 100, 25, 40, 80, 22},
        {"Specter", 90, 4, 7, 16, 9},
        {"Orc", 100, 7, 10, 20, 10},
        {"Witch", 120, 6, 9, 18, 11},
        {"Vampire", 150, 8, 12, 25, 12},
        {"Vampire Lord", 200, 30, 45, 90, 23},
        {"Troll", 180, 9, 14, 28, 13},
        {"Dragon", 200, 10, 15, 30, 14},
        {"Demon", 250, 12, 18, 35, 15},
        {"Behemoth", 280, 14, 20, 40, 16},
        {"Ancient Behemoth", 350, 35, 50, 100, 24},
        {"Kraken", 300, 15, 22, 45, 17},
        {"Phoenix", 320, 12, 25, 50, 18},
        {"Chimera", 350, 16, 28, 55, 19},
        {"Leviathan", 400, 18, 30, 60, 20},
        {"Ocean Leviathan", 600, 40, 55, 110, 25}
    };


// rollDamage function to, well, roll damage lmao
int rollDamage(int minDMG, int maxDMG)
{
    return rand() % (maxDMG - minDMG + 1) + minDMG; // Rolls dmg from numbers from min to max dmg possible
}



// Fight system
void fight(player& p, weapon& w, enemy& e) // I keep forgetting those variables in brackets lol
{
    cout << "[Roll]" << endl;
    pause();
    system("cls");

    int initP = rand() % 20 + 1; // Random number from 1 to 20 for initiative
    int initE = rand() % 20 + 1;

    cout << "You rolled " << initP << "." << endl;

    // Checks who starts first
    if (initP > initE)
    {
        cout << "You have the initiative!" << endl;
    }
    else if (initP < initE)
    {
        cout << "The enemy has the initiative!" << endl;
    }
    else
    {
        cout << "It's a tie! Roll again." << endl;
        fight(p, w, e);
    }

        pause();
        system("cls");

    int trueDMG; //DMG after calculations
    int playerDMG;
    int enemyDMG;

    // define playerTurn to determine who rolls dmg
    bool playerTurn = initP > initE;
while (p.HP >0 && e.HP > 0)
{
if (playerTurn)
{
    playerDMG = rollDamage(w.minDMG, w.maxDMG);
    enemyDMG = 0;
    trueDMG = playerDMG - e.DEF; // calculates true dmg

    // checks if it hits
    if (trueDMG > 0)
    {
        e.HP = e.HP - trueDMG; // lowers enemy HP
        if (e.HP >= 0)
        {
            cout << "You've dealt " << trueDMG << " DMG! " << e.name << " has now " << e.HP << " HP!";
        }
        else if (e.HP < 0)
        {
            cout << "You've dealt " << trueDMG << " DMG! " << e.name << " has now 0 HP!";
        }
        playerTurn = false; // changes the turn
    }
    else
    {
        cout << "You missed!";
        playerTurn = false; // changes the turn
    }
    pause();
}
else
{
    enemyDMG = rollDamage(e.minDMG, e.maxDMG);
    playerDMG = 0;
    trueDMG = enemyDMG - p.DEF;

    if (trueDMG > 0)
    {
        p.HP = p.HP - trueDMG;
        if (p.HP >= 0)
        {
            cout << "Enemy has dealt " << trueDMG << " DMG! " << p.name << " has now " << p.HP << " HP!";
        }
        else if (p.HP < 0)
        {
            cout << "Enemy has dealt " << trueDMG << " DMG! " << p.name << " has now 0 HP!";
        }
        playerTurn = true;
    }
    else
    {
        cout << "Enemy missed!";
        playerTurn = true;
    }
    pause();
}

    if (p.HP <= 0 && e.HP > 0)
    {
        pause();
        system("cls");
        cout << "Lmao, skill issue.";
        pause();
        exit(0);
    }
    else if (p.HP > 0 && e.HP <= 0)
    {
        int baseExp = p.level * 10;
        int bonusExp = rand() % 50 + 1;
        int exppGain = baseExp + bonusExp + (e.level - p.level);
        p.expp = p.expp + baseExp + bonusExp + (e.level - p.level);

        pause();
        system("cls");
        cout << "Good job! You won!" << endl;
        cout << "You've gained " << exppGain << " exp! You now have " << p.expp << " exp.";
        menu();
    }
}
}

// Menu options
void menuANS(vector<weapon>& weapons, string& Pweapon, vector<enemy>& enemies, player& p)
{
    int choice;
    cout << "> ";
    cin >> choice;
    system("cls");

    switch(choice)
    {
    case 1:
        {
        for (const auto& w : weapons)
        {
            if (w.name == Pweapon)
            {
                cout << w.name << ": " << w.minDMG << "-" << w.maxDMG << " DMG.";
                break;
            }
        }
        }
        pause();
        system("cls");
        break;
    case 2:
        {
            cout << p.name << ": " << p.HP << " HP & " << p.DEF << " DEF. Your level is "<<p.level<<". You have " << p.expp << "exp.";
        }
        pause();
        system("cls");
        break;
    case 3:
        {
           if (!weapons.empty() && !enemies.empty())
            {
                int randomIndex = rand() % enemies.size(); // chooses random enemy
                enemy& e = enemies[randomIndex];
                string enemyName = enemies[randomIndex].name;

                cout << "Going further, you've noticed " << enemyName << " on your way!" << endl;
                cout << "Roll initiative!" << endl;

                weapon selectedWeapon;
                for (const auto& weap : weapons)
                {
                    if (weap.name == Pweapon)
                    {
                        selectedWeapon = weap;
                        break;
                    }
                }

                fight(p, selectedWeapon, e);
            }
            else
            {
                exit(0);
            }
        }
        pause();
        system("cls");
        break;
    case 4:
        {
            exit(0);
        }
        system("cls");
    }
}

int main()
{
    srand(time(0));
    string answer, Pweapon, enemyName;

    player p;

    cout << "Hello adventurer! Are you ready to embark on an unforgettable journey?" << endl;
    cout << "> ";
    cin >> answer;

    if (answer == "yes")
    {
        cout << "Very well!" << endl;
        cout << "How may I call you, oh brave hero?" << endl;
        cout << "> ";
        cin >> p.name;
        cout << "Splendid!" << endl;
    }
    else if (answer == "no")
    {
        cout << "Well, that's your problem." << endl;
        cout << "How may I call you?" << endl;
        cout << "> ";
        cin >> p.name;
        cout << "Alright then." << endl;
    }
    else if (answer == "maybe")
    {
        cout << "Ha ha, smartass." << endl;
        p.name = "Smartass";
    }
    else
    {
        cout << "That's not an answer. Anyway..." << endl;
        cout << "How may I call you?" << endl;
        cout << "> ";
        cin >> p.name;
        cout << "Nice." << endl;
    }

    p.HP = 50;
    p.DEF = 2;

    cout << "Here's your weapon! Have fun." << endl;

    pause();
    system("cls");

    cout << "You've obtained a Rusty Sword!";
    Pweapon = "Rusty Sword";

    pause();
    system("cls");

    while(true)
    {
        menu();
        menuANS(weapons, Pweapon, enemies, p);
    }

    return 0;
}
