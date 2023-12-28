#include "Hero.h"
#include "Monster.h"
#include <cmath>

Monster::Monster() noexcept : Character() {
    setProtection(1);
    setDamage(1);
    setHealth(3);
}

void Monster::calculateMonsterAttack(Hero& hero, MonsterContainer& monsters) {
    for (Monster& monster : monsters) {
        int monsterDistance = std::max(std::abs(hero.getPosition().x - monster.getPosition().x), std::abs(hero.getPosition().y - monster.getPosition().y));

        int totalAttack;
        if (monster.getHealth() > 0) {
            if (monsterDistance <= hero.getDistance()) {
                totalAttack = monster.getDamage();
            }
            else {
                totalAttack = 0;
            }
        }
        else {
            return;
        }

        int heroDefense = hero.getProtection();
        int damage;

        if (totalAttack > heroDefense) {
            damage = totalAttack - heroDefense;
        }
        else {
            damage = 0;
        }

        hero.reduceHealth(damage);
    }
}