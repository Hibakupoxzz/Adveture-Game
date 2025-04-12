#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
using namespace std;

struct Player {
    string name;
    int hp, maxHp, attack, level, exp, gold, potions;
};

struct Enemy {
    string name;
    int hp, attack, rewardExp, rewardGold;
};

Enemy generateEnemy(int level) {
    string enemyNames[] = {"Goblin", "Orc", "Slime", "Skeleton", "Dark Knight"};
    int index = rand() % 5;

    Enemy e;
    e.name = enemyNames[index];
    e.hp = rand() % (10 + level * 5) + 10;
    e.attack = rand() % (3 + level * 2) + 2;
    e.rewardExp = rand() % (10 + level * 3) + 5;
    e.rewardGold = rand() % (10 + level * 2) + 5;
    return e;
}

void levelUp(Player &player) {
    while (player.exp >= 100) {
        player.exp -= 100;
        player.level++;
        player.maxHp += 10;
        player.attack += 2;
        player.hp = player.maxHp;
        cout << "\n⬆️ LEVEL UP! Kamu sekarang level " << player.level << "!\n";
    }
}

void battle(Player &player) {
    Enemy enemy = generateEnemy(player.level);
    cout << "\n⚔️  Musuh muncul: " << enemy.name << " (HP: " << enemy.hp << ", ATK: " << enemy.attack << ")\n";

    while (enemy.hp > 0 && player.hp > 0) {
        cout << "\n[1] Serang  [2] Gunakan Potion (" << player.potions << ")  [3] Kabur\n> ";
        int choice;
        cin >> choice;

        if (choice == 1) {
            int damage = rand() % player.attack + 1;
            enemy.hp -= damage;
            cout << "Kamu menyerang " << enemy.name << " dan menyebabkan " << damage << " damage.\n";
        } else if (choice == 2 && player.potions > 0) {
            int heal = rand() % 20 + 10;
            player.hp += heal;
            if (player.hp > player.maxHp) player.hp = player.maxHp;
            player.potions--;
            cout << "🧪 Kamu menggunakan potion dan memulihkan " << heal << " HP. (HP sekarang: " << player.hp << ")\n";
            continue; // musuh tidak menyerang jika kamu healing
        } else if (choice == 3) {
            cout << "Kamu kabur dari pertarungan!\n";
            return;
        } else {
            cout << "Pilihan tidak valid.\n";
            continue;
        }

        if (enemy.hp > 0) {
            int enemyDamage = rand() % enemy.attack + 1;
            player.hp -= enemyDamage;
            cout << enemy.name << " menyerang balik dan menyebabkan " << enemyDamage << " damage!\n";
        }
    }

    if (player.hp > 0) {
        cout << "\n🎉 Kamu mengalahkan " << enemy.name << "!\n";
        player.exp += enemy.rewardExp;
        player.gold += enemy.rewardGold;
        cout << "🎁 Dapat " << enemy.rewardExp << " EXP dan " << enemy.rewardGold << " gold!\n";
        levelUp(player);
    } else {
        cout << "\n💀 Kamu dikalahkan oleh " << enemy.name << ".\n";
    }
}

void shop(Player &player) {
    cout << "\n🛒 Selamat datang di toko!\nPotion: 15 gold\n[1] Beli Potion  [2] Keluar\n> ";
    int choice;
    cin >> choice;

    if (choice == 1) {
        if (player.gold >= 15) {
            player.gold -= 15;
            player.potions++;
            cout << "Kamu membeli 1 potion. Potion sekarang: " << player.potions << "\n";
        } else {
            cout << "💸 Gold kamu tidak cukup!\n";
        }
    }
}

void rest(Player &player) {
    int heal = rand() % 15 + 10;
    player.hp += heal;
    if (player.hp > player.maxHp) player.hp = player.maxHp;
    cout << "🛏️  Kamu istirahat dan memulihkan " << heal << " HP. (HP sekarang: " << player.hp << "/" << player.maxHp << ")\n";
}

void showStatus(Player &player) {
    cout << "\n👤 " << player.name << " | Level: " << player.level
         << " | HP: " << player.hp << "/" << player.maxHp
         << " | ATK: " << player.attack
         << " | EXP: " << player.exp << "/100"
         << " | Gold: " << player.gold
         << " | Potion: " << player.potions << "\n";
}

int main() {
    srand(time(0));

    Player player;
    cout << "Masukkan nama karaktermu: ";
    getline(cin, player.name);
    player.hp = 50;
    player.maxHp = 50;
    player.attack = 10;
    player.level = 1;
    player.exp = 0;
    player.gold = 0;
    player.potions = 1;

    cout << "\n✨ Petualangan dimulai, " << player.name << "!\n";

    while (player.hp > 0) {
        cout << "\n======= MENU =======\n";
        cout << "1. Menjelajah\n2. Istirahat\n3. Status\n4. Toko\n5. Keluar\n";
        cout << "Pilih aksi: ";
        int menu;
        cin >> menu;

        switch (menu) {
            case 1: battle(player); break;
            case 2: rest(player); break;
            case 3: showStatus(player); break;
            case 4: shop(player); break;
            case 5:
                cout << "👋 Terima kasih sudah bermain!\n";
                return 0;
            default:
                cout << "Pilihan tidak valid.\n";
        }

        if (player.hp <= 0) {
            cout << "\n💀 Game Over! Kamu telah gugur dalam petualangan.\n";
        }
    }

    return 0;
}
